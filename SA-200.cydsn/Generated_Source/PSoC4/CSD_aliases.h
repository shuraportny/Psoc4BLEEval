/*******************************************************************************
* File Name: CSD.h  
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

#if !defined(CY_PINS_CSD_ALIASES_H) /* Pins CSD_ALIASES_H */
#define CY_PINS_CSD_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CSD_0			(CSD__0__PC)
#define CSD_0_PS		(CSD__0__PS)
#define CSD_0_PC		(CSD__0__PC)
#define CSD_0_DR		(CSD__0__DR)
#define CSD_0_SHIFT	(CSD__0__SHIFT)
#define CSD_0_INTR	((uint16)((uint16)0x0003u << (CSD__0__SHIFT*2u)))

#define CSD_INTR_ALL	 ((uint16)(CSD_0_INTR))


#endif /* End Pins CSD_ALIASES_H */


/* [] END OF FILE */
