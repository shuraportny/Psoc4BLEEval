/***************************************************************************//**
* \file ModbusUART_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_ModbusUART_H)
#define CY_SCB_SPI_UART_PVT_ModbusUART_H

#include "ModbusUART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  ModbusUART_rxBufferHead;
    extern volatile uint32  ModbusUART_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   ModbusUART_rxBufferOverflow;
    /** @} globals */
#endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

#if (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  ModbusUART_txBufferHead;
    extern volatile uint32  ModbusUART_txBufferTail;
#endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

#if (ModbusUART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 ModbusUART_rxBufferInternal[ModbusUART_INTERNAL_RX_BUFFER_SIZE];
#endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER) */

#if (ModbusUART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 ModbusUART_txBufferInternal[ModbusUART_TX_BUFFER_SIZE];
#endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void ModbusUART_SpiPostEnable(void);
void ModbusUART_SpiStop(void);

#if (ModbusUART_SCB_MODE_SPI_CONST_CFG)
    void ModbusUART_SpiInit(void);
#endif /* (ModbusUART_SCB_MODE_SPI_CONST_CFG) */

#if (ModbusUART_SPI_WAKE_ENABLE_CONST)
    void ModbusUART_SpiSaveConfig(void);
    void ModbusUART_SpiRestoreConfig(void);
#endif /* (ModbusUART_SPI_WAKE_ENABLE_CONST) */

void ModbusUART_UartPostEnable(void);
void ModbusUART_UartStop(void);

#if (ModbusUART_SCB_MODE_UART_CONST_CFG)
    void ModbusUART_UartInit(void);
#endif /* (ModbusUART_SCB_MODE_UART_CONST_CFG) */

#if (ModbusUART_UART_WAKE_ENABLE_CONST)
    void ModbusUART_UartSaveConfig(void);
    void ModbusUART_UartRestoreConfig(void);
#endif /* (ModbusUART_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in ModbusUART_SetPins() */
#define ModbusUART_UART_RX_PIN_ENABLE    (ModbusUART_UART_RX)
#define ModbusUART_UART_TX_PIN_ENABLE    (ModbusUART_UART_TX)

/* UART RTS and CTS position to be used in  ModbusUART_SetPins() */
#define ModbusUART_UART_RTS_PIN_ENABLE    (0x10u)
#define ModbusUART_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define ModbusUART_SpiUartEnableIntRx(intSourceMask)  ModbusUART_SetRxInterruptMode(intSourceMask)
#define ModbusUART_SpiUartEnableIntTx(intSourceMask)  ModbusUART_SetTxInterruptMode(intSourceMask)
uint32  ModbusUART_SpiUartDisableIntRx(void);
uint32  ModbusUART_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_ModbusUART_H) */


/* [] END OF FILE */
