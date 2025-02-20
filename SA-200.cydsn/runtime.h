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


#define DEEPSLEEP

#define FIRMWARE_VISION "01.00.00"
#define HARDWARE_VISION "R1"


#define SENSOR_READINGS_DATA        0
#define SENSOR_CAL_DATA             10
#define SENSOR_STATIC_DATA          20
#define SENSOR_CFG_DATA             50
#define SENSOR_DEBUG_DATA           60

#define SENSOR_READINGS_LENGTH      10
#define SENSOR_CAL_DATA_LENGTH      10
#define SENSOR_STATIC__DATA_LENGTH  20
#define SENSOR_CFG_DATA_LENGTH      10
#define SENSOR_DEBUG_DATA_LENGTH    10


#define POLL_SENSOR_STATUS_OK       0
#define POLL_SENSOR_STATUS_ABSENT   8
#define POLL_SENSOR_PERIOD_MS       250 
#define POLL_SENSOR_PERIOD_S        2 

// Modbus definitions
#define MODBUS_MY_DEFAULT_ADDRESS   1
#define MODBUS_BROADCAST_ADDRESS    254
#define MODBUS_ADDRESS_REG          100
#define MODBUS_I2C_PERIOD_REG       101
#define MODBUS_SLEEP_PERIOD_REG     102
#define MODBUS_DEBUG_REG            103
#define MODBUS_FM_VERSION_REG       104
//I2C definitions
#define MINIMAL_DEFAULT_I2C_PERIOD   250

//Sleep Mode definitions
#define MINIMAL_SLEEP_PERIOD        2000
#define DEFAULT_SLEEP_PERIOD        20000

#define BUFFER_SIZE 100
 
typedef struct {
    uint8 reg;
    uint8 data[BUFFER_SIZE];
}S_I2C;


#define RS232_RX_BUFFER_SIZE 8



/* WDT counter time configuration.
 * The time is based on LFCLK (32768hz).
 * Time is 7.999 seconds ((7FFF x 8) / 32768)
*/
#define WDT_COUNT0_MATCH                    ( 0x7FFFu )         /* 1 second @ 32768hz */
#define WDT_COUNT1_MATCH                    ( 0x000Au )         /* 8 seconds ( 8 * 32768hz ) */
#define WDT_INIT                            SysWdtInit( );    /* Initialize the WDT */
#define WDT_RESET                           SysWdtReset( );   /* Reset the WDT */
/* End WDT defines */
void SysWdtInit( void );
void SysWdtReset( void );
CY_ISR_PROTO( SysWdtIsrHandler );


extern uint8_t mySlaveAddr,msa;


void Test_Increment(uint8 reg , uint8 bytes_to_send);

void InitSystem(void);
int32_t LoadSensorInfo(void);

uint8_t EEPROM_GetMyAddress(void);
void EEPROM_SetMyAddress(uint8_t addr);
uint16_t EEPROM_GetI2CPeriod(void);
void EEPROM_SetI2CPeriod(uint16_t period);
uint16_t EEPROM_GetSleepPeriod(void);
void EEPROM_SetSleepPeriod(uint16_t period);

void runtime_PollSensor(void);
void runtime_CtrlSensor(uint8_t reg , uint16_t data);

void runtime_ProcessRequest(void);
void runtime_RS232ProcessRequest(void);
void runtime_GetMySlaveAddress(void);

void GoToSleep(void);

void BLE_Start(void);
void ResetBLETimer(void);
void SetSleepPeriod(uint16_t period);



void isBLEDisconneted(void);
void updateData(void);
void updateOurBleData(void);
void Stack_Handler(uint32 eventCode, void *eventParam);

void remove_trailing_spaces(char* dst, char *str);

/* [] END OF FILE */
