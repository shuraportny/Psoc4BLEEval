/*******************************************************************************
* File Name: Control1_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Control1.h"

/* Check for removal by optimization */
#if !defined(Control1_Sync_ctrl_reg__REMOVED)

static Control1_BACKUP_STRUCT  Control1_backup = {0u};

    
/*******************************************************************************
* Function Name: Control1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control1_SaveConfig(void) 
{
    Control1_backup.controlState = Control1_Control;
}


/*******************************************************************************
* Function Name: Control1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Control1_RestoreConfig(void) 
{
     Control1_Control = Control1_backup.controlState;
}


/*******************************************************************************
* Function Name: Control1_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control1_Sleep(void) 
{
    Control1_SaveConfig();
}


/*******************************************************************************
* Function Name: Control1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control1_Wakeup(void)  
{
    Control1_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
