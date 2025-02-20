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
#if !defined(EEProm_H) /* EEProm_H */
#define EEProm_H

#include <project.h>

/***************************************
*            Variables
****************************************/

/***************************************
*            Constants
****************************************/
#ifndef EEPROM_I2C_ADDRESS
#define EEPROM_I2C_ADDRESS 0x50
#endif

#ifndef EEPROM_I2C_SN_ADDRESS
#define EEPROM_I2C_SN_ADDRESS 0x58
#endif


/***************************************
*         Function Prototypes
****************************************/
void EEProm_Write8(uint8_t reg_addr, uint8_t _data);
uint8_t EEProm_Read8(uint8_t reg_addr);
void EEProm_Write_16( uint8 address, uint16 data );
uint16_t EEProm_Read16(uint8_t reg_addr);
//uint32 PingI2cSlave( uint8 slave );
double EEprom_ReadDeviceSN( void );

#endif /* EEProm_H */
/* [] END OF FILE */
