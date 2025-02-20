/***************************************************************************//**
* \file ModbusUART_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ModbusUART_PVT.h"
#include "ModbusUART_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (ModbusUART_UART_WAKE_ENABLE_CONST && ModbusUART_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when ModbusUART_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 ModbusUART_skipStart = 1u;
    /** \} globals */
#endif /* (ModbusUART_UART_WAKE_ENABLE_CONST && ModbusUART_UART_RX_WAKEUP_IRQ) */

#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const ModbusUART_UART_INIT_STRUCT ModbusUART_configUart =
    {
        ModbusUART_UART_SUB_MODE,
        ModbusUART_UART_DIRECTION,
        ModbusUART_UART_DATA_BITS_NUM,
        ModbusUART_UART_PARITY_TYPE,
        ModbusUART_UART_STOP_BITS_NUM,
        ModbusUART_UART_OVS_FACTOR,
        ModbusUART_UART_IRDA_LOW_POWER,
        ModbusUART_UART_MEDIAN_FILTER_ENABLE,
        ModbusUART_UART_RETRY_ON_NACK,
        ModbusUART_UART_IRDA_POLARITY,
        ModbusUART_UART_DROP_ON_PARITY_ERR,
        ModbusUART_UART_DROP_ON_FRAME_ERR,
        ModbusUART_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        ModbusUART_UART_MP_MODE_ENABLE,
        ModbusUART_UART_MP_ACCEPT_ADDRESS,
        ModbusUART_UART_MP_RX_ADDRESS,
        ModbusUART_UART_MP_RX_ADDRESS_MASK,
        (uint32) ModbusUART_SCB_IRQ_INTERNAL,
        ModbusUART_UART_INTR_RX_MASK,
        ModbusUART_UART_RX_TRIGGER_LEVEL,
        ModbusUART_UART_INTR_TX_MASK,
        ModbusUART_UART_TX_TRIGGER_LEVEL,
        (uint8) ModbusUART_UART_BYTE_MODE_ENABLE,
        (uint8) ModbusUART_UART_CTS_ENABLE,
        (uint8) ModbusUART_UART_CTS_POLARITY,
        (uint8) ModbusUART_UART_RTS_POLARITY,
        (uint8) ModbusUART_UART_RTS_FIFO_LEVEL,
        (uint8) ModbusUART_UART_RX_BREAK_WIDTH
    };


    /*******************************************************************************
    * Function Name: ModbusUART_UartInit
    ****************************************************************************//**
    *
    *  Configures the ModbusUART for UART operation.
    *
    *  This function is intended specifically to be used when the ModbusUART
    *  configuration is set to “Unconfigured ModbusUART” in the customizer.
    *  After initializing the ModbusUART in UART mode using this function,
    *  the component can be enabled using the ModbusUART_Start() or
    * ModbusUART_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void ModbusUART_UartInit(const ModbusUART_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (ModbusUART_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (ModbusUART_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

            /* Configure pins */
            ModbusUART_SetPins(ModbusUART_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            ModbusUART_scbMode       = (uint8) ModbusUART_SCB_MODE_UART;
            ModbusUART_scbEnableWake = (uint8) config->enableWake;
            ModbusUART_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            ModbusUART_rxBuffer      =         config->rxBuffer;
            ModbusUART_rxDataBits    = (uint8) config->dataBits;
            ModbusUART_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            ModbusUART_txBuffer      =         config->txBuffer;
            ModbusUART_txDataBits    = (uint8) config->dataBits;
            ModbusUART_txBufferSize  =         config->txBufferSize;

            /* Configure UART interface */
            if(ModbusUART_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                ModbusUART_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (ModbusUART_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (ModbusUART_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                ModbusUART_CTRL_REG  = ModbusUART_GET_CTRL_OVS(config->oversample);
            }

            ModbusUART_CTRL_REG     |= ModbusUART_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             ModbusUART_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             ModbusUART_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            ModbusUART_UART_CTRL_REG = ModbusUART_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            ModbusUART_UART_RX_CTRL_REG = ModbusUART_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        ModbusUART_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        ModbusUART_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        ModbusUART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        ModbusUART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr)   |
                                        ModbusUART_GET_UART_RX_CTRL_BREAK_WIDTH(config->breakWidth);

            if(ModbusUART_UART_PARITY_NONE != config->parity)
            {
               ModbusUART_UART_RX_CTRL_REG |= ModbusUART_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    ModbusUART_UART_RX_CTRL_PARITY_ENABLED;
            }

            ModbusUART_RX_CTRL_REG      = ModbusUART_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                ModbusUART_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                ModbusUART_GET_UART_RX_CTRL_ENABLED(config->direction);

            ModbusUART_RX_FIFO_CTRL_REG = ModbusUART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            ModbusUART_RX_MATCH_REG     = ModbusUART_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                ModbusUART_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            ModbusUART_UART_TX_CTRL_REG = ModbusUART_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                ModbusUART_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(ModbusUART_UART_PARITY_NONE != config->parity)
            {
               ModbusUART_UART_TX_CTRL_REG |= ModbusUART_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    ModbusUART_UART_TX_CTRL_PARITY_ENABLED;
            }

            ModbusUART_TX_CTRL_REG      = ModbusUART_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                ModbusUART_GET_UART_TX_CTRL_ENABLED(config->direction);

            ModbusUART_TX_FIFO_CTRL_REG = ModbusUART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
            ModbusUART_UART_FLOW_CTRL_REG = ModbusUART_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            ModbusUART_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            ModbusUART_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            ModbusUART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (ModbusUART_ISR_NUMBER);
            CyIntSetPriority(ModbusUART_ISR_NUMBER, ModbusUART_ISR_PRIORITY);
            (void) CyIntSetVector(ModbusUART_ISR_NUMBER, &ModbusUART_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(ModbusUART_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (ModbusUART_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(ModbusUART_RX_WAKE_ISR_NUMBER, ModbusUART_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(ModbusUART_RX_WAKE_ISR_NUMBER, &ModbusUART_UART_WAKEUP_ISR);
        #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            ModbusUART_INTR_I2C_EC_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_SPI_EC_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_SLAVE_MASK_REG  = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_MASTER_MASK_REG = ModbusUART_NO_INTR_SOURCES;
            ModbusUART_INTR_RX_MASK_REG     = config->rxInterruptMask;
            ModbusUART_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Configure TX interrupt sources to restore. */
            ModbusUART_IntrTxMask = LO16(ModbusUART_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            ModbusUART_rxBufferHead     = 0u;
            ModbusUART_rxBufferTail     = 0u;
            ModbusUART_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            ModbusUART_txBufferHead = 0u;
            ModbusUART_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: ModbusUART_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void ModbusUART_UartInit(void)
    {
        /* Configure UART interface */
        ModbusUART_CTRL_REG = ModbusUART_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        ModbusUART_UART_CTRL_REG = ModbusUART_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        ModbusUART_UART_RX_CTRL_REG = ModbusUART_UART_DEFAULT_UART_RX_CTRL;
        ModbusUART_RX_CTRL_REG      = ModbusUART_UART_DEFAULT_RX_CTRL;
        ModbusUART_RX_FIFO_CTRL_REG = ModbusUART_UART_DEFAULT_RX_FIFO_CTRL;
        ModbusUART_RX_MATCH_REG     = ModbusUART_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        ModbusUART_UART_TX_CTRL_REG = ModbusUART_UART_DEFAULT_UART_TX_CTRL;
        ModbusUART_TX_CTRL_REG      = ModbusUART_UART_DEFAULT_TX_CTRL;
        ModbusUART_TX_FIFO_CTRL_REG = ModbusUART_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
        ModbusUART_UART_FLOW_CTRL_REG = ModbusUART_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(ModbusUART_SCB_IRQ_INTERNAL)
        CyIntDisable    (ModbusUART_ISR_NUMBER);
        CyIntSetPriority(ModbusUART_ISR_NUMBER, ModbusUART_ISR_PRIORITY);
        (void) CyIntSetVector(ModbusUART_ISR_NUMBER, &ModbusUART_SPI_UART_ISR);
    #endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(ModbusUART_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (ModbusUART_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(ModbusUART_RX_WAKE_ISR_NUMBER, ModbusUART_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(ModbusUART_RX_WAKE_ISR_NUMBER, &ModbusUART_UART_WAKEUP_ISR);
    #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        ModbusUART_INTR_I2C_EC_MASK_REG = ModbusUART_UART_DEFAULT_INTR_I2C_EC_MASK;
        ModbusUART_INTR_SPI_EC_MASK_REG = ModbusUART_UART_DEFAULT_INTR_SPI_EC_MASK;
        ModbusUART_INTR_SLAVE_MASK_REG  = ModbusUART_UART_DEFAULT_INTR_SLAVE_MASK;
        ModbusUART_INTR_MASTER_MASK_REG = ModbusUART_UART_DEFAULT_INTR_MASTER_MASK;
        ModbusUART_INTR_RX_MASK_REG     = ModbusUART_UART_DEFAULT_INTR_RX_MASK;
        ModbusUART_INTR_TX_MASK_REG     = ModbusUART_UART_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        ModbusUART_IntrTxMask = LO16(ModbusUART_INTR_TX_MASK_REG);

    #if(ModbusUART_INTERNAL_RX_SW_BUFFER_CONST)
        ModbusUART_rxBufferHead     = 0u;
        ModbusUART_rxBufferTail     = 0u;
        ModbusUART_rxBufferOverflow = 0u;
    #endif /* (ModbusUART_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(ModbusUART_INTERNAL_TX_SW_BUFFER_CONST)
        ModbusUART_txBufferHead = 0u;
        ModbusUART_txBufferTail = 0u;
    #endif /* (ModbusUART_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: ModbusUART_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void ModbusUART_UartPostEnable(void)
{
#if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (ModbusUART_TX_SCL_MISO_PIN)
        if (ModbusUART_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            ModbusUART_SET_HSIOM_SEL(ModbusUART_TX_SCL_MISO_HSIOM_REG, ModbusUART_TX_SCL_MISO_HSIOM_MASK,
                                           ModbusUART_TX_SCL_MISO_HSIOM_POS, ModbusUART_TX_SCL_MISO_HSIOM_SEL_UART);
        }
    #endif /* (ModbusUART_TX_SCL_MISO_PIN_PIN) */

    #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
        #if (ModbusUART_RTS_SS0_PIN)
            if (ModbusUART_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                ModbusUART_SET_HSIOM_SEL(ModbusUART_RTS_SS0_HSIOM_REG, ModbusUART_RTS_SS0_HSIOM_MASK,
                                               ModbusUART_RTS_SS0_HSIOM_POS, ModbusUART_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (ModbusUART_RTS_SS0_PIN) */
    #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

#else
    #if (ModbusUART_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        ModbusUART_SET_HSIOM_SEL(ModbusUART_TX_HSIOM_REG, ModbusUART_TX_HSIOM_MASK,
                                       ModbusUART_TX_HSIOM_POS, ModbusUART_TX_HSIOM_SEL_UART);
    #endif /* (ModbusUART_UART_TX_PIN) */

    #if (ModbusUART_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        ModbusUART_SET_HSIOM_SEL(ModbusUART_RTS_HSIOM_REG, ModbusUART_RTS_HSIOM_MASK,
                                       ModbusUART_RTS_HSIOM_POS, ModbusUART_RTS_HSIOM_SEL_UART);
    #endif /* (ModbusUART_UART_RTS_PIN) */
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    ModbusUART_SetTxInterruptMode(ModbusUART_IntrTxMask);
}


/*******************************************************************************
* Function Name: ModbusUART_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void ModbusUART_UartStop(void)
{
#if(ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (ModbusUART_TX_SCL_MISO_PIN)
        if (ModbusUART_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            ModbusUART_SET_HSIOM_SEL(ModbusUART_TX_SCL_MISO_HSIOM_REG, ModbusUART_TX_SCL_MISO_HSIOM_MASK,
                                           ModbusUART_TX_SCL_MISO_HSIOM_POS, ModbusUART_TX_SCL_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (ModbusUART_TX_SCL_MISO_PIN_PIN) */

    #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
        #if (ModbusUART_RTS_SS0_PIN)
            if (ModbusUART_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                ModbusUART_uart_rts_spi_ss0_Write(ModbusUART_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                ModbusUART_SET_HSIOM_SEL(ModbusUART_RTS_SS0_HSIOM_REG, ModbusUART_RTS_SS0_HSIOM_MASK,
                                               ModbusUART_RTS_SS0_HSIOM_POS, ModbusUART_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (ModbusUART_RTS_SS0_PIN) */
    #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

#else
    #if (ModbusUART_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        ModbusUART_SET_HSIOM_SEL(ModbusUART_TX_HSIOM_REG, ModbusUART_TX_HSIOM_MASK,
                                       ModbusUART_TX_HSIOM_POS, ModbusUART_TX_HSIOM_SEL_GPIO);
    #endif /* (ModbusUART_UART_TX_PIN) */

    #if (ModbusUART_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        ModbusUART_rts_Write(ModbusUART_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        ModbusUART_SET_HSIOM_SEL(ModbusUART_RTS_HSIOM_REG, ModbusUART_RTS_HSIOM_MASK,
                                       ModbusUART_RTS_HSIOM_POS, ModbusUART_RTS_HSIOM_SEL_GPIO);
    #endif /* (ModbusUART_UART_RTS_PIN) */

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (ModbusUART_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    ModbusUART_UART_RX_CTRL_REG &= (uint32) ~ModbusUART_UART_RX_CTRL_SKIP_START;
#endif /* (ModbusUART_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    ModbusUART_IntrTxMask = LO16(ModbusUART_GetTxInterruptMode() & ModbusUART_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: ModbusUART_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void ModbusUART_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = ModbusUART_RX_MATCH_REG;

    matchReg &= ((uint32) ~ModbusUART_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & ModbusUART_RX_MATCH_ADDR_MASK)); /* Set address  */

    ModbusUART_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: ModbusUART_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void ModbusUART_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = ModbusUART_RX_MATCH_REG;

    matchReg &= ((uint32) ~ModbusUART_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << ModbusUART_RX_MATCH_MASK_POS));

    ModbusUART_RX_MATCH_REG = matchReg;
}


#if(ModbusUART_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: ModbusUART_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check ModbusUART_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 ModbusUART_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != ModbusUART_SpiUartGetRxBufferSize())
        {
            rxData = ModbusUART_SpiUartReadRxData();
        }

        if (ModbusUART_CHECK_INTR_RX(ModbusUART_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - ModbusUART_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - ModbusUART_UART_RX_UNDERFLOW    Attempt to read from an empty
    *     receiver FIFO.
    *   - ModbusUART_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - ModbusUART_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check ModbusUART_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 ModbusUART_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (ModbusUART_CHECK_RX_SW_BUFFER)
        {
            ModbusUART_DisableInt();
        }
        #endif

        if (0u != ModbusUART_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (ModbusUART_CHECK_RX_SW_BUFFER)
            {
                ModbusUART_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = ModbusUART_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = ModbusUART_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (ModbusUART_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_NOT_EMPTY);

                ModbusUART_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (ModbusUART_GetRxInterruptSource() & ModbusUART_INTR_RX_ERR);
        ModbusUART_ClearRxInterruptSource(ModbusUART_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: ModbusUART_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - ModbusUART_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - ModbusUART_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void ModbusUART_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                ModbusUART_UART_FLOW_CTRL_REG |= (uint32)  ModbusUART_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                ModbusUART_UART_FLOW_CTRL_REG &= (uint32) ~ModbusUART_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: ModbusUART_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void ModbusUART_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = ModbusUART_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~ModbusUART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (ModbusUART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            ModbusUART_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */

#endif /* (ModbusUART_UART_RX_DIRECTION) */


#if(ModbusUART_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: ModbusUART_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void ModbusUART_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            ModbusUART_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void ModbusUART_UartPutCRLF(uint32 txDataByte)
    {
        ModbusUART_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        ModbusUART_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        ModbusUART_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: ModbusUARTSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void ModbusUART_UartEnableCts(void)
        {
            ModbusUART_UART_FLOW_CTRL_REG |= (uint32)  ModbusUART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: ModbusUART_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void ModbusUART_UartDisableCts(void)
        {
            ModbusUART_UART_FLOW_CTRL_REG &= (uint32) ~ModbusUART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: ModbusUART_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        * \param
        * polarity: Active polarity of CTS output signal.
        *   - ModbusUART_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - ModbusUART_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void ModbusUART_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                ModbusUART_UART_FLOW_CTRL_REG |= (uint32)  ModbusUART_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                ModbusUART_UART_FLOW_CTRL_REG &= (uint32) ~ModbusUART_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */


    /*******************************************************************************
    * Function Name: ModbusUART_UartSendBreakBlocking
    ****************************************************************************//**
    *
    * Sends a break condition (logic low) of specified width on UART TX line.
    * Blocks until break is completed. Only call this function when UART TX FIFO
    * and shifter are empty.
    *
    * \param breakWidth
    * Width of break condition. Valid range is 4 to 16 bits.
    *
    * \note
    * Before sending break all UART TX interrupt sources are disabled. The state
    * of UART TX interrupt sources is restored before function returns.
    *
    * \sideeffect
    * If this function is called while there is data in the TX FIFO or shifter that
    * data will be shifted out in packets the size of breakWidth.
    *
    *******************************************************************************/
    void ModbusUART_UartSendBreakBlocking(uint32 breakWidth)
    {
        uint32 txCtrlReg;
        uint32 txIntrReg;

        /* Disable all UART TX interrupt source and clear UART TX Done history */
        txIntrReg = ModbusUART_GetTxInterruptMode();
        ModbusUART_SetTxInterruptMode(0u);
        ModbusUART_ClearTxInterruptSource(ModbusUART_INTR_TX_UART_DONE);

        /* Store TX CTRL configuration */
        txCtrlReg = ModbusUART_TX_CTRL_REG;

        /* Set break width */
        ModbusUART_TX_CTRL_REG = (ModbusUART_TX_CTRL_REG & (uint32) ~ModbusUART_TX_CTRL_DATA_WIDTH_MASK) |
                                        ModbusUART_GET_TX_CTRL_DATA_WIDTH(breakWidth);

        /* Generate break */
        ModbusUART_TX_FIFO_WR_REG = 0u;

        /* Wait for break completion */
        while (0u == (ModbusUART_GetTxInterruptSource() & ModbusUART_INTR_TX_UART_DONE))
        {
        }

        /* Clear all UART TX interrupt sources to  */
        ModbusUART_ClearTxInterruptSource(ModbusUART_INTR_TX_ALL);

        /* Restore TX interrupt sources and data width */
        ModbusUART_TX_CTRL_REG = txCtrlReg;
        ModbusUART_SetTxInterruptMode(txIntrReg);
    }
#endif /* (ModbusUART_UART_TX_DIRECTION) */


#if (ModbusUART_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: ModbusUART_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be
    *  cleared by this API.
    *
    *******************************************************************************/
    void ModbusUART_UartSaveConfig(void)
    {
    #if (ModbusUART_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != ModbusUART_skipStart)
        {
            ModbusUART_UART_RX_CTRL_REG |= (uint32)  ModbusUART_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            ModbusUART_UART_RX_CTRL_REG &= (uint32) ~ModbusUART_UART_RX_CTRL_SKIP_START;
        }

        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        ModbusUART_CLEAR_UART_RX_WAKE_INTR;
        ModbusUART_RxWakeClearPendingInt();
        ModbusUART_RxWakeEnableInt();
    #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: ModbusUART_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void ModbusUART_UartRestoreConfig(void)
    {
    #if (ModbusUART_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        ModbusUART_RxWakeDisableInt();
    #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */
    }


    #if (ModbusUART_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: ModbusUART_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(ModbusUART_UART_WAKEUP_ISR)
        {
        #ifdef ModbusUART_UART_WAKEUP_ISR_ENTRY_CALLBACK
            ModbusUART_UART_WAKEUP_ISR_EntryCallback();
        #endif /* ModbusUART_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            ModbusUART_CLEAR_UART_RX_WAKE_INTR;

        #ifdef ModbusUART_UART_WAKEUP_ISR_EXIT_CALLBACK
            ModbusUART_UART_WAKEUP_ISR_ExitCallback();
        #endif /* ModbusUART_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */
#endif /* (ModbusUART_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
