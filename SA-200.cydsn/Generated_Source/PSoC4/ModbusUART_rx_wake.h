/*******************************************************************************
* File Name: ModbusUART_rx_wake.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ModbusUART_rx_wake_H) /* Pins ModbusUART_rx_wake_H */
#define CY_PINS_ModbusUART_rx_wake_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ModbusUART_rx_wake_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} ModbusUART_rx_wake_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ModbusUART_rx_wake_Read(void);
void    ModbusUART_rx_wake_Write(uint8 value);
uint8   ModbusUART_rx_wake_ReadDataReg(void);
#if defined(ModbusUART_rx_wake__PC) || (CY_PSOC4_4200L) 
    void    ModbusUART_rx_wake_SetDriveMode(uint8 mode);
#endif
void    ModbusUART_rx_wake_SetInterruptMode(uint16 position, uint16 mode);
uint8   ModbusUART_rx_wake_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ModbusUART_rx_wake_Sleep(void); 
void ModbusUART_rx_wake_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ModbusUART_rx_wake__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ModbusUART_rx_wake_DRIVE_MODE_BITS        (3)
    #define ModbusUART_rx_wake_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ModbusUART_rx_wake_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ModbusUART_rx_wake_SetDriveMode() function.
         *  @{
         */
        #define ModbusUART_rx_wake_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ModbusUART_rx_wake_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ModbusUART_rx_wake_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ModbusUART_rx_wake_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ModbusUART_rx_wake_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ModbusUART_rx_wake_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ModbusUART_rx_wake_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ModbusUART_rx_wake_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ModbusUART_rx_wake_MASK               ModbusUART_rx_wake__MASK
#define ModbusUART_rx_wake_SHIFT              ModbusUART_rx_wake__SHIFT
#define ModbusUART_rx_wake_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ModbusUART_rx_wake_SetInterruptMode() function.
     *  @{
     */
        #define ModbusUART_rx_wake_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ModbusUART_rx_wake_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ModbusUART_rx_wake_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ModbusUART_rx_wake_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ModbusUART_rx_wake__SIO)
    #define ModbusUART_rx_wake_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ModbusUART_rx_wake__PC) && (CY_PSOC4_4200L)
    #define ModbusUART_rx_wake_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ModbusUART_rx_wake_USBIO_DISABLE              ((uint32)(~ModbusUART_rx_wake_USBIO_ENABLE))
    #define ModbusUART_rx_wake_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ModbusUART_rx_wake_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ModbusUART_rx_wake_USBIO_ENTER_SLEEP          ((uint32)((1u << ModbusUART_rx_wake_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ModbusUART_rx_wake_USBIO_SUSPEND_DEL_SHIFT)))
    #define ModbusUART_rx_wake_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ModbusUART_rx_wake_USBIO_SUSPEND_SHIFT)))
    #define ModbusUART_rx_wake_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ModbusUART_rx_wake_USBIO_SUSPEND_DEL_SHIFT)))
    #define ModbusUART_rx_wake_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ModbusUART_rx_wake__PC)
    /* Port Configuration */
    #define ModbusUART_rx_wake_PC                 (* (reg32 *) ModbusUART_rx_wake__PC)
#endif
/* Pin State */
#define ModbusUART_rx_wake_PS                     (* (reg32 *) ModbusUART_rx_wake__PS)
/* Data Register */
#define ModbusUART_rx_wake_DR                     (* (reg32 *) ModbusUART_rx_wake__DR)
/* Input Buffer Disable Override */
#define ModbusUART_rx_wake_INP_DIS                (* (reg32 *) ModbusUART_rx_wake__PC2)

/* Interrupt configuration Registers */
#define ModbusUART_rx_wake_INTCFG                 (* (reg32 *) ModbusUART_rx_wake__INTCFG)
#define ModbusUART_rx_wake_INTSTAT                (* (reg32 *) ModbusUART_rx_wake__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ModbusUART_rx_wake_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ModbusUART_rx_wake__SIO)
    #define ModbusUART_rx_wake_SIO_REG            (* (reg32 *) ModbusUART_rx_wake__SIO)
#endif /* (ModbusUART_rx_wake__SIO_CFG) */

/* USBIO registers */
#if !defined(ModbusUART_rx_wake__PC) && (CY_PSOC4_4200L)
    #define ModbusUART_rx_wake_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ModbusUART_rx_wake_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ModbusUART_rx_wake_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ModbusUART_rx_wake_DRIVE_MODE_SHIFT       (0x00u)
#define ModbusUART_rx_wake_DRIVE_MODE_MASK        (0x07u << ModbusUART_rx_wake_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ModbusUART_rx_wake_H */


/* [] END OF FILE */
