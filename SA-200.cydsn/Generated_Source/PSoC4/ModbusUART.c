/***************************************************************************//**
* \file ModbusUART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#if (ModbusUART_SCB_MODE_I2C_INC)
    #include "ModbusUART_I2C_PVT.h"
#endif /* (ModbusUART_SCB_MODE_I2C_INC) */

#if (ModbusUART_SCB_MODE_EZI2C_INC)
    #include "ModbusUART_EZI2C_PVT.h"
#endif /* (ModbusUART_SCB_MODE_EZI2C_INC) */

#if (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC)
    #include "ModbusUART_SPI_UART_PVT.h"
#endif /* (ModbusUART_SCB_MODE_SPI_INC || ModbusUART_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 ModbusUART_scbMode = ModbusUART_SCB_MODE_UNCONFIG;
    uint8 ModbusUART_scbEnableWake;
    uint8 ModbusUART_scbEnableIntr;

    /* I2C configuration variables */
    uint8 ModbusUART_mode;
    uint8 ModbusUART_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * ModbusUART_rxBuffer;
    uint8  ModbusUART_rxDataBits;
    uint32 ModbusUART_rxBufferSize;

    volatile uint8 * ModbusUART_txBuffer;
    uint8  ModbusUART_txDataBits;
    uint32 ModbusUART_txBufferSize;

    /* EZI2C configuration variables */
    uint8 ModbusUART_numberOfAddr;
    uint8 ModbusUART_subAddrSize;
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** ModbusUART_initVar indicates whether the ModbusUART 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the ModbusUART_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  ModbusUART_Init() function can be called before the 
*  ModbusUART_Start() or ModbusUART_Enable() function.
*/
uint8 ModbusUART_initVar = 0u;


#if (! (ModbusUART_SCB_MODE_I2C_CONST_CFG || \
        ModbusUART_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * ModbusUART_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent ModbusUART_Enable() call.
    */
    uint16 ModbusUART_IntrTxMask = 0u;
#endif /* (! (ModbusUART_SCB_MODE_I2C_CONST_CFG || \
              ModbusUART_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (ModbusUART_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER)
    void (*ModbusUART_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER) */
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void ModbusUART_ScbEnableIntr(void);
static void ModbusUART_ScbModeStop(void);
static void ModbusUART_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: ModbusUART_Init
****************************************************************************//**
*
*  Initializes the ModbusUART component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  ModbusUART_I2CInit, ModbusUART_SpiInit, 
*  ModbusUART_UartInit or ModbusUART_EzI2CInit.
*
*******************************************************************************/
void ModbusUART_Init(void)
{
#if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    if (ModbusUART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        ModbusUART_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (ModbusUART_SCB_MODE_I2C_CONST_CFG)
    ModbusUART_I2CInit();

#elif (ModbusUART_SCB_MODE_SPI_CONST_CFG)
    ModbusUART_SpiInit();

#elif (ModbusUART_SCB_MODE_UART_CONST_CFG)
    ModbusUART_UartInit();

#elif (ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
    ModbusUART_EzI2CInit();

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_Enable
****************************************************************************//**
*
*  Enables ModbusUART component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  ModbusUART_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The ModbusUART configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured ModbusUART”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void ModbusUART_Enable(void)
{
#if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!ModbusUART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        ModbusUART_CTRL_REG |= ModbusUART_CTRL_ENABLED;

        ModbusUART_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        ModbusUART_ScbModePostEnable();
    }
#else
    ModbusUART_CTRL_REG |= ModbusUART_CTRL_ENABLED;

    ModbusUART_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    ModbusUART_ScbModePostEnable();
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_Start
****************************************************************************//**
*
*  Invokes ModbusUART_Init() and ModbusUART_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  ModbusUART_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void ModbusUART_Start(void)
{
    if (0u == ModbusUART_initVar)
    {
        ModbusUART_Init();
        ModbusUART_initVar = 1u; /* Component was initialized */
    }

    ModbusUART_Enable();
}


/*******************************************************************************
* Function Name: ModbusUART_Stop
****************************************************************************//**
*
*  Disables the ModbusUART component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function ModbusUART_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void ModbusUART_Stop(void)
{
#if (ModbusUART_SCB_IRQ_INTERNAL)
    ModbusUART_DisableInt();
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    ModbusUART_ScbModeStop();

    /* Disable SCB IP */
    ModbusUART_CTRL_REG &= (uint32) ~ModbusUART_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    ModbusUART_SetTxInterruptMode(ModbusUART_NO_INTR_SOURCES);

#if (ModbusUART_SCB_IRQ_INTERNAL)
    ModbusUART_ClearPendingInt();
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: ModbusUART_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void ModbusUART_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = ModbusUART_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~ModbusUART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (ModbusUART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    ModbusUART_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: ModbusUART_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void ModbusUART_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = ModbusUART_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~ModbusUART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (ModbusUART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    ModbusUART_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (ModbusUART_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: ModbusUART_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void ModbusUART_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER)
        ModbusUART_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_ModbusUART_CUSTOM_INTR_HANDLER) */
    }
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: ModbusUART_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void ModbusUART_ScbEnableIntr(void)
{
#if (ModbusUART_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != ModbusUART_scbEnableIntr)
        {
            ModbusUART_EnableInt();
        }

    #else
        ModbusUART_EnableInt();

    #endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (ModbusUART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: ModbusUART_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void ModbusUART_ScbModePostEnable(void)
{
#if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!ModbusUART_CY_SCBIP_V1)
    if (ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
    {
        ModbusUART_SpiPostEnable();
    }
    else if (ModbusUART_SCB_MODE_UART_RUNTM_CFG)
    {
        ModbusUART_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!ModbusUART_CY_SCBIP_V1) */

#elif (ModbusUART_SCB_MODE_SPI_CONST_CFG)
    ModbusUART_SpiPostEnable();

#elif (ModbusUART_SCB_MODE_UART_CONST_CFG)
    ModbusUART_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: ModbusUART_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void ModbusUART_ScbModeStop(void)
{
#if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    if (ModbusUART_SCB_MODE_I2C_RUNTM_CFG)
    {
        ModbusUART_I2CStop();
    }
    else if (ModbusUART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        ModbusUART_EzI2CStop();
    }
#if (!ModbusUART_CY_SCBIP_V1)
    else if (ModbusUART_SCB_MODE_SPI_RUNTM_CFG)
    {
        ModbusUART_SpiStop();
    }
    else if (ModbusUART_SCB_MODE_UART_RUNTM_CFG)
    {
        ModbusUART_UartStop();
    }
#endif /* (!ModbusUART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (ModbusUART_SCB_MODE_I2C_CONST_CFG)
    ModbusUART_I2CStop();

#elif (ModbusUART_SCB_MODE_EZI2C_CONST_CFG)
    ModbusUART_EzI2CStop();

#elif (ModbusUART_SCB_MODE_SPI_CONST_CFG)
    ModbusUART_SpiStop();

#elif (ModbusUART_SCB_MODE_UART_CONST_CFG)
    ModbusUART_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: ModbusUART_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void ModbusUART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[ModbusUART_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!ModbusUART_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!ModbusUART_CY_SCBIP_V1) */
        
        uint32 hsiomSel[ModbusUART_SCB_PINS_NUMBER] = 
        {
            ModbusUART_RX_SDA_MOSI_HSIOM_SEL_GPIO,
            ModbusUART_TX_SCL_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (ModbusUART_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (ModbusUART_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < ModbusUART_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = ModbusUART_PIN_DM_ALG_HIZ;
        }

        if ((ModbusUART_SCB_MODE_I2C   == mode) ||
            (ModbusUART_SCB_MODE_EZI2C == mode))
        {
        #if (ModbusUART_RX_SDA_MOSI_PIN)
            hsiomSel[ModbusUART_RX_SDA_MOSI_PIN_INDEX] = ModbusUART_RX_SDA_MOSI_HSIOM_SEL_I2C;
            pinsDm  [ModbusUART_RX_SDA_MOSI_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
        #elif (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
            hsiomSel[ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX] = ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_SEL_I2C;
            pinsDm  [ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
        #else
        #endif /* (ModbusUART_RX_SDA_MOSI_PIN) */
        
        #if (ModbusUART_TX_SCL_MISO_PIN)
            hsiomSel[ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_TX_SCL_MISO_HSIOM_SEL_I2C;
            pinsDm  [ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
        #endif /* (ModbusUART_TX_SCL_MISO_PIN) */
        }
    #if (!ModbusUART_CY_SCBIP_V1)
        else if (ModbusUART_SCB_MODE_SPI == mode)
        {
        #if (ModbusUART_RX_SDA_MOSI_PIN)
            hsiomSel[ModbusUART_RX_SDA_MOSI_PIN_INDEX] = ModbusUART_RX_SDA_MOSI_HSIOM_SEL_SPI;
        #elif (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
            hsiomSel[ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX] = ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (ModbusUART_RX_SDA_MOSI_PIN) */
        
        #if (ModbusUART_TX_SCL_MISO_PIN)
            hsiomSel[ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_TX_SCL_MISO_HSIOM_SEL_SPI;
        #endif /* (ModbusUART_TX_SCL_MISO_PIN) */
        
        #if (ModbusUART_CTS_SCLK_PIN)
            hsiomSel[ModbusUART_CTS_SCLK_PIN_INDEX] = ModbusUART_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (ModbusUART_CTS_SCLK_PIN) */

            if (ModbusUART_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[ModbusUART_RX_SDA_MOSI_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                pinsDm[ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsDm[ModbusUART_CTS_SCLK_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;

            #if (ModbusUART_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[ModbusUART_RTS_SS0_PIN_INDEX] = ModbusUART_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [ModbusUART_RTS_SS0_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
            #endif /* (ModbusUART_RTS_SS0_PIN) */

            #if (ModbusUART_TX_SCL_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= ModbusUART_TX_SCL_MISO_PIN_MASK;
            #endif /* (ModbusUART_TX_SCL_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[ModbusUART_RX_SDA_MOSI_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsDm[ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                pinsDm[ModbusUART_CTS_SCLK_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;

            #if (ModbusUART_RTS_SS0_PIN)
                hsiomSel [ModbusUART_RTS_SS0_PIN_INDEX] = ModbusUART_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [ModbusUART_RTS_SS0_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsInBuf |= ModbusUART_RTS_SS0_PIN_MASK;
            #endif /* (ModbusUART_RTS_SS0_PIN) */

            #if (ModbusUART_SS1_PIN)
                hsiomSel [ModbusUART_SS1_PIN_INDEX] = ModbusUART_SS1_HSIOM_SEL_SPI;
                pinsDm   [ModbusUART_SS1_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsInBuf |= ModbusUART_SS1_PIN_MASK;
            #endif /* (ModbusUART_SS1_PIN) */

            #if (ModbusUART_SS2_PIN)
                hsiomSel [ModbusUART_SS2_PIN_INDEX] = ModbusUART_SS2_HSIOM_SEL_SPI;
                pinsDm   [ModbusUART_SS2_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsInBuf |= ModbusUART_SS2_PIN_MASK;
            #endif /* (ModbusUART_SS2_PIN) */

            #if (ModbusUART_SS3_PIN)
                hsiomSel [ModbusUART_SS3_PIN_INDEX] = ModbusUART_SS3_HSIOM_SEL_SPI;
                pinsDm   [ModbusUART_SS3_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                pinsInBuf |= ModbusUART_SS3_PIN_MASK;
            #endif /* (ModbusUART_SS3_PIN) */

                /* Disable input buffers */
            #if (ModbusUART_RX_SDA_MOSI_PIN)
                pinsInBuf |= ModbusUART_RX_SDA_MOSI_PIN_MASK;
            #elif (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
                pinsInBuf |= ModbusUART_RX_WAKE_SDA_MOSI_PIN_MASK;
            #else
            #endif /* (ModbusUART_RX_SDA_MOSI_PIN) */

            #if (ModbusUART_CTS_SCLK_PIN)
                pinsInBuf |= ModbusUART_CTS_SCLK_PIN_MASK;
            #endif /* (ModbusUART_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (ModbusUART_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (ModbusUART_TX_SCL_MISO_PIN)
                hsiomSel[ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_TX_SCL_MISO_HSIOM_SEL_UART;
                pinsDm  [ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_PIN_DM_OD_LO;
            #endif /* (ModbusUART_TX_SCL_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (ModbusUART_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (ModbusUART_RX_SDA_MOSI_PIN)
                    hsiomSel[ModbusUART_RX_SDA_MOSI_PIN_INDEX] = ModbusUART_RX_SDA_MOSI_HSIOM_SEL_UART;
                    pinsDm  [ModbusUART_RX_SDA_MOSI_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                #elif (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
                    hsiomSel[ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX] = ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_SEL_UART;
                    pinsDm  [ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                #else
                #endif /* (ModbusUART_RX_SDA_MOSI_PIN) */
                }

                if (0u != (ModbusUART_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (ModbusUART_TX_SCL_MISO_PIN)
                    hsiomSel[ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_TX_SCL_MISO_HSIOM_SEL_UART;
                    pinsDm  [ModbusUART_TX_SCL_MISO_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= ModbusUART_TX_SCL_MISO_PIN_MASK;
                #endif /* (ModbusUART_TX_SCL_MISO_PIN) */
                }

            #if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
                if (ModbusUART_UART_MODE_STD == subMode)
                {
                    if (0u != (ModbusUART_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (ModbusUART_CTS_SCLK_PIN)
                        hsiomSel[ModbusUART_CTS_SCLK_PIN_INDEX] = ModbusUART_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [ModbusUART_CTS_SCLK_PIN_INDEX] = ModbusUART_PIN_DM_DIG_HIZ;
                    #endif /* (ModbusUART_CTS_SCLK_PIN) */
                    }

                    if (0u != (ModbusUART_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (ModbusUART_RTS_SS0_PIN)
                        hsiomSel[ModbusUART_RTS_SS0_PIN_INDEX] = ModbusUART_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [ModbusUART_RTS_SS0_PIN_INDEX] = ModbusUART_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= ModbusUART_RTS_SS0_PIN_MASK;
                    #endif /* (ModbusUART_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */
            }
        }
    #endif /* (!ModbusUART_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (ModbusUART_RX_SDA_MOSI_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_RX_SDA_MOSI_HSIOM_REG,
                                       ModbusUART_RX_SDA_MOSI_HSIOM_MASK,
                                       ModbusUART_RX_SDA_MOSI_HSIOM_POS,
                                        hsiomSel[ModbusUART_RX_SDA_MOSI_PIN_INDEX]);

        ModbusUART_uart_rx_i2c_sda_spi_mosi_SetDriveMode((uint8) pinsDm[ModbusUART_RX_SDA_MOSI_PIN_INDEX]);

        #if (!ModbusUART_CY_SCBIP_V1)
            ModbusUART_SET_INP_DIS(ModbusUART_uart_rx_i2c_sda_spi_mosi_INP_DIS,
                                         ModbusUART_uart_rx_i2c_sda_spi_mosi_MASK,
                                         (0u != (pinsInBuf & ModbusUART_RX_SDA_MOSI_PIN_MASK)));
        #endif /* (!ModbusUART_CY_SCBIP_V1) */
    
    #elif (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG,
                                       ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_MASK,
                                       ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_POS,
                                       hsiomSel[ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX]);

        ModbusUART_uart_rx_wake_i2c_sda_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_uart_rx_wake_i2c_sda_spi_mosi_INP_DIS,
                                     ModbusUART_uart_rx_wake_i2c_sda_spi_mosi_MASK,
                                     (0u != (pinsInBuf & ModbusUART_RX_WAKE_SDA_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        ModbusUART_SET_INCFG_TYPE(ModbusUART_RX_WAKE_SDA_MOSI_INTCFG_REG,
                                        ModbusUART_RX_WAKE_SDA_MOSI_INTCFG_TYPE_MASK,
                                        ModbusUART_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS,
                                        ModbusUART_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (ModbusUART_RX_WAKE_SDA_MOSI_PIN) */

    #if (ModbusUART_TX_SCL_MISO_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_TX_SCL_MISO_HSIOM_REG,
                                       ModbusUART_TX_SCL_MISO_HSIOM_MASK,
                                       ModbusUART_TX_SCL_MISO_HSIOM_POS,
                                        hsiomSel[ModbusUART_TX_SCL_MISO_PIN_INDEX]);

        ModbusUART_uart_tx_i2c_scl_spi_miso_SetDriveMode((uint8) pinsDm[ModbusUART_TX_SCL_MISO_PIN_INDEX]);

    #if (!ModbusUART_CY_SCBIP_V1)
        ModbusUART_SET_INP_DIS(ModbusUART_uart_tx_i2c_scl_spi_miso_INP_DIS,
                                     ModbusUART_uart_tx_i2c_scl_spi_miso_MASK,
                                    (0u != (pinsInBuf & ModbusUART_TX_SCL_MISO_PIN_MASK)));
    #endif /* (!ModbusUART_CY_SCBIP_V1) */
    #endif /* (ModbusUART_RX_SDA_MOSI_PIN) */

    #if (ModbusUART_CTS_SCLK_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_CTS_SCLK_HSIOM_REG,
                                       ModbusUART_CTS_SCLK_HSIOM_MASK,
                                       ModbusUART_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[ModbusUART_CTS_SCLK_PIN_INDEX]);

        ModbusUART_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[ModbusUART_CTS_SCLK_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_uart_cts_spi_sclk_INP_DIS,
                                     ModbusUART_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & ModbusUART_CTS_SCLK_PIN_MASK)));
    #endif /* (ModbusUART_CTS_SCLK_PIN) */

    #if (ModbusUART_RTS_SS0_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_RTS_SS0_HSIOM_REG,
                                       ModbusUART_RTS_SS0_HSIOM_MASK,
                                       ModbusUART_RTS_SS0_HSIOM_POS,
                                       hsiomSel[ModbusUART_RTS_SS0_PIN_INDEX]);

        ModbusUART_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[ModbusUART_RTS_SS0_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_uart_rts_spi_ss0_INP_DIS,
                                     ModbusUART_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & ModbusUART_RTS_SS0_PIN_MASK)));
    #endif /* (ModbusUART_RTS_SS0_PIN) */

    #if (ModbusUART_SS1_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS1_HSIOM_REG,
                                       ModbusUART_SS1_HSIOM_MASK,
                                       ModbusUART_SS1_HSIOM_POS,
                                       hsiomSel[ModbusUART_SS1_PIN_INDEX]);

        ModbusUART_spi_ss1_SetDriveMode((uint8) pinsDm[ModbusUART_SS1_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_ss1_INP_DIS,
                                     ModbusUART_spi_ss1_MASK,
                                     (0u != (pinsInBuf & ModbusUART_SS1_PIN_MASK)));
    #endif /* (ModbusUART_SS1_PIN) */

    #if (ModbusUART_SS2_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS2_HSIOM_REG,
                                       ModbusUART_SS2_HSIOM_MASK,
                                       ModbusUART_SS2_HSIOM_POS,
                                       hsiomSel[ModbusUART_SS2_PIN_INDEX]);

        ModbusUART_spi_ss2_SetDriveMode((uint8) pinsDm[ModbusUART_SS2_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_ss2_INP_DIS,
                                     ModbusUART_spi_ss2_MASK,
                                     (0u != (pinsInBuf & ModbusUART_SS2_PIN_MASK)));
    #endif /* (ModbusUART_SS2_PIN) */

    #if (ModbusUART_SS3_PIN)
        ModbusUART_SET_HSIOM_SEL(ModbusUART_SS3_HSIOM_REG,
                                       ModbusUART_SS3_HSIOM_MASK,
                                       ModbusUART_SS3_HSIOM_POS,
                                       hsiomSel[ModbusUART_SS3_PIN_INDEX]);

        ModbusUART_spi_ss3_SetDriveMode((uint8) pinsDm[ModbusUART_SS3_PIN_INDEX]);

        ModbusUART_SET_INP_DIS(ModbusUART_spi_ss3_INP_DIS,
                                     ModbusUART_spi_ss3_MASK,
                                     (0u != (pinsInBuf & ModbusUART_SS3_PIN_MASK)));
    #endif /* (ModbusUART_SS3_PIN) */
    }

#endif /* (ModbusUART_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: ModbusUART_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void ModbusUART_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (ModbusUART_CTRL_REG & ModbusUART_CTRL_EC_AM_MODE)) &&
            (0u == (ModbusUART_I2C_CTRL_REG & ModbusUART_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            ModbusUART_CTRL_REG &= ~ModbusUART_CTRL_EC_AM_MODE;
            ModbusUART_CTRL_REG |=  ModbusUART_CTRL_EC_AM_MODE;
        }

        ModbusUART_I2C_SLAVE_CMD_REG = ModbusUART_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */


/* [] END OF FILE */
