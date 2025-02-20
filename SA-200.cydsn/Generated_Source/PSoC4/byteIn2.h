/*******************************************************************************
* File Name: byteIn2.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_byteIn2_H)
#define CY_ISR_byteIn2_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void byteIn2_Start(void);
void byteIn2_StartEx(cyisraddress address);
void byteIn2_Stop(void);

CY_ISR_PROTO(byteIn2_Interrupt);

void byteIn2_SetVector(cyisraddress address);
cyisraddress byteIn2_GetVector(void);

void byteIn2_SetPriority(uint8 priority);
uint8 byteIn2_GetPriority(void);

void byteIn2_Enable(void);
uint8 byteIn2_GetState(void);
void byteIn2_Disable(void);

void byteIn2_SetPending(void);
void byteIn2_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the byteIn2 ISR. */
#define byteIn2_INTC_VECTOR            ((reg32 *) byteIn2__INTC_VECT)

/* Address of the byteIn2 ISR priority. */
#define byteIn2_INTC_PRIOR             ((reg32 *) byteIn2__INTC_PRIOR_REG)

/* Priority of the byteIn2 interrupt. */
#define byteIn2_INTC_PRIOR_NUMBER      byteIn2__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable byteIn2 interrupt. */
#define byteIn2_INTC_SET_EN            ((reg32 *) byteIn2__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the byteIn2 interrupt. */
#define byteIn2_INTC_CLR_EN            ((reg32 *) byteIn2__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the byteIn2 interrupt state to pending. */
#define byteIn2_INTC_SET_PD            ((reg32 *) byteIn2__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the byteIn2 interrupt. */
#define byteIn2_INTC_CLR_PD            ((reg32 *) byteIn2__INTC_CLR_PD_REG)



#endif /* CY_ISR_byteIn2_H */


/* [] END OF FILE */
