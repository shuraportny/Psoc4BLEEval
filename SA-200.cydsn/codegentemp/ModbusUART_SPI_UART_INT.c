/***************************************************************************//**
* \file ModbusUART_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ModbusUART_PVT.h"
#include "ModbusUART_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (ModbusUART_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: ModbusUART_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(ModbusUART_SPI_UART_ISR)
{
#if (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

#if (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef ModbusUART_SPI_UART_ISR_ENTRY_CALLBACK
    ModbusUART_SPI_UART_ISR_EntryCallback();
#endif /* ModbusUART_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != ModbusUART_customIntrHandler)
    {
        ModbusUART_customIntrHandler();
    }

    #if(ModbusUART_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        ModbusUART_ClearSpiExtClkInterruptSource(ModbusUART_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (ModbusUART_CHECK_RX_SW_BUFFER)
    {
        if (ModbusUART_CHECK_INTR_RX_MASKED(ModbusUART_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (ModbusUART_rxBufferHead + 1u);

                /* Adjust local head index */
                if (ModbusUART_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == ModbusUART_rxBufferTail)
                {
                    #if (ModbusUART_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        ModbusUART_INTR_RX_MASK_REG &= ~ModbusUART_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) ModbusUART_RX_FIFO_RD_REG;
                        ModbusUART_rxBufferOverflow = (uint8) ModbusUART_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    ModbusUART_PutWordInRxBuffer(locHead, ModbusUART_RX_FIFO_RD_REG);

                    /* Move head index */
                    ModbusUART_rxBufferHead = locHead;
                }
            }
            while(0u != ModbusUART_GET_RX_FIFO_ENTRIES);

            ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (ModbusUART_CHECK_TX_SW_BUFFER)
    {
        if (ModbusUART_CHECK_INTR_TX_MASKED(ModbusUART_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (ModbusUART_txBufferHead != ModbusUART_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (ModbusUART_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (ModbusUART_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    ModbusUART_TX_FIFO_WR_REG = ModbusUART_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    ModbusUART_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    ModbusUART_DISABLE_INTR_TX(ModbusUART_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (ModbusUART_SPI_UART_FIFO_SIZE != ModbusUART_GET_TX_FIFO_ENTRIES);

            ModbusUART_ClearTxInterruptSource(ModbusUART_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef ModbusUART_SPI_UART_ISR_EXIT_CALLBACK
    ModbusUART_SPI_UART_ISR_ExitCallback();
#endif /* ModbusUART_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
