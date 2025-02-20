/*******************************************************************************
* File Name: PG_3V3.h  
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

#if !defined(CY_PINS_PG_3V3_ALIASES_H) /* Pins PG_3V3_ALIASES_H */
#define CY_PINS_PG_3V3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PG_3V3_0			(PG_3V3__0__PC)
#define PG_3V3_0_PS		(PG_3V3__0__PS)
#define PG_3V3_0_PC		(PG_3V3__0__PC)
#define PG_3V3_0_DR		(PG_3V3__0__DR)
#define PG_3V3_0_SHIFT	(PG_3V3__0__SHIFT)
#define PG_3V3_0_INTR	((uint16)((uint16)0x0003u << (PG_3V3__0__SHIFT*2u)))

#define PG_3V3_INTR_ALL	 ((uint16)(PG_3V3_0_INTR))


#endif /* End Pins PG_3V3_ALIASES_H */


/* [] END OF FILE */
