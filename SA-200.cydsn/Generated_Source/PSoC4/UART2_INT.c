/*******************************************************************************
* File Name: UART2INT.c
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

#include "UART2.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (UART2_RX_INTERRUPT_ENABLED && (UART2_RX_ENABLED || UART2_HD_ENABLED))
    /*******************************************************************************
    * Function Name: UART2_RXISR
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
    *  UART2_rxBuffer - RAM buffer pointer for save received data.
    *  UART2_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART2_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART2_rxBufferOverflow - software overflow flag. Set to one
    *     when UART2_rxBufferWrite index overtakes
    *     UART2_rxBufferRead index.
    *  UART2_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART2_rxBufferWrite is equal to
    *    UART2_rxBufferRead
    *  UART2_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART2_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART2_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef UART2_RXISR_ENTRY_CALLBACK
        UART2_RXISR_EntryCallback();
    #endif /* UART2_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START UART2_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = UART2_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in UART2_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (UART2_RX_STS_BREAK | 
                            UART2_RX_STS_PAR_ERROR |
                            UART2_RX_STS_STOP_ERROR | 
                            UART2_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                UART2_errorStatus |= readStatus & ( UART2_RX_STS_BREAK | 
                                                            UART2_RX_STS_PAR_ERROR | 
                                                            UART2_RX_STS_STOP_ERROR | 
                                                            UART2_RX_STS_OVERRUN);
                /* `#START UART2_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef UART2_RXISR_ERROR_CALLBACK
                UART2_RXISR_ERROR_Callback();
            #endif /* UART2_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & UART2_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = UART2_RXDATA_REG;
            #if (UART2_RXHW_ADDRESS_ENABLED)
                if(UART2_rxAddressMode == (uint8)UART2__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & UART2_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & UART2_RX_STS_ADDR_MATCH) != 0u)
                        {
                            UART2_rxAddressDetected = 1u;
                        }
                        else
                        {
                            UART2_rxAddressDetected = 0u;
                        }
                    }
                    if(UART2_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        UART2_rxBuffer[UART2_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    UART2_rxBuffer[UART2_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                UART2_rxBuffer[UART2_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (UART2_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(UART2_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        UART2_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    UART2_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(UART2_rxBufferWrite >= UART2_RX_BUFFER_SIZE)
                    {
                        UART2_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(UART2_rxBufferWrite == UART2_rxBufferRead)
                    {
                        UART2_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (UART2_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            UART2_RXSTATUS_MASK_REG  &= (uint8)~UART2_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(UART2_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (UART2_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & UART2_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START UART2_RXISR_END` */

        /* `#END` */

    #ifdef UART2_RXISR_EXIT_CALLBACK
        UART2_RXISR_ExitCallback();
    #endif /* UART2_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (UART2_RX_INTERRUPT_ENABLED && (UART2_RX_ENABLED || UART2_HD_ENABLED)) */


#if (UART2_TX_INTERRUPT_ENABLED && UART2_TX_ENABLED)
    /*******************************************************************************
    * Function Name: UART2_TXISR
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
    *  UART2_txBuffer - RAM buffer pointer for transmit data from.
    *  UART2_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  UART2_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART2_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef UART2_TXISR_ENTRY_CALLBACK
        UART2_TXISR_EntryCallback();
    #endif /* UART2_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START UART2_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((UART2_txBufferRead != UART2_txBufferWrite) &&
             ((UART2_TXSTATUS_REG & UART2_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(UART2_txBufferRead >= UART2_TX_BUFFER_SIZE)
            {
                UART2_txBufferRead = 0u;
            }

            UART2_TXDATA_REG = UART2_txBuffer[UART2_txBufferRead];

            /* Set next pointer */
            UART2_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART2_TXISR_END` */

        /* `#END` */

    #ifdef UART2_TXISR_EXIT_CALLBACK
        UART2_TXISR_ExitCallback();
    #endif /* UART2_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (UART2_TX_INTERRUPT_ENABLED && UART2_TX_ENABLED) */


/* [] END OF FILE */
