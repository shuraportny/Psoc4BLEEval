/*******************************************************************************
* File Name: CPS.h  
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

#if !defined(CY_PINS_CPS_ALIASES_H) /* Pins CPS_ALIASES_H */
#define CY_PINS_CPS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CPS_0			(CPS__0__PC)
#define CPS_0_PS		(CPS__0__PS)
#define CPS_0_PC		(CPS__0__PC)
#define CPS_0_DR		(CPS__0__DR)
#define CPS_0_SHIFT	(CPS__0__SHIFT)
#define CPS_0_INTR	((uint16)((uint16)0x0003u << (CPS__0__SHIFT*2u)))

#define CPS_INTR_ALL	 ((uint16)(CPS_0_INTR))


#endif /* End Pins CPS_ALIASES_H */


/* [] END OF FILE */
