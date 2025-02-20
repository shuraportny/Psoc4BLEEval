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
#include "i2c_master.h"


// TEST I2C SLAVE DATA 
uint8_t slaveBuf[I2CS_BUFF_SIZE]={21,32,33,34,35,36,37,38,39,40};

uint32_t i2c_status(uint8 slave){
    uint32_t status;
    status = I2C_I2CMasterSendStart( slave, I2C_I2C_WRITE_XFER_MODE,1 ); 
    I2C_I2CMasterSendStop(1);
    //CyDelay(1);
    return status;
}


uint8 i2c_Read_8( uint8 slave, uint8 address )
{
    static uint8 theResult = 0;
    uint8_t status;
    //slave = slave >> 1;                                                         /* MasterSendStart requires address as 7 bit */
    I2C_I2CMasterSendStart( slave, I2C_I2C_WRITE_XFER_MODE,1 );                 /* Send start write */
    I2C_I2CMasterWriteByte( address, 1 );                                         /* Send address */
    I2C_I2CMasterSendRestart( slave, I2C_I2C_READ_XFER_MODE,1 );                /* Send re-start read */
    status = I2C_I2CMasterReadByte( I2C_I2C_NAK_DATA,&theResult, 1 );                    /* Receive byte */
    (void) I2C_I2CMasterSendStop(1);                                            /* Send stop */
    (void) I2C_I2CMasterClearStatus();                                         /* Clear status flags */
    return( theResult );                                                        /* Return the result */
}

uint16 i2c_read_16( uint8 slave, uint8 address )
{
    uint16 theResult;
    theResult = i2c_Read_8( slave, address );
    theResult <<= 8;
    theResult |= i2c_Read_8( slave, (address + 1) );
    return( theResult );
}


void i2c_write_8( uint8 slave, uint8 address, uint8 data )
{
    //slave = slave >> 1;                                                         /* MasterSendStart requires address as 7 bit */
    I2C_I2CMasterSendStart( slave, I2C_I2C_WRITE_XFER_MODE , 1 );                 /* Send start write */
    I2C_I2CMasterWriteByte( address , 1 );                                         /* Send address */
    I2C_I2CMasterWriteByte( data ,1 );                                            /* Send byte */
    (void) I2C_I2CMasterSendStop(1);                                            /* Send stop */
    (void) I2C_I2CMasterClearStatus();                                         /* Clear status flags */
    CyDelay( 10u );                                                             /* Allow 10milliseconds for write */
}


void i2c_write_16( uint8 slave, uint8 address, uint16 data )
{
    uint8 byteToWrite;
    byteToWrite = ( uint8 )( data >> 8 );                                       /* Load upper byte */
    i2c_write_8( slave, address, byteToWrite );                            /* Write it */
    byteToWrite = ( uint8 )( data );                                            /* Load lower byte */
    i2c_write_8( slave, ( address + 1 ), byteToWrite );                    /* Write it */
    CyDelay( 10u );                                                             /* Allow 10milliseconds for write */
}

uint32 slave_ReadDataRaw(uint8 Reg, uint16 dataSize, uint8 *dataPtr){
uint8 txData[1];
uint32 wrStatus;
    txData[0] = Reg;
    while (I2C_I2CMasterStatus()== I2C_I2C_MSTAT_XFER_INP){};
    wrStatus = I2C_I2CMasterWriteBuf(I2C_SLAVE_ADDR, txData, 1, I2C_I2C_MODE_NO_STOP);
    
    if (I2C_I2C_MSTAT_ERR_ADDR_NAK ==I2C_I2CMasterStatus() ){
        wrStatus = I2C_I2C_MSTAT_ERR_ADDR_NAK;    
    }
    
    while( (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT) == 0){};
    
    I2C_I2CMasterReadBuf(I2C_SLAVE_ADDR, dataPtr, dataSize, I2C_I2C_MODE_REPEAT_START);
    while( (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT) == 0){};
    
    //return I2C_NO_ERROR;  // Return success code if data is read successfully
    return wrStatus;
}

uint32 slave_WriteDataRaw(uint8 Reg, uint16 dataSize, uint8 *dataPtr){
    
//    while (I2C_I2CMasterStatus()== I2C_I2C_MSTAT_XFER_INP){};
//    I2C_I2CMasterWriteBuf(I2C_SLAVE_ADDR, &reg, 1, I2C_I2C_MODE_REPEAT_START);
//    while( (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT) == 0){};
//    I2C_I2CMasterWriteBuf(I2C_SLAVE_ADDR, dataPtr, dataSize, I2C_I2C_MODE_COMPLETE_XFER);
//    while( (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT) == 0){};
//    return I2C_NO_ERROR;
    
    
    
    I2C_I2CMasterWriteBuf(I2C_SLAVE_ADDR, dataPtr, dataSize+1,I2C_I2C_MODE_COMPLETE_XFER ); // we send dataSize+1 byte because we send register first and then data
    
    
//    I2C_I2CMasterSendStart( I2C_SLAVE_ADDR, I2C_I2C_WRITE_XFER_MODE , 1 );                 /* Send start write */
//    I2C_I2CMasterWriteByte( Reg , 1 );  
//    for (uint32_t i = 0; i < dataSize; i++){/* Send address */
//        I2C_I2CMasterWriteByte( *dataPtr ,1 );    
//        dataPtr++;
//    }
//    (void) I2C_I2CMasterSendStop(1);   
//    return I2C_NO_ERROR;
    
}


/* [] END OF FILE */
