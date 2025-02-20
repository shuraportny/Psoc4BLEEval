/*******************************************************************************
* File Name: ss.h  
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

#if !defined(CY_PINS_ss_H) /* Pins ss_H */
#define CY_PINS_ss_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ss_aliases.h"


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
} ss_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ss_Read(void);
void    ss_Write(uint8 value);
uint8   ss_ReadDataReg(void);
#if defined(ss__PC) || (CY_PSOC4_4200L) 
    void    ss_SetDriveMode(uint8 mode);
#endif
void    ss_SetInterruptMode(uint16 position, uint16 mode);
uint8   ss_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ss_Sleep(void); 
void ss_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ss__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ss_DRIVE_MODE_BITS        (3)
    #define ss_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ss_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ss_SetDriveMode() function.
         *  @{
         */
        #define ss_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ss_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ss_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ss_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ss_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ss_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ss_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ss_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ss_MASK               ss__MASK
#define ss_SHIFT              ss__SHIFT
#define ss_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ss_SetInterruptMode() function.
     *  @{
     */
        #define ss_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ss_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ss_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ss_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ss__SIO)
    #define ss_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ss__PC) && (CY_PSOC4_4200L)
    #define ss_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ss_USBIO_DISABLE              ((uint32)(~ss_USBIO_ENABLE))
    #define ss_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ss_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ss_USBIO_ENTER_SLEEP          ((uint32)((1u << ss_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ss_USBIO_SUSPEND_DEL_SHIFT)))
    #define ss_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ss_USBIO_SUSPEND_SHIFT)))
    #define ss_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ss_USBIO_SUSPEND_DEL_SHIFT)))
    #define ss_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ss__PC)
    /* Port Configuration */
    #define ss_PC                 (* (reg32 *) ss__PC)
#endif
/* Pin State */
#define ss_PS                     (* (reg32 *) ss__PS)
/* Data Register */
#define ss_DR                     (* (reg32 *) ss__DR)
/* Input Buffer Disable Override */
#define ss_INP_DIS                (* (reg32 *) ss__PC2)

/* Interrupt configuration Registers */
#define ss_INTCFG                 (* (reg32 *) ss__INTCFG)
#define ss_INTSTAT                (* (reg32 *) ss__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ss_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ss__SIO)
    #define ss_SIO_REG            (* (reg32 *) ss__SIO)
#endif /* (ss__SIO_CFG) */

/* USBIO registers */
#if !defined(ss__PC) && (CY_PSOC4_4200L)
    #define ss_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ss_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ss_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ss_DRIVE_MODE_SHIFT       (0x00u)
#define ss_DRIVE_MODE_MASK        (0x07u << ss_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ss_H */


/* [] END OF FILE */
