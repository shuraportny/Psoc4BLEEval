/*******************************************************************************
* File Name: RS232UARTINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RS232UART.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (RS232UART_RX_INTERRUPT_ENABLED && (RS232UART_RX_ENABLED || RS232UART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: RS232UART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  RS232UART_rxBuffer - RAM buffer pointer for save received data.
    *  RS232UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  RS232UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  RS232UART_rxBufferOverflow - software overflow flag. Set to one
    *     when RS232UART_rxBufferWrite index overtakes
    *     RS232UART_rxBufferRead index.
    *  RS232UART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when RS232UART_rxBufferWrite is equal to
    *    RS232UART_rxBufferRead
    *  RS232UART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  RS232UART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(RS232UART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef RS232UART_RXISR_ENTRY_CALLBACK
        RS232UART_RXISR_EntryCallback();
    #endif /* RS232UART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START RS232UART_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = RS232UART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in RS232UART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (RS232UART_RX_STS_BREAK | 
                            RS232UART_RX_STS_PAR_ERROR |
                            RS232UART_RX_STS_STOP_ERROR | 
                            RS232UART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                RS232UART_errorStatus |= readStatus & ( RS232UART_RX_STS_BREAK | 
                                                            RS232UART_RX_STS_PAR_ERROR | 
                                                            RS232UART_RX_STS_STOP_ERROR | 
                                                            RS232UART_RX_STS_OVERRUN);
                /* `#START RS232UART_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef RS232UART_RXISR_ERROR_CALLBACK
                RS232UART_RXISR_ERROR_Callback();
            #endif /* RS232UART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & RS232UART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = RS232UART_RXDATA_REG;
            #if (RS232UART_RXHW_ADDRESS_ENABLED)
                if(RS232UART_rxAddressMode == (uint8)RS232UART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & RS232UART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & RS232UART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            RS232UART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            RS232UART_rxAddressDetected = 0u;
                        }
                    }
                    if(RS232UART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        RS232UART_rxBuffer[RS232UART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    RS232UART_rxBuffer[RS232UART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                RS232UART_rxBuffer[RS232UART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (RS232UART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(RS232UART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        RS232UART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    RS232UART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(RS232UART_rxBufferWrite >= RS232UART_RX_BUFFER_SIZE)
                    {
                        RS232UART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(RS232UART_rxBufferWrite == RS232UART_rxBufferRead)
                    {
                        RS232UART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (RS232UART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            RS232UART_RXSTATUS_MASK_REG  &= (uint8)~RS232UART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(RS232UART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (RS232UART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & RS232UART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START RS232UART_RXISR_END` */

        /* `#END` */

    #ifdef RS232UART_RXISR_EXIT_CALLBACK
        RS232UART_RXISR_ExitCallback();
    #endif /* RS232UART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (RS232UART_RX_INTERRUPT_ENABLED && (RS232UART_RX_ENABLED || RS232UART_HD_ENABLED)) */


#if (RS232UART_TX_INTERRUPT_ENABLED && RS232UART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: RS232UART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  RS232UART_txBuffer - RAM buffer pointer for transmit data from.
    *  RS232UART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  RS232UART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(RS232UART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef RS232UART_TXISR_ENTRY_CALLBACK
        RS232UART_TXISR_EntryCallback();
    #endif /* RS232UART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START RS232UART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((RS232UART_txBufferRead != RS232UART_txBufferWrite) &&
             ((RS232UART_TXSTATUS_REG & RS232UART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(RS232UART_txBufferRead >= RS232UART_TX_BUFFER_SIZE)
            {
                RS232UART_txBufferRead = 0u;
            }

            RS232UART_TXDATA_REG = RS232UART_txBuffer[RS232UART_txBufferRead];

            /* Set next pointer */
            RS232UART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START RS232UART_TXISR_END` */

        /* `#END` */

    #ifdef RS232UART_TXISR_EXIT_CALLBACK
        RS232UART_TXISR_ExitCallback();
    #endif /* RS232UART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (RS232UART_TX_INTERRUPT_ENABLED && RS232UART_TX_ENABLED) */


/* [] END OF FILE */
