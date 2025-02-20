/*******************************************************************************
* File Name: wakeUp.h  
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

#if !defined(CY_PINS_wakeUp_H) /* Pins wakeUp_H */
#define CY_PINS_wakeUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "wakeUp_aliases.h"


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
} wakeUp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   wakeUp_Read(void);
void    wakeUp_Write(uint8 value);
uint8   wakeUp_ReadDataReg(void);
#if defined(wakeUp__PC) || (CY_PSOC4_4200L) 
    void    wakeUp_SetDriveMode(uint8 mode);
#endif
void    wakeUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   wakeUp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void wakeUp_Sleep(void); 
void wakeUp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(wakeUp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define wakeUp_DRIVE_MODE_BITS        (3)
    #define wakeUp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - wakeUp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the wakeUp_SetDriveMode() function.
         *  @{
         */
        #define wakeUp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define wakeUp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define wakeUp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define wakeUp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define wakeUp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define wakeUp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define wakeUp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define wakeUp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define wakeUp_MASK               wakeUp__MASK
#define wakeUp_SHIFT              wakeUp__SHIFT
#define wakeUp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in wakeUp_SetInterruptMode() function.
     *  @{
     */
        #define wakeUp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define wakeUp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define wakeUp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define wakeUp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(wakeUp__SIO)
    #define wakeUp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(wakeUp__PC) && (CY_PSOC4_4200L)
    #define wakeUp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define wakeUp_USBIO_DISABLE              ((uint32)(~wakeUp_USBIO_ENABLE))
    #define wakeUp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define wakeUp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define wakeUp_USBIO_ENTER_SLEEP          ((uint32)((1u << wakeUp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << wakeUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define wakeUp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << wakeUp_USBIO_SUSPEND_SHIFT)))
    #define wakeUp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << wakeUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define wakeUp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(wakeUp__PC)
    /* Port Configuration */
    #define wakeUp_PC                 (* (reg32 *) wakeUp__PC)
#endif
/* Pin State */
#define wakeUp_PS                     (* (reg32 *) wakeUp__PS)
/* Data Register */
#define wakeUp_DR                     (* (reg32 *) wakeUp__DR)
/* Input Buffer Disable Override */
#define wakeUp_INP_DIS                (* (reg32 *) wakeUp__PC2)

/* Interrupt configuration Registers */
#define wakeUp_INTCFG                 (* (reg32 *) wakeUp__INTCFG)
#define wakeUp_INTSTAT                (* (reg32 *) wakeUp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define wakeUp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(wakeUp__SIO)
    #define wakeUp_SIO_REG            (* (reg32 *) wakeUp__SIO)
#endif /* (wakeUp__SIO_CFG) */

/* USBIO registers */
#if !defined(wakeUp__PC) && (CY_PSOC4_4200L)
    #define wakeUp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define wakeUp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define wakeUp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define wakeUp_DRIVE_MODE_SHIFT       (0x00u)
#define wakeUp_DRIVE_MODE_MASK        (0x07u << wakeUp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins wakeUp_H */


/* [] END OF FILE */
