/*******************************************************************************
* File Name: DACout.h  
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

#if !defined(CY_PINS_DACout_ALIASES_H) /* Pins DACout_ALIASES_H */
#define CY_PINS_DACout_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DACout_0			(DACout__0__PC)
#define DACout_0_PS		(DACout__0__PS)
#define DACout_0_PC		(DACout__0__PC)
#define DACout_0_DR		(DACout__0__DR)
#define DACout_0_SHIFT	(DACout__0__SHIFT)
#define DACout_0_INTR	((uint16)((uint16)0x0003u << (DACout__0__SHIFT*2u)))

#define DACout_INTR_ALL	 ((uint16)(DACout_0_INTR))


#endif /* End Pins DACout_ALIASES_H */


/* [] END OF FILE */
