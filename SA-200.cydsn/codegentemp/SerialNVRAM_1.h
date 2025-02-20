/***************************************************************************//**
* \file SerialNVRAM_1.h
* \version 1.0
*
* \brief
* This file provides constants and parameter values for the SerialNVRAM 
* Component.
* 
********************************************************************************
* Copyright (2017), Cypress Semiconductor Corporation.
******************************************************************************** 
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
* CYPRESS PROVIDES THIS SOFTWARE "AS IS" AND MAKES NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED 
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS 
* FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#if !defined(CY_SERIAL_NVRAM_SerialNVRAM_1_H) /* CY_SERIAL_NVRAM_SerialNVRAM_1_H */
#define CY_SERIAL_NVRAM_SerialNVRAM_1_H

#include "cytypes.h"
#include "cyfitter.h"

#include ".h"

#if (1 == 1)
    #include "_SPI_UART.h"
    #include "SerialNVRAM_1_CS_0.h"
    #if (1 == 0)
        #include "SerialNVRAM_1_HOLD.h"
    #endif
    #if (1 < 1)
        #include "SerialNVRAM_1_CS_1.h"
        #if (2 < 1)
            #include "SerialNVRAM_1_CS_2.h"
        #endif
            #if (3 < 1)
                #include "SerialNVRAM_1_CS_3.h"
            #endif
   #endif
#endif

#if (1 == 0)
    #include "SerialNVRAM_1_WP.h"
#endif

#if (2 == 1)
    #include "_I2C.h"
#endif

/***************************************
*    Initial Parameter Constants        
***************************************/

#define SerialNVRAM_1_INTERFACE                  1
#define SerialNVRAM_1_MASTER_INTERFACE           
#define SerialNVRAM_1_SPI_CHIP_SELECT            1
#define SerialNVRAM_1_DENSITY                    7
#define SerialNVRAM_1_ENABLE_WRITE_PROTECTION    0
#define SerialNVRAM_1_ENABLE_HOLD                0
#define SerialNVRAM_1_SPI_BIT_RATE               

/***************************************
*   Conditional Compilation Parameters  
***************************************/

#define SerialNVRAM_1_INTERFACE_SPI_SCB          (1U)
#define SerialNVRAM_1_INTERFACE_I2C_SCB          (2U)

/* Densities */
#define SerialNVRAM_1_DENSITY_4_KBIT             (1U)
#define SerialNVRAM_1_DENSITY_16_KBIT            (2U)
#define SerialNVRAM_1_DENSITY_64_KBIT            (3U)
#define SerialNVRAM_1_DENSITY_128_KBIT           (4U)
#define SerialNVRAM_1_DENSITY_256_KBIT           (5U)
#define SerialNVRAM_1_DENSITY_512_KBIT           (6U)
#define SerialNVRAM_1_DENSITY_1_MBIT             (7U)
#define SerialNVRAM_1_DENSITY_2_MBIT             (8U)
#define SerialNVRAM_1_DENSITY_4_MBIT             (9U)
#define SerialNVRAM_1_DENSITY_8_MBIT             (10U)


/***************************************
*   API Constants  
***************************************/

/* Values for SerialNVRAM_1_SetHold() and SerialNVRAM_1_SetWp() functions */
#define SerialNVRAM_1_HIGH                       (1U)           /**< Logic high */
#define SerialNVRAM_1_LOW                        (0U)           /**< Logic low */

/** The define to show the data is sent/received and the component is ready 
* to send/receive new data */
#define SerialNVRAM_1_READY                      (0U)

/** The define to show the component is sending/receiving previous data */
#define SerialNVRAM_1_BUSY                       (1U)

/* SPI chip select IDs */
#define SerialNVRAM_1_CS0                        (0U)      /**< SPI Chip select 0 */
#define SerialNVRAM_1_CS1                        (1U)      /**< SPI Chip select 1 */
#define SerialNVRAM_1_CS2                        (2U)      /**< SPI Chip select 2 */
#define SerialNVRAM_1_CS3                        (3U)      /**< SPI Chip select 3 */

/* NVRAM commands */
#define SerialNVRAM_1_NVRAM_WREN                 (0x06U)   /**< Write Enable command */
#define SerialNVRAM_1_NVRAM_WRDI                 (0x04U)   /**< Write Disable command */
#define SerialNVRAM_1_NVRAM_SRAM_WRITE_CMD       (0x02U)   /**< NVRAM Write command */
#define SerialNVRAM_1_NVRAM_SRAM_READ_CMD        (0x03U)   /**< NVRAM Read command */
#define SerialNVRAM_1_NVRAM_SRAM_FAST_READ_CMD   (0x0BU)   /**< NVRAM Fast Read command */
#define SerialNVRAM_1_NVRAM_RDSR_CMD             (0x05U)   /**< Read Status Register command */
#define SerialNVRAM_1_NVRAM_WRSR_CMD             (0x01U)   /**< Write Status Register command */
#define SerialNVRAM_1_NVRAM_RDID_CMD             (0x9FU)   /**< Read ID command */
#define SerialNVRAM_1_NVRAM_SLEEP_CMD            (0xB9U)   /**< Sleep mode command */
#define SerialNVRAM_1_NVRAM_WRSN_CMD             (0xC2U)   /**< Serial number write command */
#define SerialNVRAM_1_NVRAM_RDSN_CMD             (0xC3U)   /**< Serial number read command */
#define SerialNVRAM_1_NVRAM_WRPC_CMD             (0x12U)   /**< Write Processor Companion command */
#define SerialNVRAM_1_NVRAM_RDPC_CMD             (0x13U)   /**< Read Processor Companion command */
#define SerialNVRAM_1_NVRAM_WRTC_CMD             (0x12U)   /**< Write RTC (WRTC) instruction */
#define SerialNVRAM_1_NVRAM_RDRTC_CMD            (0x13U)   /**< Read RTC (RDRTC) instruction */
#define SerialNVRAM_1_NVRAM_STORE_CMD            (0x3CU)   /**< Software STORE command */
#define SerialNVRAM_1_NVRAM_RECALL_CMD           (0x60U)   /**< Software RECALL command */
#define SerialNVRAM_1_NVRAM_ASENB_CMD            (0x59U)   /**< AutoStore enable command */
#define SerialNVRAM_1_NVRAM_ASDISB_CMD           (0x19U)   /**< AutoStore disable command */

/* RTC Register Map used for RTC-related functions */
#define SerialNVRAM_1_RTC_YEARS_00_99            (0x0FU)   /**< Years: 00–99 */
#define SerialNVRAM_1_RTC_MTHS_01_12             (0x0EU)   /**< Months: 01–12 */
#define SerialNVRAM_1_RTC_DAY_OF_MTH_01_31       (0x0DU)   /**< Day of month: 01–31 */
#define SerialNVRAM_1_RTC_DAY_OF_WEEK_01_07      (0x0CU)   /**< Day of week: 01–07 */
#define SerialNVRAM_1_RTC_HOURS_00_23            (0x0BU)   /**< Hours: 00–23 */
#define SerialNVRAM_1_RTC_MINUTES_00_59          (0x0AU)   /**< Minutes: 00–59 */
#define SerialNVRAM_1_RTC_SECONDS_00_59          (0x09U)   /**< Seconds: 00–59 */
#define SerialNVRAM_1_RTC_CALIBRATION_VALUES     (0x08U)   /**< Calibration values */
#define SerialNVRAM_1_RTC_WATCHDOG               (0x07U)   /**< Watchdog */
#define SerialNVRAM_1_RTC_INTERRUPTS             (0x06U)   /**< Interrupts */
#define SerialNVRAM_1_RTC_ALARM_DAY_OF_MTH_01_31 (0x05U)   /**< Alarm, day of month: 01–31 */
#define SerialNVRAM_1_RTC_ALARM_HOURS_00_23      (0x04U)   /**< Alarm, hours: 00–23 */
#define SerialNVRAM_1_RTC_ALARM_MINUTES_00_59    (0x03U)   /**< Alarm, minutes: 00–59 */
#define SerialNVRAM_1_RTC_ALARM_SECONDS_00_59    (0x02U)   /**< Alarm, seconds: 00–59 */
#define SerialNVRAM_1_RTC_CENTURIES_00_99        (0x01U)   /**< Centuries: 00–99 */
#define SerialNVRAM_1_RTC_FLAGS                  (0x00U)   /**< Flags */

/* Register Map for SPI F-RAM processor companion devices (For example, FM33256BG) */
#define SerialNVRAM_1_COMPANION_ALARM_MONTH      (0x1DU)   /**< Alarm Month: 01–12 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_ALARM_DATE       (0x1CU)   /**< Alarm Date: 01-31 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_ALARM_HOURS      (0x1BU)   /**< Alarm Hours: 01-23 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_ALARM_MINUTES    (0x1AU)   /**< Alarm Minutes: 01-59 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_ALARM_SECONDS    (0x19U)   /**< Alarm Seconds: 01-59 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_CONTROL          (0x18U)   /**< Companion Control (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SERIAL_NUMBER_7  (0x17U)   /**< Serial Number Byte 7 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SERIAL_NUMBER_6  (0x16U)   /**< Serial Number Byte 6 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SERIAL_NUMBER_5  (0x15U)   /**< Serial Number Byte 5 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SERIAL_NUMBER_4  (0x14U)   /**< Serial Number Byte 4 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SERIAL_NUMBER_3  (0x13U)   /**< Serial Number Byte 3 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SERIAL_NUMBER_2  (0x12U)   /**< Serial Number Byte 2 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SERIAL_NUMBER_1  (0x11U)   /**< Serial Number Byte 1 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SERIAL_NUMBER_0  (0x10U)   /**< Serial Number Byte 0 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_EVENT_COUNTER_1  (0x0FU)   /**< Event Counter Byte 1 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_EVENT_COUNTER_0  (0x0EU)   /**< Event Counter Byte 0 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_EVENT_CNT_CTL    (0x0DU)   /**< Event Counter Control (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_WDT_CONTROL_1    (0x0CU)   /**< Watchdog Control (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_WDT_CONTROL_0    (0x0BU)   /**< Watchdog Control (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_WDT_RESTART      (0x0AU)   /**< Watchdog Restart (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_WDT_FLAGS        (0x09U)   /**< Watchdog Flags (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_YEARS_00_99      (0x08U)   /**< Years: 00-99 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_MONTH_01_12      (0x07U)   /**< Month: 01-12 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_DATE_01_31       (0x06U)   /**< Date: 01-31 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_DAY_01_07        (0x05U)   /**< Day: 01-07 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_HOURS_00_23      (0x04U)   /**< Hours: 00-23 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_MINUTES_00_59    (0x03U)   /**< Minutes: 00-59 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_SECONDS_00_59    (0x02U)   /**< Seconds: 00-59 (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_CAL_CONTROL      (0x01U)   /**< CAL/Control (for SPI  processor companion devices) */
#define SerialNVRAM_1_COMPANION_RTC_ALARM_CTL    (0x00U)   /**< RTC/Alarm Control (for SPI  processor companion devices) */

/* Register Map for I2C F-RAM processor companion devices (For example, FM31L276, FM31L278) */
#define SerialNVRAM_1_I2C_COMP_SERIAL_NUMBER_7   (0x18U)   /**< Serial Number Byte 7 (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_SERIAL_NUMBER_6   (0x17U)   /**< Serial Number Byte 6 (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_SERIAL_NUMBER_5   (0x16U)   /**< Serial Number Byte 5 (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_SERIAL_NUMBER_4   (0x15U)   /**< Serial Number Byte 4 (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_SERIAL_NUMBER_3   (0x14U)   /**< Serial Number Byte 3 (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_SERIAL_NUMBER_2   (0x13U)   /**< Serial Number Byte 2 (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_SERIAL_NUMBER_1   (0x12U)   /**< Serial Number Byte 1 (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_SERIAL_NUMBER_0   (0x11U)   /**< Serial Number Byte 0 (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_EVENT_CNT_2_MSB   (0x10U)   /**< Event Counter 2 MSB (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_EVENT_CNT_2_LSB   (0x0FU)   /**< Event Counter 2 LSB (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_EVENT_CNT_1_MSB   (0x0EU)   /**< Event Counter 1 MSB (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_EVENT_CNT_1_LSB   (0x0DU)   /**< Event Counter 1 LSB (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_EVENT_COUNT_CTR   (0x0CU)   /**< Event Count Control (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_COMPANION_CTR     (0x0BU)   /**< Companion Control (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_WATCHDOG_CTR      (0x0AU)   /**< Watchdog Control (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_WATCHDOG_FLAGS    (0x09U)   /**< Watchdog Restart/Flags (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_YEARS             (0x08U)   /**< Years (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_MONTH             (0x07U)   /**< Month (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_DATE              (0x06U)   /**< Date (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_DAY               (0x05U)   /**< Day (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_HOURS             (0x04U)   /**< Hours (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_MINUTES           (0x03U)   /**< Minutes (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_SECONDS           (0x02U)   /**< Seconds (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_CAL_CTR           (0x01U)   /**< CAL Control (for I2C processor companion devices) */
#define SerialNVRAM_1_I2C_COMP_RTC_CTR           (0x00U)   /**< RTC Control (for I2C processor companion devices) */

/* ID lengths used in SerialNVRAM_1_SpiDevIdRead() function */
#define SerialNVRAM_1_3_BYTE_DEVICE_ID           (3U)      /**< 3 bytes ID length */
#define SerialNVRAM_1_4_BYTE_DEVICE_ID           (4U)      /**< 4 bytes ID length */
#define SerialNVRAM_1_8_BYTE_DEVICE_ID           (8U)      /**< 8 bytes ID length */
#define SerialNVRAM_1_9_BYTE_DEVICE_ID           (9U)      /**< 9 bytes ID length */


/* I2C communication timeout  */
#define SerialNVRAM_1_I2C_COM_TIMEOUT_MS         (10U)

/* SPI communication timeout at 1000us = 1ms */
#define SerialNVRAM_1_SPI_COM_TIMEOUT            (1000U)

/* Status Register bit definition */
#define SerialNVRAM_1_SPI_NOT_RDY                (0x01U)    /* Ready */
#define SerialNVRAM_1_SPI_WEN                    (0x02U)    /* Write Enable */
#define SerialNVRAM_1_SPI_BP0                    (0x04U)    /* Block Protect bit 0 */
#define SerialNVRAM_1_SPI_BP1                    (0x08U)    /* Block Protect bit 1 */
#define SerialNVRAM_1_SPI_SNL                    (0x40U)    /* Serial Number Lock */
#define SerialNVRAM_1_SPI_WPEN                   (0x80U)    /* Write Protect Enable bit */

/* Address masks */
#define SerialNVRAM_1_LSBIT_MASK                 (1U)
#define SerialNVRAM_1_MSBIT_MASK                 (0x010000UL) /* upto 1 Mbit */
#define SerialNVRAM_1_MSB_ADDR_MASK              (0xFF0000UL)
#define SerialNVRAM_1_ISB_ADDR_MASK              (0x00FF00UL)
#define SerialNVRAM_1_MSB_ADDR_SHIFTBITS         (16U)
#define SerialNVRAM_1_ISB_ADDR_SHIFTBITS         (8U)

#define SerialNVRAM_1_I2C_SLAVE_ADDR_SHIFT       (0x01U)   /* I2C slave Device select ID position */
#define SerialNVRAM_1_I2C_SLAVE_ADDR_MASK        (0x07U)   /* I2C slave Device select ID mask */
#define SerialNVRAM_1_I2C_RSVD_SLAVE_ADDR_MASK   (0x56U)   /* I2C slave Device select ID mask */
#define SerialNVRAM_1_I2C_FM24V10_SLAVE_ID       (0x50U)   /* FM24V10 Device Slave ID */
#define SerialNVRAM_1_NVRAM_SEL_MEM_MASK         (0x50U)   /* I2C Memory selection mask */
#define SerialNVRAM_1_NVRAM_SEL_RTCR_MASK        (0x68U)   /* I2C RTC Registers selection mask */
#define SerialNVRAM_1_NVRAM_SEL_CR_MASK          (0x18U)   /* I2C Control Registers selection mask */

#define SerialNVRAM_1_MEM_CTR_REG_ADDR           (0x00U)   /* Memory Control Register address */
#define SerialNVRAM_1_SERIAL_NUM_REG_ADDR        (0x01U)   /* Serial Number address */
#define SerialNVRAM_1_DEVICE_ID_REG_ADDR         (0x09U)   /* Device ID address */
#define SerialNVRAM_1_COMMAND_REG_ADDR           (0xAAU)   /* Command Register address */

#define SerialNVRAM_1_RSVD_SLAVE_ID              (0xF8U >> 1U)   /* Reserved Slave ID */
#define SerialNVRAM_1_RSVD_SLAVE_SERIAL_NUM_ID   (0xCDU >> 1U)   /* Reserved Slave ID to read the serial number */
#define SerialNVRAM_1_RSVD_SLAVE_DEV_ID          (0xF9U >> 1U)   /* Reserved Slave ID to read the device ID */
#define SerialNVRAM_1_RSVD_SLAVE_SLEEP_ID        (0x86U >> 1U)   /* Reserved Slave ID or sleep */

/* Other constants */
#define SerialNVRAM_1_SERIAL_NUM_LENGTH          (8U)      /* Serial number length */



/******************************************************************************
 * Enumerations
 *****************************************************************************/

/** The error codes */
typedef enum 
{
    SerialNVRAM_1_SUCCESS             = 0x00u,  /**< Successful */
    SerialNVRAM_1_DEVICE_BUSY         = 0x01u,  /**< The device is busy */
    SerialNVRAM_1_DEVICE_ERROR        = 0x02u,  /**< A device error */
    SerialNVRAM_1_TIMEOUT_ERROR       = 0x04u,  /**< Operation has timed out */
    SerialNVRAM_1_COMMUNICATION_ERROR = 0x08u  /**< A communication error */ 
} SerialNVRAM_1_status; 

/** @} group_constants */


/***************************************
*    Function Prototypes                
***************************************/
/**
* \addtogroup group_general
* @{
*/
void SerialNVRAM_1_Init(void);
void SerialNVRAM_1_Start(void);
void SerialNVRAM_1_Stop(void);
SerialNVRAM_1_status SerialNVRAM_1_GetStatus(uint8 nvramId);
SerialNVRAM_1_status SerialNVRAM_1_MemoryWrite(uint8 nvramId, 
                                                     uint32 addr, 
                                                     const uint8 *dataWritePtr, 
                                                     uint32 totalDataCount);
SerialNVRAM_1_status SerialNVRAM_1_MemoryRead(uint8 nvramId, 
                                                    uint32 addr, 
                                                    uint8 *dataReadPtr, 
                                                    uint32 totalDataCount);
#if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
    SerialNVRAM_1_status SerialNVRAM_1_CurrentMemoryRead(uint8 nvramId, 
                                                               uint8 *dataReadPtr, 
                                                               uint32 totalDataCount);
#endif
#if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
    SerialNVRAM_1_status SerialNVRAM_1_MemoryFastReadOpcode(uint8 nvramId, 
                                                                  uint32 addr, 
                                                                  uint8 *dataReadPtr, 
                                                                  uint32 totalDataCount);
    SerialNVRAM_1_status SerialNVRAM_1_StatusRegWrite(uint8 nvramId, uint8 dataByte);
    SerialNVRAM_1_status SerialNVRAM_1_StatusRegRead(uint8 nvramId, uint8 *dataByte);
    SerialNVRAM_1_status SerialNVRAM_1_WriteProcessorCompanion(uint8 nvramId,
                                                                     uint32 addr,
                                                                     const uint8 *dataPtr,
                                                                     uint32 totalDataCount);
    SerialNVRAM_1_status SerialNVRAM_1_ReadProcessorCompanion(uint8 nvramId,
                                                                    uint32 addr,
                                                                    uint8 *dataReadPtr,
                                                                    uint32 totalDataCount);
#endif
#if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
    SerialNVRAM_1_status SerialNVRAM_1_MemCtrlRegWrite(uint8 nvramId, uint8 dataByte);
    SerialNVRAM_1_status SerialNVRAM_1_MemCtrlRegRead(uint8 nvramId, uint8 *dataByte);
#endif
SerialNVRAM_1_status SerialNVRAM_1_Sleep(uint8 nvramId);
SerialNVRAM_1_status SerialNVRAM_1_NvCommand(uint8 nvramId, uint8 nvcmd);
SerialNVRAM_1_status SerialNVRAM_1_SerialNoWrite(uint8 nvramId, const uint8 *dataPtr);
SerialNVRAM_1_status SerialNVRAM_1_SerialNoRead(uint8 nvramId, uint8 *dataPtr);                                                   
SerialNVRAM_1_status SerialNVRAM_1_DevIdRead(uint8 nvramId, 
                                                   uint8 *dataPtr, 
                                                   uint8 iDLength);
SerialNVRAM_1_status SerialNVRAM_1_RtcRegWrite(uint8 nvramId, 
                                                     uint32 addr, 
                                                     const uint8 *dataWritePtr, 
                                                     uint32 totalDataCount);
SerialNVRAM_1_status SerialNVRAM_1_RtcRegRead(uint8 nvramId, 
                                                    uint32 addr, 
                                                    uint8 *dataReadPtr, 
                                                    uint32 totalDataCount);
#if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
    SerialNVRAM_1_status SerialNVRAM_1_CurrentRtcRegRead(uint8 nvramId, 
                                                               uint8 *dataReadPtr, 
                                                               uint32 totalDataCount);
#endif
#if (1 == SerialNVRAM_1_ENABLE_WRITE_PROTECTION)
    void SerialNVRAM_1_SetWp(uint8 value);
#endif
#if ((SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE) &&\
     (1 == SerialNVRAM_1_ENABLE_HOLD))
    void SerialNVRAM_1_SetHold(uint8 value);
#endif
/** @} group_general */


/***************************************
*           Global Variables
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8 SerialNVRAM_1_initVar;
/** @} globals */


/***************************************
*    Macros       
***************************************/

    /* Master interface init */
    #define SerialNVRAM_1_InterfaceStart()           _Start()
    
    /* SPI chip select pin controls */
    #define SerialNVRAM_1_CS_0_OFF                   SerialNVRAM_1_CS_0_Write(1u)
    #define SerialNVRAM_1_CS_1_OFF                   SerialNVRAM_1_CS_1_Write(1u)
    #define SerialNVRAM_1_CS_2_OFF                   SerialNVRAM_1_CS_2_Write(1u)
    #define SerialNVRAM_1_CS_3_OFF                   SerialNVRAM_1_CS_3_Write(1u)
    #define SerialNVRAM_1_CS_0_ON                    SerialNVRAM_1_CS_0_Write(0u)
    #define SerialNVRAM_1_CS_1_ON                    SerialNVRAM_1_CS_1_Write(0u)
    #define SerialNVRAM_1_CS_2_ON                    SerialNVRAM_1_CS_2_Write(0u)
    #define SerialNVRAM_1_CS_3_ON                    SerialNVRAM_1_CS_3_Write(0u)
    
#endif /* CY_SERIAL_NVRAM_SerialNVRAM_1_H */


/* [] END OF FILE */
