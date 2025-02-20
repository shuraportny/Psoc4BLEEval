/*******************************************************************************
* File Name: BLETimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the BLETimer
*  component.
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

#if !defined(CY_TCPWM_BLETimer_H)
#define CY_TCPWM_BLETimer_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} BLETimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  BLETimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define BLETimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define BLETimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define BLETimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define BLETimer_QUAD_ENCODING_MODES            (0lu)
#define BLETimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define BLETimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define BLETimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define BLETimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define BLETimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define BLETimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define BLETimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define BLETimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define BLETimer_TC_RUN_MODE                    (1lu)
#define BLETimer_TC_COUNTER_MODE                (0lu)
#define BLETimer_TC_COMP_CAP_MODE               (2lu)
#define BLETimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define BLETimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define BLETimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define BLETimer_TC_START_SIGNAL_MODE           (0lu)
#define BLETimer_TC_STOP_SIGNAL_MODE            (0lu)
#define BLETimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define BLETimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define BLETimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define BLETimer_TC_START_SIGNAL_PRESENT        (0lu)
#define BLETimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define BLETimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BLETimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define BLETimer_PWM_KILL_EVENT                 (0lu)
#define BLETimer_PWM_STOP_EVENT                 (0lu)
#define BLETimer_PWM_MODE                       (4lu)
#define BLETimer_PWM_OUT_N_INVERT               (0lu)
#define BLETimer_PWM_OUT_INVERT                 (0lu)
#define BLETimer_PWM_ALIGN                      (0lu)
#define BLETimer_PWM_RUN_MODE                   (0lu)
#define BLETimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define BLETimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define BLETimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define BLETimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define BLETimer_PWM_START_SIGNAL_MODE          (0lu)
#define BLETimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define BLETimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define BLETimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define BLETimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define BLETimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define BLETimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define BLETimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BLETimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define BLETimer_TC_PERIOD_VALUE                (20000lu)
#define BLETimer_TC_COMPARE_VALUE               (65535lu)
#define BLETimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define BLETimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define BLETimer_PWM_PERIOD_VALUE               (65535lu)
#define BLETimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define BLETimer_PWM_PERIOD_SWAP                (0lu)
#define BLETimer_PWM_COMPARE_VALUE              (65535lu)
#define BLETimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define BLETimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define BLETimer__LEFT 0
#define BLETimer__RIGHT 1
#define BLETimer__CENTER 2
#define BLETimer__ASYMMETRIC 3

#define BLETimer__X1 0
#define BLETimer__X2 1
#define BLETimer__X4 2

#define BLETimer__PWM 4
#define BLETimer__PWM_DT 5
#define BLETimer__PWM_PR 6

#define BLETimer__INVERSE 1
#define BLETimer__DIRECT 0

#define BLETimer__CAPTURE 2
#define BLETimer__COMPARE 0

#define BLETimer__TRIG_LEVEL 3
#define BLETimer__TRIG_RISING 0
#define BLETimer__TRIG_FALLING 1
#define BLETimer__TRIG_BOTH 2

#define BLETimer__INTR_MASK_TC 1
#define BLETimer__INTR_MASK_CC_MATCH 2
#define BLETimer__INTR_MASK_NONE 0
#define BLETimer__INTR_MASK_TC_CC 3

#define BLETimer__UNCONFIG 8
#define BLETimer__TIMER 1
#define BLETimer__QUAD 3
#define BLETimer__PWM_SEL 7

#define BLETimer__COUNT_UP 0
#define BLETimer__COUNT_DOWN 1
#define BLETimer__COUNT_UPDOWN0 2
#define BLETimer__COUNT_UPDOWN1 3


/* Prescaler */
#define BLETimer_PRESCALE_DIVBY1                ((uint32)(0u << BLETimer_PRESCALER_SHIFT))
#define BLETimer_PRESCALE_DIVBY2                ((uint32)(1u << BLETimer_PRESCALER_SHIFT))
#define BLETimer_PRESCALE_DIVBY4                ((uint32)(2u << BLETimer_PRESCALER_SHIFT))
#define BLETimer_PRESCALE_DIVBY8                ((uint32)(3u << BLETimer_PRESCALER_SHIFT))
#define BLETimer_PRESCALE_DIVBY16               ((uint32)(4u << BLETimer_PRESCALER_SHIFT))
#define BLETimer_PRESCALE_DIVBY32               ((uint32)(5u << BLETimer_PRESCALER_SHIFT))
#define BLETimer_PRESCALE_DIVBY64               ((uint32)(6u << BLETimer_PRESCALER_SHIFT))
#define BLETimer_PRESCALE_DIVBY128              ((uint32)(7u << BLETimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define BLETimer_MODE_TIMER_COMPARE             ((uint32)(BLETimer__COMPARE         <<  \
                                                                  BLETimer_MODE_SHIFT))
#define BLETimer_MODE_TIMER_CAPTURE             ((uint32)(BLETimer__CAPTURE         <<  \
                                                                  BLETimer_MODE_SHIFT))
#define BLETimer_MODE_QUAD                      ((uint32)(BLETimer__QUAD            <<  \
                                                                  BLETimer_MODE_SHIFT))
#define BLETimer_MODE_PWM                       ((uint32)(BLETimer__PWM             <<  \
                                                                  BLETimer_MODE_SHIFT))
#define BLETimer_MODE_PWM_DT                    ((uint32)(BLETimer__PWM_DT          <<  \
                                                                  BLETimer_MODE_SHIFT))
#define BLETimer_MODE_PWM_PR                    ((uint32)(BLETimer__PWM_PR          <<  \
                                                                  BLETimer_MODE_SHIFT))

/* Quad Modes */
#define BLETimer_MODE_X1                        ((uint32)(BLETimer__X1              <<  \
                                                                  BLETimer_QUAD_MODE_SHIFT))
#define BLETimer_MODE_X2                        ((uint32)(BLETimer__X2              <<  \
                                                                  BLETimer_QUAD_MODE_SHIFT))
#define BLETimer_MODE_X4                        ((uint32)(BLETimer__X4              <<  \
                                                                  BLETimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define BLETimer_COUNT_UP                       ((uint32)(BLETimer__COUNT_UP        <<  \
                                                                  BLETimer_UPDOWN_SHIFT))
#define BLETimer_COUNT_DOWN                     ((uint32)(BLETimer__COUNT_DOWN      <<  \
                                                                  BLETimer_UPDOWN_SHIFT))
#define BLETimer_COUNT_UPDOWN0                  ((uint32)(BLETimer__COUNT_UPDOWN0   <<  \
                                                                  BLETimer_UPDOWN_SHIFT))
#define BLETimer_COUNT_UPDOWN1                  ((uint32)(BLETimer__COUNT_UPDOWN1   <<  \
                                                                  BLETimer_UPDOWN_SHIFT))

/* PWM output invert */
#define BLETimer_INVERT_LINE                    ((uint32)(BLETimer__INVERSE         <<  \
                                                                  BLETimer_INV_OUT_SHIFT))
#define BLETimer_INVERT_LINE_N                  ((uint32)(BLETimer__INVERSE         <<  \
                                                                  BLETimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define BLETimer_TRIG_RISING                    ((uint32)BLETimer__TRIG_RISING)
#define BLETimer_TRIG_FALLING                   ((uint32)BLETimer__TRIG_FALLING)
#define BLETimer_TRIG_BOTH                      ((uint32)BLETimer__TRIG_BOTH)
#define BLETimer_TRIG_LEVEL                     ((uint32)BLETimer__TRIG_LEVEL)

/* Interrupt mask */
#define BLETimer_INTR_MASK_TC                   ((uint32)BLETimer__INTR_MASK_TC)
#define BLETimer_INTR_MASK_CC_MATCH             ((uint32)BLETimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define BLETimer_CC_MATCH_SET                   (0x00u)
#define BLETimer_CC_MATCH_CLEAR                 (0x01u)
#define BLETimer_CC_MATCH_INVERT                (0x02u)
#define BLETimer_CC_MATCH_NO_CHANGE             (0x03u)
#define BLETimer_OVERLOW_SET                    (0x00u)
#define BLETimer_OVERLOW_CLEAR                  (0x04u)
#define BLETimer_OVERLOW_INVERT                 (0x08u)
#define BLETimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define BLETimer_UNDERFLOW_SET                  (0x00u)
#define BLETimer_UNDERFLOW_CLEAR                (0x10u)
#define BLETimer_UNDERFLOW_INVERT               (0x20u)
#define BLETimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define BLETimer_PWM_MODE_LEFT                  (BLETimer_CC_MATCH_CLEAR        |   \
                                                         BLETimer_OVERLOW_SET           |   \
                                                         BLETimer_UNDERFLOW_NO_CHANGE)
#define BLETimer_PWM_MODE_RIGHT                 (BLETimer_CC_MATCH_SET          |   \
                                                         BLETimer_OVERLOW_NO_CHANGE     |   \
                                                         BLETimer_UNDERFLOW_CLEAR)
#define BLETimer_PWM_MODE_ASYM                  (BLETimer_CC_MATCH_INVERT       |   \
                                                         BLETimer_OVERLOW_SET           |   \
                                                         BLETimer_UNDERFLOW_CLEAR)

#if (BLETimer_CY_TCPWM_V2)
    #if(BLETimer_CY_TCPWM_4000)
        #define BLETimer_PWM_MODE_CENTER                (BLETimer_CC_MATCH_INVERT       |   \
                                                                 BLETimer_OVERLOW_NO_CHANGE     |   \
                                                                 BLETimer_UNDERFLOW_CLEAR)
    #else
        #define BLETimer_PWM_MODE_CENTER                (BLETimer_CC_MATCH_INVERT       |   \
                                                                 BLETimer_OVERLOW_SET           |   \
                                                                 BLETimer_UNDERFLOW_CLEAR)
    #endif /* (BLETimer_CY_TCPWM_4000) */
#else
    #define BLETimer_PWM_MODE_CENTER                (BLETimer_CC_MATCH_INVERT       |   \
                                                             BLETimer_OVERLOW_NO_CHANGE     |   \
                                                             BLETimer_UNDERFLOW_CLEAR)
#endif /* (BLETimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define BLETimer_CMD_CAPTURE                    (0u)
#define BLETimer_CMD_RELOAD                     (8u)
#define BLETimer_CMD_STOP                       (16u)
#define BLETimer_CMD_START                      (24u)

/* Status */
#define BLETimer_STATUS_DOWN                    (1u)
#define BLETimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   BLETimer_Init(void);
void   BLETimer_Enable(void);
void   BLETimer_Start(void);
void   BLETimer_Stop(void);

void   BLETimer_SetMode(uint32 mode);
void   BLETimer_SetCounterMode(uint32 counterMode);
void   BLETimer_SetPWMMode(uint32 modeMask);
void   BLETimer_SetQDMode(uint32 qdMode);

void   BLETimer_SetPrescaler(uint32 prescaler);
void   BLETimer_TriggerCommand(uint32 mask, uint32 command);
void   BLETimer_SetOneShot(uint32 oneShotEnable);
uint32 BLETimer_ReadStatus(void);

void   BLETimer_SetPWMSyncKill(uint32 syncKillEnable);
void   BLETimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   BLETimer_SetPWMDeadTime(uint32 deadTime);
void   BLETimer_SetPWMInvert(uint32 mask);

void   BLETimer_SetInterruptMode(uint32 interruptMask);
uint32 BLETimer_GetInterruptSourceMasked(void);
uint32 BLETimer_GetInterruptSource(void);
void   BLETimer_ClearInterrupt(uint32 interruptMask);
void   BLETimer_SetInterrupt(uint32 interruptMask);

void   BLETimer_WriteCounter(uint32 count);
uint32 BLETimer_ReadCounter(void);

uint32 BLETimer_ReadCapture(void);
uint32 BLETimer_ReadCaptureBuf(void);

void   BLETimer_WritePeriod(uint32 period);
uint32 BLETimer_ReadPeriod(void);
void   BLETimer_WritePeriodBuf(uint32 periodBuf);
uint32 BLETimer_ReadPeriodBuf(void);

void   BLETimer_WriteCompare(uint32 compare);
uint32 BLETimer_ReadCompare(void);
void   BLETimer_WriteCompareBuf(uint32 compareBuf);
uint32 BLETimer_ReadCompareBuf(void);

void   BLETimer_SetPeriodSwap(uint32 swapEnable);
void   BLETimer_SetCompareSwap(uint32 swapEnable);

void   BLETimer_SetCaptureMode(uint32 triggerMode);
void   BLETimer_SetReloadMode(uint32 triggerMode);
void   BLETimer_SetStartMode(uint32 triggerMode);
void   BLETimer_SetStopMode(uint32 triggerMode);
void   BLETimer_SetCountMode(uint32 triggerMode);

void   BLETimer_SaveConfig(void);
void   BLETimer_RestoreConfig(void);
void   BLETimer_Sleep(void);
void   BLETimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define BLETimer_BLOCK_CONTROL_REG              (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BLETimer_BLOCK_CONTROL_PTR              ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BLETimer_COMMAND_REG                    (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BLETimer_COMMAND_PTR                    ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BLETimer_INTRRUPT_CAUSE_REG             (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BLETimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BLETimer_CONTROL_REG                    (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__CTRL )
#define BLETimer_CONTROL_PTR                    ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__CTRL )
#define BLETimer_STATUS_REG                     (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__STATUS )
#define BLETimer_STATUS_PTR                     ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__STATUS )
#define BLETimer_COUNTER_REG                    (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__COUNTER )
#define BLETimer_COUNTER_PTR                    ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__COUNTER )
#define BLETimer_COMP_CAP_REG                   (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__CC )
#define BLETimer_COMP_CAP_PTR                   ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__CC )
#define BLETimer_COMP_CAP_BUF_REG               (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define BLETimer_COMP_CAP_BUF_PTR               ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define BLETimer_PERIOD_REG                     (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__PERIOD )
#define BLETimer_PERIOD_PTR                     ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__PERIOD )
#define BLETimer_PERIOD_BUF_REG                 (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BLETimer_PERIOD_BUF_PTR                 ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BLETimer_TRIG_CONTROL0_REG              (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BLETimer_TRIG_CONTROL0_PTR              ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BLETimer_TRIG_CONTROL1_REG              (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BLETimer_TRIG_CONTROL1_PTR              ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BLETimer_TRIG_CONTROL2_REG              (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BLETimer_TRIG_CONTROL2_PTR              ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BLETimer_INTERRUPT_REQ_REG              (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__INTR )
#define BLETimer_INTERRUPT_REQ_PTR              ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__INTR )
#define BLETimer_INTERRUPT_SET_REG              (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__INTR_SET )
#define BLETimer_INTERRUPT_SET_PTR              ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__INTR_SET )
#define BLETimer_INTERRUPT_MASK_REG             (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define BLETimer_INTERRUPT_MASK_PTR             ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define BLETimer_INTERRUPT_MASKED_REG           (*(reg32 *) BLETimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define BLETimer_INTERRUPT_MASKED_PTR           ( (reg32 *) BLETimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define BLETimer_MASK                           ((uint32)BLETimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define BLETimer_RELOAD_CC_SHIFT                (0u)
#define BLETimer_RELOAD_PERIOD_SHIFT            (1u)
#define BLETimer_PWM_SYNC_KILL_SHIFT            (2u)
#define BLETimer_PWM_STOP_KILL_SHIFT            (3u)
#define BLETimer_PRESCALER_SHIFT                (8u)
#define BLETimer_UPDOWN_SHIFT                   (16u)
#define BLETimer_ONESHOT_SHIFT                  (18u)
#define BLETimer_QUAD_MODE_SHIFT                (20u)
#define BLETimer_INV_OUT_SHIFT                  (20u)
#define BLETimer_INV_COMPL_OUT_SHIFT            (21u)
#define BLETimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define BLETimer_RELOAD_CC_MASK                 ((uint32)(BLETimer_1BIT_MASK        <<  \
                                                                            BLETimer_RELOAD_CC_SHIFT))
#define BLETimer_RELOAD_PERIOD_MASK             ((uint32)(BLETimer_1BIT_MASK        <<  \
                                                                            BLETimer_RELOAD_PERIOD_SHIFT))
#define BLETimer_PWM_SYNC_KILL_MASK             ((uint32)(BLETimer_1BIT_MASK        <<  \
                                                                            BLETimer_PWM_SYNC_KILL_SHIFT))
#define BLETimer_PWM_STOP_KILL_MASK             ((uint32)(BLETimer_1BIT_MASK        <<  \
                                                                            BLETimer_PWM_STOP_KILL_SHIFT))
#define BLETimer_PRESCALER_MASK                 ((uint32)(BLETimer_8BIT_MASK        <<  \
                                                                            BLETimer_PRESCALER_SHIFT))
#define BLETimer_UPDOWN_MASK                    ((uint32)(BLETimer_2BIT_MASK        <<  \
                                                                            BLETimer_UPDOWN_SHIFT))
#define BLETimer_ONESHOT_MASK                   ((uint32)(BLETimer_1BIT_MASK        <<  \
                                                                            BLETimer_ONESHOT_SHIFT))
#define BLETimer_QUAD_MODE_MASK                 ((uint32)(BLETimer_3BIT_MASK        <<  \
                                                                            BLETimer_QUAD_MODE_SHIFT))
#define BLETimer_INV_OUT_MASK                   ((uint32)(BLETimer_2BIT_MASK        <<  \
                                                                            BLETimer_INV_OUT_SHIFT))
#define BLETimer_MODE_MASK                      ((uint32)(BLETimer_3BIT_MASK        <<  \
                                                                            BLETimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define BLETimer_CAPTURE_SHIFT                  (0u)
#define BLETimer_COUNT_SHIFT                    (2u)
#define BLETimer_RELOAD_SHIFT                   (4u)
#define BLETimer_STOP_SHIFT                     (6u)
#define BLETimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define BLETimer_CAPTURE_MASK                   ((uint32)(BLETimer_2BIT_MASK        <<  \
                                                                  BLETimer_CAPTURE_SHIFT))
#define BLETimer_COUNT_MASK                     ((uint32)(BLETimer_2BIT_MASK        <<  \
                                                                  BLETimer_COUNT_SHIFT))
#define BLETimer_RELOAD_MASK                    ((uint32)(BLETimer_2BIT_MASK        <<  \
                                                                  BLETimer_RELOAD_SHIFT))
#define BLETimer_STOP_MASK                      ((uint32)(BLETimer_2BIT_MASK        <<  \
                                                                  BLETimer_STOP_SHIFT))
#define BLETimer_START_MASK                     ((uint32)(BLETimer_2BIT_MASK        <<  \
                                                                  BLETimer_START_SHIFT))

/* MASK */
#define BLETimer_1BIT_MASK                      ((uint32)0x01u)
#define BLETimer_2BIT_MASK                      ((uint32)0x03u)
#define BLETimer_3BIT_MASK                      ((uint32)0x07u)
#define BLETimer_6BIT_MASK                      ((uint32)0x3Fu)
#define BLETimer_8BIT_MASK                      ((uint32)0xFFu)
#define BLETimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define BLETimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define BLETimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(BLETimer_QUAD_ENCODING_MODES     << BLETimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(BLETimer_CONFIG                  << BLETimer_MODE_SHIFT)))

#define BLETimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(BLETimer_PWM_STOP_EVENT          << BLETimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(BLETimer_PWM_OUT_INVERT          << BLETimer_INV_OUT_SHIFT))         |\
         ((uint32)(BLETimer_PWM_OUT_N_INVERT        << BLETimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(BLETimer_PWM_MODE                << BLETimer_MODE_SHIFT)))

#define BLETimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(BLETimer_PWM_RUN_MODE         << BLETimer_ONESHOT_SHIFT))
            
#define BLETimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(BLETimer_PWM_ALIGN            << BLETimer_UPDOWN_SHIFT))

#define BLETimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(BLETimer_PWM_KILL_EVENT      << BLETimer_PWM_SYNC_KILL_SHIFT))

#define BLETimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(BLETimer_PWM_DEAD_TIME_CYCLE  << BLETimer_PRESCALER_SHIFT))

#define BLETimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(BLETimer_PWM_PRESCALER        << BLETimer_PRESCALER_SHIFT))

#define BLETimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(BLETimer_TC_PRESCALER            << BLETimer_PRESCALER_SHIFT))       |\
         ((uint32)(BLETimer_TC_COUNTER_MODE         << BLETimer_UPDOWN_SHIFT))          |\
         ((uint32)(BLETimer_TC_RUN_MODE             << BLETimer_ONESHOT_SHIFT))         |\
         ((uint32)(BLETimer_TC_COMP_CAP_MODE        << BLETimer_MODE_SHIFT)))
        
#define BLETimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(BLETimer_QUAD_PHIA_SIGNAL_MODE   << BLETimer_COUNT_SHIFT))           |\
         ((uint32)(BLETimer_QUAD_INDEX_SIGNAL_MODE  << BLETimer_RELOAD_SHIFT))          |\
         ((uint32)(BLETimer_QUAD_STOP_SIGNAL_MODE   << BLETimer_STOP_SHIFT))            |\
         ((uint32)(BLETimer_QUAD_PHIB_SIGNAL_MODE   << BLETimer_START_SHIFT)))

#define BLETimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(BLETimer_PWM_SWITCH_SIGNAL_MODE  << BLETimer_CAPTURE_SHIFT))         |\
         ((uint32)(BLETimer_PWM_COUNT_SIGNAL_MODE   << BLETimer_COUNT_SHIFT))           |\
         ((uint32)(BLETimer_PWM_RELOAD_SIGNAL_MODE  << BLETimer_RELOAD_SHIFT))          |\
         ((uint32)(BLETimer_PWM_STOP_SIGNAL_MODE    << BLETimer_STOP_SHIFT))            |\
         ((uint32)(BLETimer_PWM_START_SIGNAL_MODE   << BLETimer_START_SHIFT)))

#define BLETimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(BLETimer_TC_CAPTURE_SIGNAL_MODE  << BLETimer_CAPTURE_SHIFT))         |\
         ((uint32)(BLETimer_TC_COUNT_SIGNAL_MODE    << BLETimer_COUNT_SHIFT))           |\
         ((uint32)(BLETimer_TC_RELOAD_SIGNAL_MODE   << BLETimer_RELOAD_SHIFT))          |\
         ((uint32)(BLETimer_TC_STOP_SIGNAL_MODE     << BLETimer_STOP_SHIFT))            |\
         ((uint32)(BLETimer_TC_START_SIGNAL_MODE    << BLETimer_START_SHIFT)))
        
#define BLETimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((BLETimer__COUNT_UPDOWN0 == BLETimer_TC_COUNTER_MODE)                  ||\
                 (BLETimer__COUNT_UPDOWN1 == BLETimer_TC_COUNTER_MODE))

#define BLETimer_PWM_UPDOWN_CNT_USED                                                            \
                ((BLETimer__CENTER == BLETimer_PWM_ALIGN)                               ||\
                 (BLETimer__ASYMMETRIC == BLETimer_PWM_ALIGN))               
        
#define BLETimer_PWM_PR_INIT_VALUE              (1u)
#define BLETimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_BLETimer_H */

/* [] END OF FILE */
