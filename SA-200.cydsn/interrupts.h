/* ========================================
 *
 * Copyright Sam Walsh, 2014
 * All Rights Reserved.
 *
 * interrupts.h Contains all the interrupts variables
 *
 * ========================================
*/
#include <cytypes.h>
#include <cyfitter.h>



uint8_t startI2CRead;

void wdtInterruptCallback();

//CY_ISR_PROTO(SysWdtIsrHandler);

CY_ISR_PROTO(ModbusByteIn_isr);
CY_ISR_PROTO(RS232_isr);


CY_ISR_PROTO(Btn_isr); // Button Press/Release ISR
//CY_ISR_PROTO(endOfMessage_isr);

// ************************
// * Interrupt Prototypes *
// ************************

CY_ISR_PROTO(SW_isr); // Switch Press / Release ISR

CY_ISR_PROTO(BLE_isr);
CY_ISR_PROTO(I2C_isr);

CY_ISR_PROTO(SysTick_isr); // SysTick Ms/Second counter ISR

CY_ISR_PROTO(SysTickLED_ISR); // SysTickLED Ms counter ISR

CY_ISR_PROTO(Timer_ISR_Handler);
CY_ISR_PROTO(NewMessage_isr);
/* [] END OF FILE */
