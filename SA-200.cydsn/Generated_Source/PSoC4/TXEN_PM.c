/*******************************************************************************
* File Name: TXEN.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "TXEN.h"

static TXEN_BACKUP_STRUCT  TXEN_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: TXEN_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet TXEN_SUT.c usage_TXEN_Sleep_Wakeup
*******************************************************************************/
void TXEN_Sleep(void)
{
    #if defined(TXEN__PC)
        TXEN_backup.pcState = TXEN_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            TXEN_backup.usbState = TXEN_CR1_REG;
            TXEN_USB_POWER_REG |= TXEN_USBIO_ENTER_SLEEP;
            TXEN_CR1_REG &= TXEN_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TXEN__SIO)
        TXEN_backup.sioState = TXEN_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        TXEN_SIO_REG &= (uint32)(~TXEN_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: TXEN_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to TXEN_Sleep() for an example usage.
*******************************************************************************/
void TXEN_Wakeup(void)
{
    #if defined(TXEN__PC)
        TXEN_PC = TXEN_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            TXEN_USB_POWER_REG &= TXEN_USBIO_EXIT_SLEEP_PH1;
            TXEN_CR1_REG = TXEN_backup.usbState;
            TXEN_USB_POWER_REG &= TXEN_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TXEN__SIO)
        TXEN_SIO_REG = TXEN_backup.sioState;
    #endif
}


/* [] END OF FILE */
