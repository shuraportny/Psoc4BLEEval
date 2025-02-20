/*******************************************************************************
* File Name: SWT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SWT_ALIASES_H) /* Pins SWT_ALIASES_H */
#define CY_PINS_SWT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWT_0			(SWT__0__PC)
#define SWT_0_PS		(SWT__0__PS)
#define SWT_0_PC		(SWT__0__PC)
#define SWT_0_DR		(SWT__0__DR)
#define SWT_0_SHIFT	(SWT__0__SHIFT)
#define SWT_0_INTR	((uint16)((uint16)0x0003u << (SWT__0__SHIFT*2u)))

#define SWT_INTR_ALL	 ((uint16)(SWT_0_INTR))


#endif /* End Pins SWT_ALIASES_H */


/* [] END OF FILE */
