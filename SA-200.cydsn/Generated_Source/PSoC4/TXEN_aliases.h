/*******************************************************************************
* File Name: TXEN.h  
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

#if !defined(CY_PINS_TXEN_ALIASES_H) /* Pins TXEN_ALIASES_H */
#define CY_PINS_TXEN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TXEN_0			(TXEN__0__PC)
#define TXEN_0_PS		(TXEN__0__PS)
#define TXEN_0_PC		(TXEN__0__PC)
#define TXEN_0_DR		(TXEN__0__DR)
#define TXEN_0_SHIFT	(TXEN__0__SHIFT)
#define TXEN_0_INTR	((uint16)((uint16)0x0003u << (TXEN__0__SHIFT*2u)))

#define TXEN_INTR_ALL	 ((uint16)(TXEN_0_INTR))


#endif /* End Pins TXEN_ALIASES_H */


/* [] END OF FILE */
