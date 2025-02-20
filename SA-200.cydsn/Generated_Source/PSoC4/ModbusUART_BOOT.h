/***************************************************************************//**
* \file ModbusUART_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_ModbusUART_H)
#define CY_SCB_BOOT_ModbusUART_H

#include "ModbusUART_PVT.h"

#if (ModbusUART_SCB_MODE_I2C_INC)
    #include "ModbusUART_I2C.h"
#endif /* (ModbusUART_SCB_MODE_I2C_INC) */

#if (ModbusUART_SCB_MODE_EZI2C_INC)
    #include "ModbusUART_EZI2C.h"
#endif /* (ModbusUART_SCB_MODE_EZI2C_INC) */

#if (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC)
    #include "ModbusUART_SPI_UART.h"
#endif /* (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define ModbusUART_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (ModbusUART_SCB_MODE_I2C_INC)
    #define ModbusUART_I2C_BTLDR_COMM_ENABLED     (ModbusUART_BTLDR_COMM_ENABLED && \
                                                            (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             ModbusUART_I2C_SLAVE_CONST))
#else
     #define ModbusUART_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (ModbusUART_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (ModbusUART_SCB_MODE_EZI2C_INC)
    #define ModbusUART_EZI2C_BTLDR_COMM_ENABLED   (ModbusUART_BTLDR_COMM_ENABLED && \
                                                         ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define ModbusUART_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (ModbusUART_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (ModbusUART_SCB_MODE_SPI_INC)
    #define ModbusUART_SPI_BTLDR_COMM_ENABLED     (ModbusUART_BTLDR_COMM_ENABLED && \
                                                            (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             ModbusUART_SPI_SLAVE_CONST))
#else
        #define ModbusUART_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (ModbusUART_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (ModbusUART_SCB_MODE_UART_INC)
       #define ModbusUART_UART_BTLDR_COMM_ENABLED    (ModbusUART_BTLDR_COMM_ENABLED && \
                                                            (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (ModbusUART_UART_RX_DIRECTION && \
                                                              ModbusUART_UART_TX_DIRECTION)))
#else
     #define ModbusUART_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (ModbusUART_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define ModbusUART_BTLDR_COMM_MODE_ENABLED    (ModbusUART_I2C_BTLDR_COMM_ENABLED   || \
                                                     ModbusUART_SPI_BTLDR_COMM_ENABLED   || \
                                                     ModbusUART_EZI2C_BTLDR_COMM_ENABLED || \
                                                     ModbusUART_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void ModbusUART_I2CCyBtldrCommStart(void);
    void ModbusUART_I2CCyBtldrCommStop (void);
    void ModbusUART_I2CCyBtldrCommReset(void);
    cystatus ModbusUART_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (ModbusUART_SCB_MODE_I2C_CONST_CFG)
        #define ModbusUART_CyBtldrCommStart   ModbusUART_I2CCyBtldrCommStart
        #define ModbusUART_CyBtldrCommStop    ModbusUART_I2CCyBtldrCommStop
        #define ModbusUART_CyBtldrCommReset   ModbusUART_I2CCyBtldrCommReset
        #define ModbusUART_CyBtldrCommRead    ModbusUART_I2CCyBtldrCommRead
        #define ModbusUART_CyBtldrCommWrite   ModbusUART_I2CCyBtldrCommWrite
    #endif /* (ModbusUART_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void ModbusUART_EzI2CCyBtldrCommStart(void);
    void ModbusUART_EzI2CCyBtldrCommStop (void);
    void ModbusUART_EzI2CCyBtldrCommReset(void);
    cystatus ModbusUART_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
        #define ModbusUART_CyBtldrCommStart   ModbusUART_EzI2CCyBtldrCommStart
        #define ModbusUART_CyBtldrCommStop    ModbusUART_EzI2CCyBtldrCommStop
        #define ModbusUART_CyBtldrCommReset   ModbusUART_EzI2CCyBtldrCommReset
        #define ModbusUART_CyBtldrCommRead    ModbusUART_EzI2CCyBtldrCommRead
        #define ModbusUART_CyBtldrCommWrite   ModbusUART_EzI2CCyBtldrCommWrite
    #endif /* (ModbusUART_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void ModbusUART_SpiCyBtldrCommStart(void);
    void ModbusUART_SpiCyBtldrCommStop (void);
    void ModbusUART_SpiCyBtldrCommReset(void);
    cystatus ModbusUART_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (ModbusUART_SCB_MODE_SPI_CONST_CFG)
        #define ModbusUART_CyBtldrCommStart   ModbusUART_SpiCyBtldrCommStart
        #define ModbusUART_CyBtldrCommStop    ModbusUART_SpiCyBtldrCommStop
        #define ModbusUART_CyBtldrCommReset   ModbusUART_SpiCyBtldrCommReset
        #define ModbusUART_CyBtldrCommRead    ModbusUART_SpiCyBtldrCommRead
        #define ModbusUART_CyBtldrCommWrite   ModbusUART_SpiCyBtldrCommWrite
    #endif /* (ModbusUART_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void ModbusUART_UartCyBtldrCommStart(void);
    void ModbusUART_UartCyBtldrCommStop (void);
    void ModbusUART_UartCyBtldrCommReset(void);
    cystatus ModbusUART_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus ModbusUART_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (ModbusUART_SCB_MODE_UART_CONST_CFG)
        #define ModbusUART_CyBtldrCommStart   ModbusUART_UartCyBtldrCommStart
        #define ModbusUART_CyBtldrCommStop    ModbusUART_UartCyBtldrCommStop
        #define ModbusUART_CyBtldrCommReset   ModbusUART_UartCyBtldrCommReset
        #define ModbusUART_CyBtldrCommRead    ModbusUART_UartCyBtldrCommRead
        #define ModbusUART_CyBtldrCommWrite   ModbusUART_UartCyBtldrCommWrite
    #endif /* (ModbusUART_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_BTLDR_COMM_ENABLED)
    #if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void ModbusUART_CyBtldrCommStart(void);
        void ModbusUART_CyBtldrCommStop (void);
        void ModbusUART_CyBtldrCommReset(void);
        cystatus ModbusUART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus ModbusUART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART)
        #define CyBtldrCommStart    ModbusUART_CyBtldrCommStart
        #define CyBtldrCommStop     ModbusUART_CyBtldrCommStop
        #define CyBtldrCommReset    ModbusUART_CyBtldrCommReset
        #define CyBtldrCommWrite    ModbusUART_CyBtldrCommWrite
        #define CyBtldrCommRead     ModbusUART_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ModbusUART) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (ModbusUART_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define ModbusUART_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define ModbusUART_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define ModbusUART_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define ModbusUART_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef ModbusUART_SPI_BYTE_TO_BYTE
    #define ModbusUART_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef ModbusUART_UART_BYTE_TO_BYTE
    #define ModbusUART_UART_BYTE_TO_BYTE  (2084u)
#endif /* ModbusUART_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_ModbusUART_H) */


/* [] END OF FILE */
