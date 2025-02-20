/*******************************************************************************
* File Name: ModbusUART_rx_wake.c  
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
#include "ModbusUART_rx_wake.h"

static ModbusUART_rx_wake_BACKUP_STRUCT  ModbusUART_rx_wake_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: ModbusUART_rx_wake_Sleep
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
*  \snippet ModbusUART_rx_wake_SUT.c usage_ModbusUART_rx_wake_Sleep_Wakeup
*******************************************************************************/
void ModbusUART_rx_wake_Sleep(void)
{
    #if defined(ModbusUART_rx_wake__PC)
        ModbusUART_rx_wake_backup.pcState = ModbusUART_rx_wake_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            ModbusUART_rx_wake_backup.usbState = ModbusUART_rx_wake_CR1_REG;
            ModbusUART_rx_wake_USB_POWER_REG |= ModbusUART_rx_wake_USBIO_ENTER_SLEEP;
            ModbusUART_rx_wake_CR1_REG &= ModbusUART_rx_wake_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ModbusUART_rx_wake__SIO)
        ModbusUART_rx_wake_backup.sioState = ModbusUART_rx_wake_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        ModbusUART_rx_wake_SIO_REG &= (uint32)(~ModbusUART_rx_wake_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: ModbusUART_rx_wake_Wakeup
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
*  Refer to ModbusUART_rx_wake_Sleep() for an example usage.
*******************************************************************************/
void ModbusUART_rx_wake_Wakeup(void)
{
    #if defined(ModbusUART_rx_wake__PC)
        ModbusUART_rx_wake_PC = ModbusUART_rx_wake_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            ModbusUART_rx_wake_USB_POWER_REG &= ModbusUART_rx_wake_USBIO_EXIT_SLEEP_PH1;
            ModbusUART_rx_wake_CR1_REG = ModbusUART_rx_wake_backup.usbState;
            ModbusUART_rx_wake_USB_POWER_REG &= ModbusUART_rx_wake_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ModbusUART_rx_wake__SIO)
        ModbusUART_rx_wake_SIO_REG = ModbusUART_rx_wake_backup.sioState;
    #endif
}


/* [] END OF FILE */
