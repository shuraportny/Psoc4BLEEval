/*******************************************************************************
* File Name: BLETimer_PM.c
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

#include "BLETimer.h"

static BLETimer_BACKUP_STRUCT BLETimer_backup;


/*******************************************************************************
* Function Name: BLETimer_SaveConfig
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
void BLETimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: BLETimer_Sleep
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
void BLETimer_Sleep(void)
{
    if(0u != (BLETimer_BLOCK_CONTROL_REG & BLETimer_MASK))
    {
        BLETimer_backup.enableState = 1u;
    }
    else
    {
        BLETimer_backup.enableState = 0u;
    }

    BLETimer_Stop();
    BLETimer_SaveConfig();
}


/*******************************************************************************
* Function Name: BLETimer_RestoreConfig
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
void BLETimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: BLETimer_Wakeup
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
void BLETimer_Wakeup(void)
{
    BLETimer_RestoreConfig();

    if(0u != BLETimer_backup.enableState)
    {
        BLETimer_Enable();
    }
}


/* [] END OF FILE */
