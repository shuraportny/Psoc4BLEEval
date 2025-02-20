/*******************************************************************************
* File Name: wakeUp.h  
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

#if !defined(CY_PINS_wakeUp_ALIASES_H) /* Pins wakeUp_ALIASES_H */
#define CY_PINS_wakeUp_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define wakeUp_0			(wakeUp__0__PC)
#define wakeUp_0_PS		(wakeUp__0__PS)
#define wakeUp_0_PC		(wakeUp__0__PC)
#define wakeUp_0_DR		(wakeUp__0__DR)
#define wakeUp_0_SHIFT	(wakeUp__0__SHIFT)
#define wakeUp_0_INTR	((uint16)((uint16)0x0003u << (wakeUp__0__SHIFT*2u)))

#define wakeUp_INTR_ALL	 ((uint16)(wakeUp_0_INTR))


#endif /* End Pins wakeUp_ALIASES_H */


/* [] END OF FILE */
