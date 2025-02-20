/*******************************************************************************
* File Name: CPS.h  
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

#if !defined(CY_PINS_CPS_H) /* Pins CPS_H */
#define CY_PINS_CPS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CPS_aliases.h"


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
} CPS_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CPS_Read(void);
void    CPS_Write(uint8 value);
uint8   CPS_ReadDataReg(void);
#if defined(CPS__PC) || (CY_PSOC4_4200L) 
    void    CPS_SetDriveMode(uint8 mode);
#endif
void    CPS_SetInterruptMode(uint16 position, uint16 mode);
uint8   CPS_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CPS_Sleep(void); 
void CPS_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CPS__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CPS_DRIVE_MODE_BITS        (3)
    #define CPS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CPS_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CPS_SetDriveMode() function.
         *  @{
         */
        #define CPS_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CPS_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CPS_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CPS_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CPS_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CPS_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CPS_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CPS_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CPS_MASK               CPS__MASK
#define CPS_SHIFT              CPS__SHIFT
#define CPS_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CPS_SetInterruptMode() function.
     *  @{
     */
        #define CPS_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CPS_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CPS_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CPS_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CPS__SIO)
    #define CPS_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CPS__PC) && (CY_PSOC4_4200L)
    #define CPS_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CPS_USBIO_DISABLE              ((uint32)(~CPS_USBIO_ENABLE))
    #define CPS_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CPS_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CPS_USBIO_ENTER_SLEEP          ((uint32)((1u << CPS_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CPS_USBIO_SUSPEND_DEL_SHIFT)))
    #define CPS_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CPS_USBIO_SUSPEND_SHIFT)))
    #define CPS_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CPS_USBIO_SUSPEND_DEL_SHIFT)))
    #define CPS_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CPS__PC)
    /* Port Configuration */
    #define CPS_PC                 (* (reg32 *) CPS__PC)
#endif
/* Pin State */
#define CPS_PS                     (* (reg32 *) CPS__PS)
/* Data Register */
#define CPS_DR                     (* (reg32 *) CPS__DR)
/* Input Buffer Disable Override */
#define CPS_INP_DIS                (* (reg32 *) CPS__PC2)

/* Interrupt configuration Registers */
#define CPS_INTCFG                 (* (reg32 *) CPS__INTCFG)
#define CPS_INTSTAT                (* (reg32 *) CPS__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CPS_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CPS__SIO)
    #define CPS_SIO_REG            (* (reg32 *) CPS__SIO)
#endif /* (CPS__SIO_CFG) */

/* USBIO registers */
#if !defined(CPS__PC) && (CY_PSOC4_4200L)
    #define CPS_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CPS_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CPS_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CPS_DRIVE_MODE_SHIFT       (0x00u)
#define CPS_DRIVE_MODE_MASK        (0x07u << CPS_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CPS_H */


/* [] END OF FILE */
