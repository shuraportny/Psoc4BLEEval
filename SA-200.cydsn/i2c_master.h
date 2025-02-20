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

#include "project.h"

#define EEPROM_I2C_ADDRESS              0x50
#define EEPROM_MY_ADDRESS_REG           0
#define EEPROM_I2C_PERIOD_MSB_REG       1
#define EEPROM_I2C_PERIOD_LSB_REG       2
#define EEPROM_SLEEP_PERIOD_MSB_REG     3
#define EEPROM_SLEEP_PERIOD_LSB_REG     4

#define I2C_SLAVE_ADDR              0x61
#define I2C_SYS_READING_OFFSET      (1)
#define I2C_CALIBRATION_OFFSET      (11)
#define I2C_STATIC_DATA_OFFSET      (21)
#define I2C_CONFIG_DATA_OFFSET      (35)


#define I2C_NO_ERROR 0

#define I2CS_BUFF_SIZE          (100)



uint32_t i2c_status(uint8 slave);
uint8 i2c_Read_8( uint8 slave, uint8 address );
uint16 i2c_read_16( uint8 slave, uint8 address );
void i2c_write_8( uint8 slave, uint8 address, uint8 data );
void i2c_write_16( uint8 slave, uint8 address, uint16 data );

uint32 slave_ReadDataRaw(uint8 Reg, uint16 dataSize, uint8 *dataPtr);
uint32 slave_WriteDataRaw(uint8 Reg, uint16 dataSize, uint8 *dataPtr);

/* [] END OF FILE */
