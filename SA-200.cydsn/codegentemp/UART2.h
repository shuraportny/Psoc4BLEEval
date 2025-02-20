/*******************************************************************************
* File Name: UART2.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_UART2_H)
#define CY_UART_UART2_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UART2_RX_ENABLED                     (1u)
#define UART2_TX_ENABLED                     (1u)
#define UART2_HD_ENABLED                     (0u)
#define UART2_RX_INTERRUPT_ENABLED           (1u)
#define UART2_TX_INTERRUPT_ENABLED           (0u)
#define UART2_INTERNAL_CLOCK_USED            (1u)
#define UART2_RXHW_ADDRESS_ENABLED           (0u)
#define UART2_OVER_SAMPLE_COUNT              (8u)
#define UART2_PARITY_TYPE                    (0u)
#define UART2_PARITY_TYPE_SW                 (0u)
#define UART2_BREAK_DETECT                   (0u)
#define UART2_BREAK_BITS_TX                  (13u)
#define UART2_BREAK_BITS_RX                  (13u)
#define UART2_TXCLKGEN_DP                    (1u)
#define UART2_USE23POLLING                   (1u)
#define UART2_FLOW_CONTROL                   (0u)
#define UART2_CLK_FREQ                       (0u)
#define UART2_TX_BUFFER_SIZE                 (4u)
#define UART2_RX_BUFFER_SIZE                 (8u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(UART2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define UART2_CONTROL_REG_REMOVED            (0u)
#else
    #define UART2_CONTROL_REG_REMOVED            (1u)
#endif /* End UART2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UART2_backupStruct_
{
    uint8 enableState;

    #if(UART2_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UART2_CONTROL_REG_REMOVED */

} UART2_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UART2_Start(void) ;
void UART2_Stop(void) ;
uint8 UART2_ReadControlRegister(void) ;
void UART2_WriteControlRegister(uint8 control) ;

void UART2_Init(void) ;
void UART2_Enable(void) ;
void UART2_SaveConfig(void) ;
void UART2_RestoreConfig(void) ;
void UART2_Sleep(void) ;
void UART2_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UART2_RX_ENABLED) || (UART2_HD_ENABLED) )

    #if (UART2_RX_INTERRUPT_ENABLED)
        #define UART2_EnableRxInt()  CyIntEnable (UART2_RX_VECT_NUM)
        #define UART2_DisableRxInt() CyIntDisable(UART2_RX_VECT_NUM)
        CY_ISR_PROTO(UART2_RXISR);
    #endif /* UART2_RX_INTERRUPT_ENABLED */

    void UART2_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UART2_SetRxAddress1(uint8 address) ;
    void UART2_SetRxAddress2(uint8 address) ;

    void  UART2_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UART2_ReadRxData(void) ;
    uint8 UART2_ReadRxStatus(void) ;
    uint8 UART2_GetChar(void) ;
    uint16 UART2_GetByte(void) ;
    uint8 UART2_GetRxBufferSize(void)
                                                            ;
    void UART2_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UART2_GetRxInterruptSource   UART2_ReadRxStatus

#endif /* End (UART2_RX_ENABLED) || (UART2_HD_ENABLED) */

/* Only if TX is enabled */
#if(UART2_TX_ENABLED || UART2_HD_ENABLED)

    #if(UART2_TX_INTERRUPT_ENABLED)
        #define UART2_EnableTxInt()  CyIntEnable (UART2_TX_VECT_NUM)
        #define UART2_DisableTxInt() CyIntDisable(UART2_TX_VECT_NUM)
        #define UART2_SetPendingTxInt() CyIntSetPending(UART2_TX_VECT_NUM)
        #define UART2_ClearPendingTxInt() CyIntClearPending(UART2_TX_VECT_NUM)
        CY_ISR_PROTO(UART2_TXISR);
    #endif /* UART2_TX_INTERRUPT_ENABLED */

    void UART2_SetTxInterruptMode(uint8 intSrc) ;
    void UART2_WriteTxData(uint8 txDataByte) ;
    uint8 UART2_ReadTxStatus(void) ;
    void UART2_PutChar(uint8 txDataByte) ;
    void UART2_PutString(const char8 string[]) ;
    void UART2_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UART2_PutCRLF(uint8 txDataByte) ;
    void UART2_ClearTxBuffer(void) ;
    void UART2_SetTxAddressMode(uint8 addressMode) ;
    void UART2_SendBreak(uint8 retMode) ;
    uint8 UART2_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UART2_PutStringConst         UART2_PutString
    #define UART2_PutArrayConst          UART2_PutArray
    #define UART2_GetTxInterruptSource   UART2_ReadTxStatus

#endif /* End UART2_TX_ENABLED || UART2_HD_ENABLED */

#if(UART2_HD_ENABLED)
    void UART2_LoadRxConfig(void) ;
    void UART2_LoadTxConfig(void) ;
#endif /* End UART2_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UART2_CyBtldrCommStart(void) CYSMALL ;
    void    UART2_CyBtldrCommStop(void) CYSMALL ;
    void    UART2_CyBtldrCommReset(void) CYSMALL ;
    cystatus UART2_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UART2_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2)
        #define CyBtldrCommStart    UART2_CyBtldrCommStart
        #define CyBtldrCommStop     UART2_CyBtldrCommStop
        #define CyBtldrCommReset    UART2_CyBtldrCommReset
        #define CyBtldrCommWrite    UART2_CyBtldrCommWrite
        #define CyBtldrCommRead     UART2_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART2) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UART2_BYTE2BYTE_TIME_OUT (25u)
    #define UART2_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define UART2_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define UART2_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UART2_SET_SPACE      (0x00u)
#define UART2_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (UART2_TX_ENABLED) || (UART2_HD_ENABLED) )
    #if(UART2_TX_INTERRUPT_ENABLED)
        #define UART2_TX_VECT_NUM            (uint8)UART2_TXInternalInterrupt__INTC_NUMBER
        #define UART2_TX_PRIOR_NUM           (uint8)UART2_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART2_TX_INTERRUPT_ENABLED */

    #define UART2_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define UART2_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define UART2_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(UART2_TX_ENABLED)
        #define UART2_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (UART2_HD_ENABLED) */
        #define UART2_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (UART2_TX_ENABLED) */

    #define UART2_TX_STS_COMPLETE            (uint8)(0x01u << UART2_TX_STS_COMPLETE_SHIFT)
    #define UART2_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UART2_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART2_TX_STS_FIFO_FULL           (uint8)(0x01u << UART2_TX_STS_FIFO_FULL_SHIFT)
    #define UART2_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UART2_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UART2_TX_ENABLED) || (UART2_HD_ENABLED)*/

#if( (UART2_RX_ENABLED) || (UART2_HD_ENABLED) )
    #if(UART2_RX_INTERRUPT_ENABLED)
        #define UART2_RX_VECT_NUM            (uint8)UART2_RXInternalInterrupt__INTC_NUMBER
        #define UART2_RX_PRIOR_NUM           (uint8)UART2_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART2_RX_INTERRUPT_ENABLED */
    #define UART2_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UART2_RX_STS_BREAK_SHIFT             (0x01u)
    #define UART2_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UART2_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UART2_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UART2_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UART2_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UART2_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UART2_RX_STS_MRKSPC           (uint8)(0x01u << UART2_RX_STS_MRKSPC_SHIFT)
    #define UART2_RX_STS_BREAK            (uint8)(0x01u << UART2_RX_STS_BREAK_SHIFT)
    #define UART2_RX_STS_PAR_ERROR        (uint8)(0x01u << UART2_RX_STS_PAR_ERROR_SHIFT)
    #define UART2_RX_STS_STOP_ERROR       (uint8)(0x01u << UART2_RX_STS_STOP_ERROR_SHIFT)
    #define UART2_RX_STS_OVERRUN          (uint8)(0x01u << UART2_RX_STS_OVERRUN_SHIFT)
    #define UART2_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UART2_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART2_RX_STS_ADDR_MATCH       (uint8)(0x01u << UART2_RX_STS_ADDR_MATCH_SHIFT)
    #define UART2_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UART2_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UART2_RX_HW_MASK                     (0x7Fu)
#endif /* End (UART2_RX_ENABLED) || (UART2_HD_ENABLED) */

/* Control Register definitions */
#define UART2_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UART2_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UART2_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UART2_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UART2_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UART2_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UART2_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UART2_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UART2_CTRL_HD_SEND               (uint8)(0x01u << UART2_CTRL_HD_SEND_SHIFT)
#define UART2_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UART2_CTRL_HD_SEND_BREAK_SHIFT)
#define UART2_CTRL_MARK                  (uint8)(0x01u << UART2_CTRL_MARK_SHIFT)
#define UART2_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UART2_CTRL_PARITY_TYPE0_SHIFT)
#define UART2_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UART2_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UART2_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UART2_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UART2_SEND_BREAK                         (0x00u)
#define UART2_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UART2_REINIT                             (0x02u)
#define UART2_SEND_WAIT_REINIT                   (0x03u)

#define UART2_OVER_SAMPLE_8                      (8u)
#define UART2_OVER_SAMPLE_16                     (16u)

#define UART2_BIT_CENTER                         (UART2_OVER_SAMPLE_COUNT - 2u)

#define UART2_FIFO_LENGTH                        (4u)
#define UART2_NUMBER_OF_START_BIT                (1u)
#define UART2_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define UART2_TXBITCTR_BREAKBITS8X   ((UART2_BREAK_BITS_TX * UART2_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define UART2_TXBITCTR_BREAKBITS ((UART2_BREAK_BITS_TX * UART2_OVER_SAMPLE_COUNT) - 1u)

#define UART2_HALF_BIT_COUNT   \
                            (((UART2_OVER_SAMPLE_COUNT / 2u) + (UART2_USE23POLLING * 1u)) - 2u)
#if (UART2_OVER_SAMPLE_COUNT == UART2_OVER_SAMPLE_8)
    #define UART2_HD_TXBITCTR_INIT   (((UART2_BREAK_BITS_TX + \
                            UART2_NUMBER_OF_START_BIT) * UART2_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UART2_RXBITCTR_INIT  ((((UART2_BREAK_BITS_RX + UART2_NUMBER_OF_START_BIT) \
                            * UART2_OVER_SAMPLE_COUNT) + UART2_HALF_BIT_COUNT) - 1u)

#else /* UART2_OVER_SAMPLE_COUNT == UART2_OVER_SAMPLE_16 */
    #define UART2_HD_TXBITCTR_INIT   ((8u * UART2_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define UART2_RXBITCTR_INIT      (((7u * UART2_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UART2_HALF_BIT_COUNT)
#endif /* End UART2_OVER_SAMPLE_COUNT */

#define UART2_HD_RXBITCTR_INIT                   UART2_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UART2_initVar;
#if (UART2_TX_INTERRUPT_ENABLED && UART2_TX_ENABLED)
    extern volatile uint8 UART2_txBuffer[UART2_TX_BUFFER_SIZE];
    extern volatile uint8 UART2_txBufferRead;
    extern uint8 UART2_txBufferWrite;
#endif /* (UART2_TX_INTERRUPT_ENABLED && UART2_TX_ENABLED) */
#if (UART2_RX_INTERRUPT_ENABLED && (UART2_RX_ENABLED || UART2_HD_ENABLED))
    extern uint8 UART2_errorStatus;
    extern volatile uint8 UART2_rxBuffer[UART2_RX_BUFFER_SIZE];
    extern volatile uint8 UART2_rxBufferRead;
    extern volatile uint8 UART2_rxBufferWrite;
    extern volatile uint8 UART2_rxBufferLoopDetect;
    extern volatile uint8 UART2_rxBufferOverflow;
    #if (UART2_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UART2_rxAddressMode;
        extern volatile uint8 UART2_rxAddressDetected;
    #endif /* (UART2_RXHW_ADDRESS_ENABLED) */
#endif /* (UART2_RX_INTERRUPT_ENABLED && (UART2_RX_ENABLED || UART2_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART2__B_UART__AM_SW_BYTE_BYTE 1
#define UART2__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART2__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART2__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART2__B_UART__AM_NONE 0

#define UART2__B_UART__NONE_REVB 0
#define UART2__B_UART__EVEN_REVB 1
#define UART2__B_UART__ODD_REVB 2
#define UART2__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UART2_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UART2_NUMBER_OF_STOP_BITS    (1u)

#if (UART2_RXHW_ADDRESS_ENABLED)
    #define UART2_RX_ADDRESS_MODE    (0u)
    #define UART2_RX_HW_ADDRESS1     (0u)
    #define UART2_RX_HW_ADDRESS2     (0u)
#endif /* (UART2_RXHW_ADDRESS_ENABLED) */

#define UART2_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << UART2_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UART2_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UART2_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UART2_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UART2_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UART2_RX_STS_BREAK_SHIFT) \
                                        | (0 << UART2_RX_STS_OVERRUN_SHIFT))

#define UART2_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << UART2_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << UART2_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UART2_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UART2_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UART2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART2_CONTROL_REG \
                            (* (reg8 *) UART2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UART2_CONTROL_PTR \
                            (  (reg8 *) UART2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UART2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART2_TX_ENABLED)
    #define UART2_TXDATA_REG          (* (reg8 *) UART2_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART2_TXDATA_PTR          (  (reg8 *) UART2_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART2_TXDATA_AUX_CTL_REG  (* (reg8 *) UART2_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART2_TXDATA_AUX_CTL_PTR  (  (reg8 *) UART2_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART2_TXSTATUS_REG        (* (reg8 *) UART2_BUART_sTX_TxSts__STATUS_REG)
    #define UART2_TXSTATUS_PTR        (  (reg8 *) UART2_BUART_sTX_TxSts__STATUS_REG)
    #define UART2_TXSTATUS_MASK_REG   (* (reg8 *) UART2_BUART_sTX_TxSts__MASK_REG)
    #define UART2_TXSTATUS_MASK_PTR   (  (reg8 *) UART2_BUART_sTX_TxSts__MASK_REG)
    #define UART2_TXSTATUS_ACTL_REG   (* (reg8 *) UART2_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UART2_TXSTATUS_ACTL_PTR   (  (reg8 *) UART2_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UART2_TXCLKGEN_DP)
        #define UART2_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART2_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART2_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UART2_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UART2_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART2_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART2_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART2_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART2_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UART2_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UART2_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UART2_TXCLKGEN_DP */

#endif /* End UART2_TX_ENABLED */

#if(UART2_HD_ENABLED)

    #define UART2_TXDATA_REG             (* (reg8 *) UART2_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART2_TXDATA_PTR             (  (reg8 *) UART2_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART2_TXDATA_AUX_CTL_REG     (* (reg8 *) UART2_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UART2_TXDATA_AUX_CTL_PTR     (  (reg8 *) UART2_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART2_TXSTATUS_REG           (* (reg8 *) UART2_BUART_sRX_RxSts__STATUS_REG )
    #define UART2_TXSTATUS_PTR           (  (reg8 *) UART2_BUART_sRX_RxSts__STATUS_REG )
    #define UART2_TXSTATUS_MASK_REG      (* (reg8 *) UART2_BUART_sRX_RxSts__MASK_REG )
    #define UART2_TXSTATUS_MASK_PTR      (  (reg8 *) UART2_BUART_sRX_RxSts__MASK_REG )
    #define UART2_TXSTATUS_ACTL_REG      (* (reg8 *) UART2_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART2_TXSTATUS_ACTL_PTR      (  (reg8 *) UART2_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UART2_HD_ENABLED */

#if( (UART2_RX_ENABLED) || (UART2_HD_ENABLED) )
    #define UART2_RXDATA_REG             (* (reg8 *) UART2_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART2_RXDATA_PTR             (  (reg8 *) UART2_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART2_RXADDRESS1_REG         (* (reg8 *) UART2_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART2_RXADDRESS1_PTR         (  (reg8 *) UART2_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART2_RXADDRESS2_REG         (* (reg8 *) UART2_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART2_RXADDRESS2_PTR         (  (reg8 *) UART2_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART2_RXDATA_AUX_CTL_REG     (* (reg8 *) UART2_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART2_RXBITCTR_PERIOD_REG    (* (reg8 *) UART2_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART2_RXBITCTR_PERIOD_PTR    (  (reg8 *) UART2_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART2_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART2_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART2_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART2_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART2_RXBITCTR_COUNTER_REG   (* (reg8 *) UART2_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UART2_RXBITCTR_COUNTER_PTR   (  (reg8 *) UART2_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UART2_RXSTATUS_REG           (* (reg8 *) UART2_BUART_sRX_RxSts__STATUS_REG )
    #define UART2_RXSTATUS_PTR           (  (reg8 *) UART2_BUART_sRX_RxSts__STATUS_REG )
    #define UART2_RXSTATUS_MASK_REG      (* (reg8 *) UART2_BUART_sRX_RxSts__MASK_REG )
    #define UART2_RXSTATUS_MASK_PTR      (  (reg8 *) UART2_BUART_sRX_RxSts__MASK_REG )
    #define UART2_RXSTATUS_ACTL_REG      (* (reg8 *) UART2_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART2_RXSTATUS_ACTL_PTR      (  (reg8 *) UART2_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UART2_RX_ENABLED) || (UART2_HD_ENABLED) */

#if(UART2_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UART2_INTCLOCK_CLKEN_REG     (* (reg8 *) UART2_IntClock__PM_ACT_CFG)
    #define UART2_INTCLOCK_CLKEN_PTR     (  (reg8 *) UART2_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UART2_INTCLOCK_CLKEN_MASK    UART2_IntClock__PM_ACT_MSK
#endif /* End UART2_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UART2_TX_ENABLED)
    #define UART2_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UART2_TX_ENABLED */

#if(UART2_HD_ENABLED)
    #define UART2_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UART2_HD_ENABLED */

#if( (UART2_RX_ENABLED) || (UART2_HD_ENABLED) )
    #define UART2_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UART2_RX_ENABLED) || (UART2_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define UART2_WAIT_1_MS      UART2_BL_CHK_DELAY_MS   

#define UART2_TXBUFFERSIZE   UART2_TX_BUFFER_SIZE
#define UART2_RXBUFFERSIZE   UART2_RX_BUFFER_SIZE

#if (UART2_RXHW_ADDRESS_ENABLED)
    #define UART2_RXADDRESSMODE  UART2_RX_ADDRESS_MODE
    #define UART2_RXHWADDRESS1   UART2_RX_HW_ADDRESS1
    #define UART2_RXHWADDRESS2   UART2_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define UART2_RXAddressMode  UART2_RXADDRESSMODE
#endif /* (UART2_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define UART2_initvar                    UART2_initVar

#define UART2_RX_Enabled                 UART2_RX_ENABLED
#define UART2_TX_Enabled                 UART2_TX_ENABLED
#define UART2_HD_Enabled                 UART2_HD_ENABLED
#define UART2_RX_IntInterruptEnabled     UART2_RX_INTERRUPT_ENABLED
#define UART2_TX_IntInterruptEnabled     UART2_TX_INTERRUPT_ENABLED
#define UART2_InternalClockUsed          UART2_INTERNAL_CLOCK_USED
#define UART2_RXHW_Address_Enabled       UART2_RXHW_ADDRESS_ENABLED
#define UART2_OverSampleCount            UART2_OVER_SAMPLE_COUNT
#define UART2_ParityType                 UART2_PARITY_TYPE

#if( UART2_TX_ENABLED && (UART2_TXBUFFERSIZE > UART2_FIFO_LENGTH))
    #define UART2_TXBUFFER               UART2_txBuffer
    #define UART2_TXBUFFERREAD           UART2_txBufferRead
    #define UART2_TXBUFFERWRITE          UART2_txBufferWrite
#endif /* End UART2_TX_ENABLED */
#if( ( UART2_RX_ENABLED || UART2_HD_ENABLED ) && \
     (UART2_RXBUFFERSIZE > UART2_FIFO_LENGTH) )
    #define UART2_RXBUFFER               UART2_rxBuffer
    #define UART2_RXBUFFERREAD           UART2_rxBufferRead
    #define UART2_RXBUFFERWRITE          UART2_rxBufferWrite
    #define UART2_RXBUFFERLOOPDETECT     UART2_rxBufferLoopDetect
    #define UART2_RXBUFFER_OVERFLOW      UART2_rxBufferOverflow
#endif /* End UART2_RX_ENABLED */

#ifdef UART2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART2_CONTROL                UART2_CONTROL_REG
#endif /* End UART2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART2_TX_ENABLED)
    #define UART2_TXDATA                 UART2_TXDATA_REG
    #define UART2_TXSTATUS               UART2_TXSTATUS_REG
    #define UART2_TXSTATUS_MASK          UART2_TXSTATUS_MASK_REG
    #define UART2_TXSTATUS_ACTL          UART2_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UART2_TXCLKGEN_DP)
        #define UART2_TXBITCLKGEN_CTR        UART2_TXBITCLKGEN_CTR_REG
        #define UART2_TXBITCLKTX_COMPLETE    UART2_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UART2_TXBITCTR_PERIOD        UART2_TXBITCTR_PERIOD_REG
        #define UART2_TXBITCTR_CONTROL       UART2_TXBITCTR_CONTROL_REG
        #define UART2_TXBITCTR_COUNTER       UART2_TXBITCTR_COUNTER_REG
    #endif /* UART2_TXCLKGEN_DP */
#endif /* End UART2_TX_ENABLED */

#if(UART2_HD_ENABLED)
    #define UART2_TXDATA                 UART2_TXDATA_REG
    #define UART2_TXSTATUS               UART2_TXSTATUS_REG
    #define UART2_TXSTATUS_MASK          UART2_TXSTATUS_MASK_REG
    #define UART2_TXSTATUS_ACTL          UART2_TXSTATUS_ACTL_REG
#endif /* End UART2_HD_ENABLED */

#if( (UART2_RX_ENABLED) || (UART2_HD_ENABLED) )
    #define UART2_RXDATA                 UART2_RXDATA_REG
    #define UART2_RXADDRESS1             UART2_RXADDRESS1_REG
    #define UART2_RXADDRESS2             UART2_RXADDRESS2_REG
    #define UART2_RXBITCTR_PERIOD        UART2_RXBITCTR_PERIOD_REG
    #define UART2_RXBITCTR_CONTROL       UART2_RXBITCTR_CONTROL_REG
    #define UART2_RXBITCTR_COUNTER       UART2_RXBITCTR_COUNTER_REG
    #define UART2_RXSTATUS               UART2_RXSTATUS_REG
    #define UART2_RXSTATUS_MASK          UART2_RXSTATUS_MASK_REG
    #define UART2_RXSTATUS_ACTL          UART2_RXSTATUS_ACTL_REG
#endif /* End  (UART2_RX_ENABLED) || (UART2_HD_ENABLED) */

#if(UART2_INTERNAL_CLOCK_USED)
    #define UART2_INTCLOCK_CLKEN         UART2_INTCLOCK_CLKEN_REG
#endif /* End UART2_INTERNAL_CLOCK_USED */

#define UART2_WAIT_FOR_COMLETE_REINIT    UART2_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UART2_H */


/* [] END OF FILE */
