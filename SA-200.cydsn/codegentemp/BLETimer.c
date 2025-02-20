/*******************************************************************************
* File Name: BLETimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the BLETimer
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BLETimer.h"

uint8 BLETimer_initVar = 0u;


/*******************************************************************************
* Function Name: BLETimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default BLETimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (BLETimer__QUAD == BLETimer_CONFIG)
        BLETimer_CONTROL_REG = BLETimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        BLETimer_TRIG_CONTROL1_REG  = BLETimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        BLETimer_SetInterruptMode(BLETimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        BLETimer_SetCounterMode(BLETimer_COUNT_DOWN);
        BLETimer_WritePeriod(BLETimer_QUAD_PERIOD_INIT_VALUE);
        BLETimer_WriteCounter(BLETimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (BLETimer__QUAD == BLETimer_CONFIG) */

    #if (BLETimer__TIMER == BLETimer_CONFIG)
        BLETimer_CONTROL_REG = BLETimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        BLETimer_TRIG_CONTROL1_REG  = BLETimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        BLETimer_SetInterruptMode(BLETimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        BLETimer_WritePeriod(BLETimer_TC_PERIOD_VALUE );

        #if (BLETimer__COMPARE == BLETimer_TC_COMP_CAP_MODE)
            BLETimer_WriteCompare(BLETimer_TC_COMPARE_VALUE);

            #if (1u == BLETimer_TC_COMPARE_SWAP)
                BLETimer_SetCompareSwap(1u);
                BLETimer_WriteCompareBuf(BLETimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == BLETimer_TC_COMPARE_SWAP) */
        #endif  /* (BLETimer__COMPARE == BLETimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (BLETimer_CY_TCPWM_V2 && BLETimer_TIMER_UPDOWN_CNT_USED && !BLETimer_CY_TCPWM_4000)
            BLETimer_WriteCounter(1u);
        #elif(BLETimer__COUNT_DOWN == BLETimer_TC_COUNTER_MODE)
            BLETimer_WriteCounter(BLETimer_TC_PERIOD_VALUE);
        #else
            BLETimer_WriteCounter(0u);
        #endif /* (BLETimer_CY_TCPWM_V2 && BLETimer_TIMER_UPDOWN_CNT_USED && !BLETimer_CY_TCPWM_4000) */
    #endif  /* (BLETimer__TIMER == BLETimer_CONFIG) */

    #if (BLETimer__PWM_SEL == BLETimer_CONFIG)
        BLETimer_CONTROL_REG = BLETimer_CTRL_PWM_BASE_CONFIG;

        #if (BLETimer__PWM_PR == BLETimer_PWM_MODE)
            BLETimer_CONTROL_REG |= BLETimer_CTRL_PWM_RUN_MODE;
            BLETimer_WriteCounter(BLETimer_PWM_PR_INIT_VALUE);
        #else
            BLETimer_CONTROL_REG |= BLETimer_CTRL_PWM_ALIGN | BLETimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (BLETimer_CY_TCPWM_V2 && BLETimer_PWM_UPDOWN_CNT_USED && !BLETimer_CY_TCPWM_4000)
                BLETimer_WriteCounter(1u);
            #elif (BLETimer__RIGHT == BLETimer_PWM_ALIGN)
                BLETimer_WriteCounter(BLETimer_PWM_PERIOD_VALUE);
            #else 
                BLETimer_WriteCounter(0u);
            #endif  /* (BLETimer_CY_TCPWM_V2 && BLETimer_PWM_UPDOWN_CNT_USED && !BLETimer_CY_TCPWM_4000) */
        #endif  /* (BLETimer__PWM_PR == BLETimer_PWM_MODE) */

        #if (BLETimer__PWM_DT == BLETimer_PWM_MODE)
            BLETimer_CONTROL_REG |= BLETimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (BLETimer__PWM_DT == BLETimer_PWM_MODE) */

        #if (BLETimer__PWM == BLETimer_PWM_MODE)
            BLETimer_CONTROL_REG |= BLETimer_CTRL_PWM_PRESCALER;
        #endif  /* (BLETimer__PWM == BLETimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        BLETimer_TRIG_CONTROL1_REG  = BLETimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        BLETimer_SetInterruptMode(BLETimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (BLETimer__PWM_PR == BLETimer_PWM_MODE)
            BLETimer_TRIG_CONTROL2_REG =
                    (BLETimer_CC_MATCH_NO_CHANGE    |
                    BLETimer_OVERLOW_NO_CHANGE      |
                    BLETimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (BLETimer__LEFT == BLETimer_PWM_ALIGN)
                BLETimer_TRIG_CONTROL2_REG = BLETimer_PWM_MODE_LEFT;
            #endif  /* ( BLETimer_PWM_LEFT == BLETimer_PWM_ALIGN) */

            #if (BLETimer__RIGHT == BLETimer_PWM_ALIGN)
                BLETimer_TRIG_CONTROL2_REG = BLETimer_PWM_MODE_RIGHT;
            #endif  /* ( BLETimer_PWM_RIGHT == BLETimer_PWM_ALIGN) */

            #if (BLETimer__CENTER == BLETimer_PWM_ALIGN)
                BLETimer_TRIG_CONTROL2_REG = BLETimer_PWM_MODE_CENTER;
            #endif  /* ( BLETimer_PWM_CENTER == BLETimer_PWM_ALIGN) */

            #if (BLETimer__ASYMMETRIC == BLETimer_PWM_ALIGN)
                BLETimer_TRIG_CONTROL2_REG = BLETimer_PWM_MODE_ASYM;
            #endif  /* (BLETimer__ASYMMETRIC == BLETimer_PWM_ALIGN) */
        #endif  /* (BLETimer__PWM_PR == BLETimer_PWM_MODE) */

        /* Set other values from customizer */
        BLETimer_WritePeriod(BLETimer_PWM_PERIOD_VALUE );
        BLETimer_WriteCompare(BLETimer_PWM_COMPARE_VALUE);

        #if (1u == BLETimer_PWM_COMPARE_SWAP)
            BLETimer_SetCompareSwap(1u);
            BLETimer_WriteCompareBuf(BLETimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == BLETimer_PWM_COMPARE_SWAP) */

        #if (1u == BLETimer_PWM_PERIOD_SWAP)
            BLETimer_SetPeriodSwap(1u);
            BLETimer_WritePeriodBuf(BLETimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == BLETimer_PWM_PERIOD_SWAP) */
    #endif  /* (BLETimer__PWM_SEL == BLETimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: BLETimer_Enable
********************************************************************************
*
* Summary:
*  Enables the BLETimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    BLETimer_BLOCK_CONTROL_REG |= BLETimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (BLETimer__PWM_SEL == BLETimer_CONFIG)
        #if (0u == BLETimer_PWM_START_SIGNAL_PRESENT)
            BLETimer_TriggerCommand(BLETimer_MASK, BLETimer_CMD_START);
        #endif /* (0u == BLETimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (BLETimer__PWM_SEL == BLETimer_CONFIG) */

    #if (BLETimer__TIMER == BLETimer_CONFIG)
        #if (0u == BLETimer_TC_START_SIGNAL_PRESENT)
            BLETimer_TriggerCommand(BLETimer_MASK, BLETimer_CMD_START);
        #endif /* (0u == BLETimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (BLETimer__TIMER == BLETimer_CONFIG) */
    
    #if (BLETimer__QUAD == BLETimer_CONFIG)
        #if (0u != BLETimer_QUAD_AUTO_START)
            BLETimer_TriggerCommand(BLETimer_MASK, BLETimer_CMD_RELOAD);
        #endif /* (0u != BLETimer_QUAD_AUTO_START) */
    #endif  /* (BLETimer__QUAD == BLETimer_CONFIG) */
}


/*******************************************************************************
* Function Name: BLETimer_Start
********************************************************************************
*
* Summary:
*  Initializes the BLETimer with default customizer
*  values when called the first time and enables the BLETimer.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BLETimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time BLETimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the BLETimer_Start() routine.
*
*******************************************************************************/
void BLETimer_Start(void)
{
    if (0u == BLETimer_initVar)
    {
        BLETimer_Init();
        BLETimer_initVar = 1u;
    }

    BLETimer_Enable();
}


/*******************************************************************************
* Function Name: BLETimer_Stop
********************************************************************************
*
* Summary:
*  Disables the BLETimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_BLOCK_CONTROL_REG &= (uint32)~BLETimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the BLETimer. This function is used when
*  configured as a generic BLETimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the BLETimer to operate in
*   Values:
*   - BLETimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - BLETimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - BLETimer_MODE_QUAD - Quadrature decoder
*         - BLETimer_MODE_PWM - PWM
*         - BLETimer_MODE_PWM_DT - PWM with dead time
*         - BLETimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_MODE_MASK;
    BLETimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - BLETimer_MODE_X1 - Counts on phi 1 rising
*         - BLETimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - BLETimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_QUAD_MODE_MASK;
    BLETimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - BLETimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - BLETimer_PRESCALE_DIVBY2    - Divide by 2
*         - BLETimer_PRESCALE_DIVBY4    - Divide by 4
*         - BLETimer_PRESCALE_DIVBY8    - Divide by 8
*         - BLETimer_PRESCALE_DIVBY16   - Divide by 16
*         - BLETimer_PRESCALE_DIVBY32   - Divide by 32
*         - BLETimer_PRESCALE_DIVBY64   - Divide by 64
*         - BLETimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_PRESCALER_MASK;
    BLETimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the BLETimer runs
*  continuously or stops when terminal count is reached.  By default the
*  BLETimer operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_ONESHOT_MASK;
    BLETimer_CONTROL_REG |= ((uint32)((oneShotEnable & BLETimer_1BIT_MASK) <<
                                                               BLETimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetPWMMode(uint32 modeMask)
{
    BLETimer_TRIG_CONTROL2_REG = (modeMask & BLETimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: BLETimer_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_PWM_SYNC_KILL_MASK;
    BLETimer_CONTROL_REG |= ((uint32)((syncKillEnable & BLETimer_1BIT_MASK)  <<
                                               BLETimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_PWM_STOP_KILL_MASK;
    BLETimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & BLETimer_1BIT_MASK)  <<
                                                         BLETimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_PRESCALER_MASK;
    BLETimer_CONTROL_REG |= ((uint32)((deadTime & BLETimer_8BIT_MASK) <<
                                                          BLETimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - BLETimer_INVERT_LINE   - Inverts the line output
*         - BLETimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_INV_OUT_MASK;
    BLETimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: BLETimer_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_WriteCounter(uint32 count)
{
    BLETimer_COUNTER_REG = (count & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 BLETimer_ReadCounter(void)
{
    return (BLETimer_COUNTER_REG & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - BLETimer_COUNT_UP       - Counts up
*     - BLETimer_COUNT_DOWN     - Counts down
*     - BLETimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - BLETimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_UPDOWN_MASK;
    BLETimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_WritePeriod(uint32 period)
{
    BLETimer_PERIOD_REG = (period & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 BLETimer_ReadPeriod(void)
{
    return (BLETimer_PERIOD_REG & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_RELOAD_CC_MASK;
    BLETimer_CONTROL_REG |= (swapEnable & BLETimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_WritePeriodBuf(uint32 periodBuf)
{
    BLETimer_PERIOD_BUF_REG = (periodBuf & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 BLETimer_ReadPeriodBuf(void)
{
    return (BLETimer_PERIOD_BUF_REG & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_CONTROL_REG &= (uint32)~BLETimer_RELOAD_PERIOD_MASK;
    BLETimer_CONTROL_REG |= ((uint32)((swapEnable & BLETimer_1BIT_MASK) <<
                                                            BLETimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void BLETimer_WriteCompare(uint32 compare)
{
    #if (BLETimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (BLETimer_CY_TCPWM_4000) */

    #if (BLETimer_CY_TCPWM_4000)
        currentMode = ((BLETimer_CONTROL_REG & BLETimer_UPDOWN_MASK) >> BLETimer_UPDOWN_SHIFT);

        if (((uint32)BLETimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)BLETimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (BLETimer_CY_TCPWM_4000) */
    
    BLETimer_COMP_CAP_REG = (compare & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 BLETimer_ReadCompare(void)
{
    #if (BLETimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (BLETimer_CY_TCPWM_4000) */

    #if (BLETimer_CY_TCPWM_4000)
        currentMode = ((BLETimer_CONTROL_REG & BLETimer_UPDOWN_MASK) >> BLETimer_UPDOWN_SHIFT);
        
        regVal = BLETimer_COMP_CAP_REG;
        
        if (((uint32)BLETimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)BLETimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & BLETimer_16BIT_MASK);
    #else
        return (BLETimer_COMP_CAP_REG & BLETimer_16BIT_MASK);
    #endif /* (BLETimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: BLETimer_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void BLETimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (BLETimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (BLETimer_CY_TCPWM_4000) */

    #if (BLETimer_CY_TCPWM_4000)
        currentMode = ((BLETimer_CONTROL_REG & BLETimer_UPDOWN_MASK) >> BLETimer_UPDOWN_SHIFT);

        if (((uint32)BLETimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)BLETimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (BLETimer_CY_TCPWM_4000) */
    
    BLETimer_COMP_CAP_BUF_REG = (compareBuf & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 BLETimer_ReadCompareBuf(void)
{
    #if (BLETimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (BLETimer_CY_TCPWM_4000) */

    #if (BLETimer_CY_TCPWM_4000)
        currentMode = ((BLETimer_CONTROL_REG & BLETimer_UPDOWN_MASK) >> BLETimer_UPDOWN_SHIFT);

        regVal = BLETimer_COMP_CAP_BUF_REG;
        
        if (((uint32)BLETimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)BLETimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & BLETimer_16BIT_MASK);
    #else
        return (BLETimer_COMP_CAP_BUF_REG & BLETimer_16BIT_MASK);
    #endif /* (BLETimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: BLETimer_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 BLETimer_ReadCapture(void)
{
    return (BLETimer_COMP_CAP_REG & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 BLETimer_ReadCaptureBuf(void)
{
    return (BLETimer_COMP_CAP_BUF_REG & BLETimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: BLETimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLETimer_TRIG_LEVEL     - Level
*     - BLETimer_TRIG_RISING    - Rising edge
*     - BLETimer_TRIG_FALLING   - Falling edge
*     - BLETimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_TRIG_CONTROL1_REG &= (uint32)~BLETimer_CAPTURE_MASK;
    BLETimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLETimer_TRIG_LEVEL     - Level
*     - BLETimer_TRIG_RISING    - Rising edge
*     - BLETimer_TRIG_FALLING   - Falling edge
*     - BLETimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_TRIG_CONTROL1_REG &= (uint32)~BLETimer_RELOAD_MASK;
    BLETimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << BLETimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLETimer_TRIG_LEVEL     - Level
*     - BLETimer_TRIG_RISING    - Rising edge
*     - BLETimer_TRIG_FALLING   - Falling edge
*     - BLETimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_TRIG_CONTROL1_REG &= (uint32)~BLETimer_START_MASK;
    BLETimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << BLETimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLETimer_TRIG_LEVEL     - Level
*     - BLETimer_TRIG_RISING    - Rising edge
*     - BLETimer_TRIG_FALLING   - Falling edge
*     - BLETimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_TRIG_CONTROL1_REG &= (uint32)~BLETimer_STOP_MASK;
    BLETimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << BLETimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - BLETimer_TRIG_LEVEL     - Level
*     - BLETimer_TRIG_RISING    - Rising edge
*     - BLETimer_TRIG_FALLING   - Falling edge
*     - BLETimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_TRIG_CONTROL1_REG &= (uint32)~BLETimer_COUNT_MASK;
    BLETimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << BLETimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - BLETimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - BLETimer_CMD_RELOAD     - Trigger Reload/Index command
*     - BLETimer_CMD_STOP       - Trigger Stop/Kill command
*     - BLETimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    BLETimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLETimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the BLETimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - BLETimer_STATUS_DOWN    - Set if counting down
*     - BLETimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 BLETimer_ReadStatus(void)
{
    return ((BLETimer_STATUS_REG >> BLETimer_RUNNING_STATUS_SHIFT) |
            (BLETimer_STATUS_REG & BLETimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: BLETimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - BLETimer_INTR_MASK_TC       - Terminal count mask
*     - BLETimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetInterruptMode(uint32 interruptMask)
{
    BLETimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: BLETimer_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - BLETimer_INTR_MASK_TC       - Terminal count mask
*     - BLETimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 BLETimer_GetInterruptSourceMasked(void)
{
    return (BLETimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: BLETimer_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - BLETimer_INTR_MASK_TC       - Terminal count mask
*     - BLETimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 BLETimer_GetInterruptSource(void)
{
    return (BLETimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: BLETimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - BLETimer_INTR_MASK_TC       - Terminal count mask
*     - BLETimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_ClearInterrupt(uint32 interruptMask)
{
    BLETimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: BLETimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - BLETimer_INTR_MASK_TC       - Terminal count mask
*     - BLETimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void BLETimer_SetInterrupt(uint32 interruptMask)
{
    BLETimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
