/*******************************************************************************
* File Name: PWM_BLINK_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

#include "PWM_BLINK.h"

static PWM_BLINK_BACKUP_STRUCT PWM_BLINK_backup;


/*******************************************************************************
* Function Name: PWM_BLINK_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_BLINK_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_BLINK_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_BLINK_Sleep(void)
{
    if(0u != (PWM_BLINK_BLOCK_CONTROL_REG & PWM_BLINK_MASK))
    {
        PWM_BLINK_backup.enableState = 1u;
    }
    else
    {
        PWM_BLINK_backup.enableState = 0u;
    }

    PWM_BLINK_Stop();
    PWM_BLINK_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_BLINK_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_BLINK_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_BLINK_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_BLINK_Wakeup(void)
{
    PWM_BLINK_RestoreConfig();

    if(0u != PWM_BLINK_backup.enableState)
    {
        PWM_BLINK_Enable();
    }
}


/* [] END OF FILE */
