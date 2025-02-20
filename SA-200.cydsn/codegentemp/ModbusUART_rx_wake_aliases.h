/*******************************************************************************
* File Name: ModbusUART_rx_wake.h  
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

#if !defined(CY_PINS_ModbusUART_rx_wake_ALIASES_H) /* Pins ModbusUART_rx_wake_ALIASES_H */
#define CY_PINS_ModbusUART_rx_wake_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ModbusUART_rx_wake_0			(ModbusUART_rx_wake__0__PC)
#define ModbusUART_rx_wake_0_PS		(ModbusUART_rx_wake__0__PS)
#define ModbusUART_rx_wake_0_PC		(ModbusUART_rx_wake__0__PC)
#define ModbusUART_rx_wake_0_DR		(ModbusUART_rx_wake__0__DR)
#define ModbusUART_rx_wake_0_SHIFT	(ModbusUART_rx_wake__0__SHIFT)
#define ModbusUART_rx_wake_0_INTR	((uint16)((uint16)0x0003u << (ModbusUART_rx_wake__0__SHIFT*2u)))

#define ModbusUART_rx_wake_INTR_ALL	 ((uint16)(ModbusUART_rx_wake_0_INTR))


#endif /* End Pins ModbusUART_rx_wake_ALIASES_H */


/* [] END OF FILE */
