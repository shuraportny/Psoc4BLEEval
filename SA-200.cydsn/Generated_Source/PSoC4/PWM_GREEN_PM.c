/*******************************************************************************
* File Name: PWM_GREEN_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_GREEN.h"

static PWM_GREEN_backupStruct PWM_GREEN_backup;


/*******************************************************************************
* Function Name: PWM_GREEN_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GREEN_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_GREEN_SaveConfig(void) 
{

    #if(!PWM_GREEN_UsingFixedFunction)
        #if(!PWM_GREEN_PWMModeIsCenterAligned)
            PWM_GREEN_backup.PWMPeriod = PWM_GREEN_ReadPeriod();
        #endif /* (!PWM_GREEN_PWMModeIsCenterAligned) */
        PWM_GREEN_backup.PWMUdb = PWM_GREEN_ReadCounter();
        #if (PWM_GREEN_UseStatus)
            PWM_GREEN_backup.InterruptMaskValue = PWM_GREEN_STATUS_MASK;
        #endif /* (PWM_GREEN_UseStatus) */

        #if(PWM_GREEN_DeadBandMode == PWM_GREEN__B_PWM__DBM_256_CLOCKS || \
            PWM_GREEN_DeadBandMode == PWM_GREEN__B_PWM__DBM_2_4_CLOCKS)
            PWM_GREEN_backup.PWMdeadBandValue = PWM_GREEN_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_GREEN_KillModeMinTime)
             PWM_GREEN_backup.PWMKillCounterPeriod = PWM_GREEN_ReadKillTime();
        #endif /* (PWM_GREEN_KillModeMinTime) */

        #if(PWM_GREEN_UseControl)
            PWM_GREEN_backup.PWMControlRegister = PWM_GREEN_ReadControlRegister();
        #endif /* (PWM_GREEN_UseControl) */
    #endif  /* (!PWM_GREEN_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_GREEN_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GREEN_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_GREEN_RestoreConfig(void) 
{
        #if(!PWM_GREEN_UsingFixedFunction)
            #if(!PWM_GREEN_PWMModeIsCenterAligned)
                PWM_GREEN_WritePeriod(PWM_GREEN_backup.PWMPeriod);
            #endif /* (!PWM_GREEN_PWMModeIsCenterAligned) */

            PWM_GREEN_WriteCounter(PWM_GREEN_backup.PWMUdb);

            #if (PWM_GREEN_UseStatus)
                PWM_GREEN_STATUS_MASK = PWM_GREEN_backup.InterruptMaskValue;
            #endif /* (PWM_GREEN_UseStatus) */

            #if(PWM_GREEN_DeadBandMode == PWM_GREEN__B_PWM__DBM_256_CLOCKS || \
                PWM_GREEN_DeadBandMode == PWM_GREEN__B_PWM__DBM_2_4_CLOCKS)
                PWM_GREEN_WriteDeadTime(PWM_GREEN_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_GREEN_KillModeMinTime)
                PWM_GREEN_WriteKillTime(PWM_GREEN_backup.PWMKillCounterPeriod);
            #endif /* (PWM_GREEN_KillModeMinTime) */

            #if(PWM_GREEN_UseControl)
                PWM_GREEN_WriteControlRegister(PWM_GREEN_backup.PWMControlRegister);
            #endif /* (PWM_GREEN_UseControl) */
        #endif  /* (!PWM_GREEN_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_GREEN_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GREEN_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_GREEN_Sleep(void) 
{
    #if(PWM_GREEN_UseControl)
        if(PWM_GREEN_CTRL_ENABLE == (PWM_GREEN_CONTROL & PWM_GREEN_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_GREEN_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_GREEN_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_GREEN_UseControl) */

    /* Stop component */
    PWM_GREEN_Stop();

    /* Save registers configuration */
    PWM_GREEN_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_GREEN_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GREEN_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_GREEN_Wakeup(void) 
{
     /* Restore registers values */
    PWM_GREEN_RestoreConfig();

    if(PWM_GREEN_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_GREEN_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
