/*******************************************************************************
* File Name: UART2_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART2.h"


/***************************************
* Local data allocation
***************************************/

static UART2_BACKUP_STRUCT  UART2_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART2_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the UART2_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART2_SaveConfig(void)
{
    #if(UART2_CONTROL_REG_REMOVED == 0u)
        UART2_backup.cr = UART2_CONTROL_REG;
    #endif /* End UART2_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling UART2_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void UART2_RestoreConfig(void)
{
    #if(UART2_CONTROL_REG_REMOVED == 0u)
        UART2_CONTROL_REG = UART2_backup.cr;
    #endif /* End UART2_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART2_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UART2_Sleep() API saves the current component state. Then it
*  calls the UART2_Stop() function and calls 
*  UART2_SaveConfig() to save the hardware configuration.
*  Call the UART2_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART2_Sleep(void)
{
    #if(UART2_RX_ENABLED || UART2_HD_ENABLED)
        if((UART2_RXSTATUS_ACTL_REG  & UART2_INT_ENABLE) != 0u)
        {
            UART2_backup.enableState = 1u;
        }
        else
        {
            UART2_backup.enableState = 0u;
        }
    #else
        if((UART2_TXSTATUS_ACTL_REG  & UART2_INT_ENABLE) !=0u)
        {
            UART2_backup.enableState = 1u;
        }
        else
        {
            UART2_backup.enableState = 0u;
        }
    #endif /* End UART2_RX_ENABLED || UART2_HD_ENABLED*/

    UART2_Stop();
    UART2_SaveConfig();
}


/*******************************************************************************
* Function Name: UART2_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UART2_Sleep() was called. The UART2_Wakeup() function
*  calls the UART2_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UART2_Sleep() function was called, the UART2_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART2_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART2_Wakeup(void)
{
    UART2_RestoreConfig();
    #if( (UART2_RX_ENABLED) || (UART2_HD_ENABLED) )
        UART2_ClearRxBuffer();
    #endif /* End (UART2_RX_ENABLED) || (UART2_HD_ENABLED) */
    #if(UART2_TX_ENABLED || UART2_HD_ENABLED)
        UART2_ClearTxBuffer();
    #endif /* End UART2_TX_ENABLED || UART2_HD_ENABLED */

    if(UART2_backup.enableState != 0u)
    {
        UART2_Enable();
    }
}


/* [] END OF FILE */
