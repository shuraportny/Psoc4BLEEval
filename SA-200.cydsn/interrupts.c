 /* ========================================
 *
 * Copyright Sam Walsh, 2014
 * All Rights Reserved.
 *
 * Interrupts.c Contains all the interrupts, put your own in here..
 *
 * ========================================
*/
#include <project.h>
#include <cydevice_trm.h>
#include <CyLib.h>
#include <interrupts.h>
#include <ModbusUART.h>
#include "modbus.h"
#include "runtime.h"


#define SW_PRESSED    0x00
#define SW_RELEASED   0x01


//#define BTN_NONE    0x03
//#define BTN_RIGHT   0x02
//#define BTN_LEFT    0x01

uint32_t msTick = 0;
uint32_t sTick = 0; 

extern uint8_t rcvByte;
extern uint8_t bytesIn;
extern uint8_t modbusRequestReceived;
extern uint8_t modbus_rxBuffer[MODBUS_RX_BUFFER_SIZE];

extern uint8_t swPressed;
extern uint8_t swReleased;

extern uint16_t i2cPeriod;
extern uint8_t startI2CRead;
extern uint8_t startI2CWrite;



volatile uint8_t deepSleep;
extern uint8_t mySlaveAddr,msa;
volatile uint8_t bleConnected;

extern uint8_t bleTimerExpired;

extern uint8_t updateEn;

extern uint8_t rs232RxBuffer[RS232_RX_BUFFER_SIZE];
extern uint8_t rs232RequestReceived;

//CY_ISR(RS232_isr){
//    static uint8_t byteCnt; 
//    
//    isr_RS232Rx_ClearPending();
//    rs232RxBuffer[byteCnt++] = RS232UART_GetChar(); 
//    if(byteCnt >=8){
//        byteCnt=0;
//        rs232RequestReceived=1;
//    }
//} 


CY_ISR(SysWdtIsrHandler)
{
	CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);                            /* Clear the counter interrupt */
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1_INT);                            /* Clear the counter interrupt */
    WdtIsr_ClearPending();                                                      /* Clear WDT interrupt */
}


extern uint8 newM;

CY_ISR(NewMessage_isr){

    newM=1;
    uint32 source = MessageTimer_GetInterruptSource();
    MessageTimer_ClearInterrupt(source);
    
}


CY_ISR(ModbusByteIn_isr) 
{  
    uint32 size;
    uint32 InterruptSource;
    
#ifdef DEEPSLEEP
    BLETimer_WriteCounter(0);
    BLETimer_Start();
#endif 
    

     if(newM){
        newM=0;
        bytesIn =0;
    }
    //size = ModbusUART_SpiUartGetRxBufferSize(); // this helps not to miss incoming bytes!
    //for(uint8 i = 0 ;i<size; i++){
        modbus_rxBuffer[bytesIn++] = ModbusUART_UartGetByte();
    //}
    
        
    //modbus_rxBuffer[bytesIn++] = ModbusUART_UartGetByte();
    MessageTimer_WriteCounter(0);
    MessageTimer_Start(); 
        
    if(deepSleep){
        SysWdtInit(); // This Init might be temporary
        deepSleep=0;
        bytesIn =0;
        modbusRequestReceived =1;
        CyDelay(500);// This delay affects on aligning recieved bytes. If to remove it , it will never recovering from deep sleep mode
    }else{
        
        
        
        // NEW
//        if(modbus_rxBuffer[0]!=mySlaveAddr){
//            bytesIn =0;        
//        }
//        if(bytesIn>2){
//            switch(modbus_rxBuffer[1]){
//                case 0x3:               
//                break;
//                case 0x6:
//                break;
//                default:
//                    bytesIn=0;
//                break;
//            }
//        }
        
        if(bytesIn>=MODBUS_COMMAND_SIZE){
            bytesIn =0;
            modbusRequestReceived =1;
        }
        

        }
    
    InterruptSource = ModbusUART_GetRxInterruptSourceMasked();    
    ModbusUART_ClearRxInterruptSource(InterruptSource);
}





CY_ISR(SW_isr)
{
    uint8 InterruptState = SW_ClearInterrupt();	
    uint8 value = SW_Read();
       
 
    deepSleep = 0;
    
#ifdef DEEPSLEEP    
    BLETimer_Start();
#endif    

    
}   


CY_ISR(BLE_isr)
{
    uint8 InterruptState = SW_ClearInterrupt();	
    uint8 value = SW_Read();
    
    
#ifdef DEEPSLEEP
    ResetBLETimer();
    
    
#endif
    
    bleTimerExpired =1;
    

    
}   





CY_ISR(SysTick_isr){
    static uint8_t pm;  
    

    // I2C Milliseconds Period
    //if(++msTick >= POLL_SENSOR_PERIOD_MS){
    if(++msTick >= i2cPeriod){    
        startI2CRead =1;
        msTick = 0;
    }
    
    
    
}

    

//CY_ISR(Timer_ISR_Handler){
//    
//    CYBLE_GATT_HANDLE_VALUE_PAIR_T locHandleValuePair;
//    uint8 bval;
//    
//    locHandleValuePair.attrHandle = cyBle_bass[0].batteryLevelHandle;
//    locHandleValuePair.value.len=1;
//    locHandleValuePair.value.val=&bval;
//    if(CYBLE_GATT_ERR_NONE == CyBle_GattsReadAttributeValue(&locHandleValuePair,NULL , CYBLE_GATT_DB_LOCALLY_INITIATED)){
//        if(--bval ==0)
//            bval =100;
//        CyBle_GattsWriteAttributeValue(&locHandleValuePair, 0 , NULL, CYBLE_GATT_DB_LOCALLY_INITIATED);
//    }
//    
//    Timer_ClearInterrupt(Timer_INTR_MASK_TC);
//    
//}    
    



/// **************************************
/// * Interrupt Service Routine:  SW_isr *
/// **************************************
///
/// \brief Increments the sTickMs 
///
/// \details This service routine increments thje sTickMs every microsecond, and 
/// increments the sTickSecond as well as reseting sTickMs every 1000 microseconds.
///
/// \return none.
///
/// \author Black Pearl Technology, Inc.
//





/* [] END OF FILE */
