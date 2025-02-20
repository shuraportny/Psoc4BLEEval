/*******************************************************************************
* File Name: FADE_Clock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_FADE_Clock_H)
#define CY_CLOCK_FADE_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void FADE_Clock_StartEx(uint32 alignClkDiv);
#define FADE_Clock_Start() \
    FADE_Clock_StartEx(FADE_Clock__PA_DIV_ID)

#else

void FADE_Clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void FADE_Clock_Stop(void);

void FADE_Clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 FADE_Clock_GetDividerRegister(void);
uint8  FADE_Clock_GetFractionalDividerRegister(void);

#define FADE_Clock_Enable()                         FADE_Clock_Start()
#define FADE_Clock_Disable()                        FADE_Clock_Stop()
#define FADE_Clock_SetDividerRegister(clkDivider, reset)  \
    FADE_Clock_SetFractionalDividerRegister((clkDivider), 0u)
#define FADE_Clock_SetDivider(clkDivider)           FADE_Clock_SetDividerRegister((clkDivider), 1u)
#define FADE_Clock_SetDividerValue(clkDivider)      FADE_Clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define FADE_Clock_DIV_ID     FADE_Clock__DIV_ID

#define FADE_Clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define FADE_Clock_CTRL_REG   (*(reg32 *)FADE_Clock__CTRL_REGISTER)
#define FADE_Clock_DIV_REG    (*(reg32 *)FADE_Clock__DIV_REGISTER)

#define FADE_Clock_CMD_DIV_SHIFT          (0u)
#define FADE_Clock_CMD_PA_DIV_SHIFT       (8u)
#define FADE_Clock_CMD_DISABLE_SHIFT      (30u)
#define FADE_Clock_CMD_ENABLE_SHIFT       (31u)

#define FADE_Clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << FADE_Clock_CMD_DISABLE_SHIFT))
#define FADE_Clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << FADE_Clock_CMD_ENABLE_SHIFT))

#define FADE_Clock_DIV_FRAC_MASK  (0x000000F8u)
#define FADE_Clock_DIV_FRAC_SHIFT (3u)
#define FADE_Clock_DIV_INT_MASK   (0xFFFFFF00u)
#define FADE_Clock_DIV_INT_SHIFT  (8u)

#else 

#define FADE_Clock_DIV_REG        (*(reg32 *)FADE_Clock__REGISTER)
#define FADE_Clock_ENABLE_REG     FADE_Clock_DIV_REG
#define FADE_Clock_DIV_FRAC_MASK  FADE_Clock__FRAC_MASK
#define FADE_Clock_DIV_FRAC_SHIFT (16u)
#define FADE_Clock_DIV_INT_MASK   FADE_Clock__DIVIDER_MASK
#define FADE_Clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_FADE_Clock_H) */

/* [] END OF FILE */
