/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "EEProm.h"
/***************************************
*            Variabeles
****************************************/

/* RAM variables */


/* ROM variables */
/***************************************
*            
****************************************/
void EEProm_Write8(uint8_t reg_addr, uint8_t _data)
{
    I2C_I2CMasterSendStart( EEPROM_I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE,1 );  /* Send start with write */
    I2C_I2CMasterWriteByte( reg_addr,1 );                              /* Select register to read */
    I2C_I2CMasterWriteByte( _data,1 );                              /* Select register to read */
    I2C_I2CMasterSendStop(1 );                                     /* Send stop */
    I2C_I2CMasterClearStatus();
}
/***************************************
*            
****************************************/
uint8_t EEProm_Read8(uint8_t reg_addr)
{
    uint8_t ret;
    uint32_t status;
    I2C_I2CMasterSendStart( EEPROM_I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE,1 );     /* Send start with write */
    I2C_I2CMasterWriteByte( reg_addr,1 );                               /* Select register to read */
    I2C_I2CMasterSendRestart( EEPROM_I2C_ADDRESS, I2C_I2C_READ_XFER_MODE,1 );     /* Send Restart */
    status = I2C_I2CMasterReadByte( I2C_I2C_NAK_DATA,&ret, 1 );         /* Read the byte */
    I2C_I2CMasterSendStop(1 );                                         /* Send stop */
    I2C_I2CMasterClearStatus();                                           /* Clear Status */
    return( ret );
}

/***************************************
*            
****************************************/
void EEProm_Write_16( uint8 address, uint16 data )
{
    uint8 byteToWrite;
    byteToWrite = ( uint8 )( data >> 8 );                                       /* Load upper byte */
    EEProm_Write8( address, byteToWrite );                            /* Write it */
    byteToWrite = ( uint8 )( data );                                            /* Load lower byte */
    EEProm_Write8( ( address + 1 ), byteToWrite );                    /* Write it */
    CyDelay( 10u );                                                             /* Allow 10milliseconds for write */
}

/***************************************
*            
****************************************/
uint16_t EEProm_Read16(uint8_t reg_addr)
{
    union
    {
        uint8_t b[2];
        uint16_t w;
    } ret;
    I2C_I2CMasterSendStart( EEPROM_I2C_ADDRESS, I2C_I2C_WRITE_XFER_MODE );     /* Send start with write */
    I2C_I2CMasterWriteByte( reg_addr );                               /* Select register to read */
    I2C_I2CMasterSendRestart( EEPROM_I2C_ADDRESS, I2CM_I2C_READ_XFER_MODE );     /* Send Restart */
    ret.b[0] = I2CM_I2CMasterReadByte( I2CM_I2C_ACK_DATA );         /* Read the byte */
    ret.b[1] = I2CM_I2CMasterReadByte( I2CM_I2C_NAK_DATA );         /* Read the byte */
    I2C_I2CMasterSendStop( );                                         /* Send stop */
    I2C_I2CMasterClearStatus();                                           /* Clear Status */
    return( ret.w );
}
/*******************************************************************************
* Function Name: AT24CS01_DeviceSN
********************************************************************************
* Summary:
*  Master initiates the transfer to read 128bit device id from the slave.
*  The data read from the slave is returned.
*
* Parameters:
*  - slave:     I2C slave address.
*
* Return:
*  Returns data from slave.
*  - 
*  - 
*
*******************************************************************************/
/* NOT TESTED */
double EEprom_ReadDeviceSN( void )
{
    uint8 index;
//    uint8 offset = 112;
    uint8_t ret;
//    union
//    {
//        uint8 b[16];
//        volatile uint64_t d;
//    } ret;
    while( EZI2C_1_EzI2CGetActivity() != 0 ){}
    I2CM_I2CMasterSendStart( EEPROM_I2C_SN_ADDRESS, I2CM_I2C_WRITE_XFER_MODE );                 /* Send start write */
    I2CM_I2CMasterWriteByte( 0x80 );                                            /* Send address */
    I2CM_I2CMasterSendRestart( EEPROM_I2C_SN_ADDRESS, I2CM_I2C_READ_XFER_MODE );                /* Send re-start read */
    for(index = 0; index < 15; index++ )                                       /* Process all 16 bytes */
    {
        ret = I2CM_I2CMasterReadByte( I2CM_I2C_ACK_DATA );         /* Read the byte */
        ADFEi2cBuffer[index+LOC_SN_OFFSET] = ret;
    }
    ret = I2CM_I2CMasterReadByte( I2CM_I2C_ACK_DATA );         /* Read the byte */
    ADFEi2cBuffer[index+LOC_SN_OFFSET] = ret;
    I2CM_I2CMasterSendStop( );                                         /* Send stop */
    I2CM_I2CMasterClearStatus();                                           /* Clear Status */
    return( ret );
}

/* [] END OF FILE */
