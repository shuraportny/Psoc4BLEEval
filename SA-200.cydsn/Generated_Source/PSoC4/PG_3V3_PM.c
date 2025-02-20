/*******************************************************************************
* File Name: PG_3V3.c  
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
#include "PG_3V3.h"

static PG_3V3_BACKUP_STRUCT  PG_3V3_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PG_3V3_Sleep
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
*  \snippet PG_3V3_SUT.c usage_PG_3V3_Sleep_Wakeup
*******************************************************************************/
void PG_3V3_Sleep(void)
{
    #if defined(PG_3V3__PC)
        PG_3V3_backup.pcState = PG_3V3_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PG_3V3_backup.usbState = PG_3V3_CR1_REG;
            PG_3V3_USB_POWER_REG |= PG_3V3_USBIO_ENTER_SLEEP;
            PG_3V3_CR1_REG &= PG_3V3_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PG_3V3__SIO)
        PG_3V3_backup.sioState = PG_3V3_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PG_3V3_SIO_REG &= (uint32)(~PG_3V3_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PG_3V3_Wakeup
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
*  Refer to PG_3V3_Sleep() for an example usage.
*******************************************************************************/
void PG_3V3_Wakeup(void)
{
    #if defined(PG_3V3__PC)
        PG_3V3_PC = PG_3V3_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PG_3V3_USB_POWER_REG &= PG_3V3_USBIO_EXIT_SLEEP_PH1;
            PG_3V3_CR1_REG = PG_3V3_backup.usbState;
            PG_3V3_USB_POWER_REG &= PG_3V3_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PG_3V3__SIO)
        PG_3V3_SIO_REG = PG_3V3_backup.sioState;
    #endif
}


/* [] END OF FILE */
