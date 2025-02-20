/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <interrupts.h>
#include <stdio.h>
#include "modbus.h"
#include "runtime.h"
#include "sensor.h"

#include "i2c_master.h"

extern uint8_t mySlaveAddr;
extern uint8_t deepSleep;
extern uint8_t bleConnected;
uint8_t bleTimerExpired ;

uint8_t swPressed;
uint8_t swReleased;

extern uint32_t sTick;
extern uint8_t sendCommand;
extern uint8_t bytesIn;

uint8_t swLED =0;


extern uint8_t slaveBuf[I2CS_BUFF_SIZE];
extern uint8_t modbus_rxBuffer[MODBUS_RX_BUFFER_SIZE];


uint8_t rcvByte;

extern uint16 sleepPeriod;
extern uint8_t sleepEnable;
//void Stack_Handler(uint32 eventCode, void *eventParam){
//    
//    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReq;
//    
//    switch (eventCode){
//        case CYBLE_EVT_STACK_ON:
//            /* Enable the Skyworks SE2438T PA/LNA */
//            CSD_Write(1);
//            CPS_Write(1);
//            /* Configure the Link Layer to automatically switch PA control pin P3[2] and LNA control pin P3[3] */
//            CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLESS_RF_CONFIG), 0x0331);
//            CY_SET_XTND_REG32((void CYFAR *)(CYREG_SRSS_TST_DDFT_CTRL), 0x80000302);
//        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
//            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
//            break;
//            
//        case CYBLE_EVT_GATT_CONNECT_IND:
//            connectionHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;
//            bleConnected =1;
//            updateData();
//            break;
//        
//        case CYBLE_EVT_GATTS_WRITE_REQ:
//            wrReq = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
//
//            break;
//        default:
//            break;    
//    }
//    
//    
//    
//}

//void Ias_Handler(uint32 eventCode, void *eventParam){
//
//        CYBLE_IAS_CHAR_VALUE_T *param = (CYBLE_IAS_CHAR_VALUE_T * ) eventParam;
//        
//        if(*param->value->val == 0 )
//            PWM_WriteCompare(0);
//        else if (*param->value->val == 1) 
//            PWM_WriteCompare(500);
//        else     
//            PWM_WriteCompare(1000);
//}

//void Nextion_SendEndOfCommand(){
//    UART2_PutChar(0xFF);
//    UART2_PutChar(0xFF);
//    UART2_PutChar(0xFF);
//}
//
//void Nextion_SetPage(char* id){
//    char buf[50];
//    memset(buf, 0 , sizeof(buf));
//    uint32 len = sprintf(buf, "page %s",id) ;
//    UART2_PutString(buf);
//    Nextion_SendEndOfCommand();
//}
//
//void Nextion_SendFloat(char* obj, uint32 val,  uint8 res){
//    char buf[50];
//    memset(buf, 0 , sizeof(buf));
//    sprintf(buf, "%s.vvs1=%d",obj,res) ;
//    UART2_PutString(buf);
//    Nextion_SendEndOfCommand();
//    memset(buf, 0 , sizeof(buf));
//    sprintf(buf, "%s.val=%lu",obj,val) ;
//    UART2_PutString(buf);
//    Nextion_SendEndOfCommand();
//}
//
//void Nextion_SendInt(char* obj, uint32 val){
//    char buf[50];
//    memset(buf, 0 , sizeof(buf));
//    sprintf(buf, "%s.val=%lu",obj,val) ;
//    UART2_PutString(buf);
//    Nextion_SendEndOfCommand();
//}
//
//void Nextion_SetText(char* obj,char* txt){
//    char buf[50];
//    memset(buf, 0 , sizeof(buf));
//    sprintf(buf, "%s.txt=\"%s\"",obj,txt) ;
//    UART2_PutString(buf);
//    Nextion_SendEndOfCommand();
//
//}


uint8 newM;




int main(void)
{   
    
    /* Start system timer */
    CySysTickSetClockSource(CY_SYS_SYST_CSR_CLK_SRC_LFCLK);
    CySysTickStart();
    CySysTickSetCallback(0,SysTick_isr );
    
    /* Start SW interrupt handler*/
    isr_SW_Start();
    isr_SW_StartEx(SW_isr);
    
    /* Start I2C */
    I2C_Start();
   
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // BLE
    BLE_Start();
    TXEN_Write(0);

    
    isr_BLE_Start();
    isr_BLE_StartEx(BLE_isr);
    
    SysWdtInit();
    
    /*Read Sensor here*/
    LoadSensorInfo();
    CyDelay(100);
    InitSystem();
    
    /* Start UART */
    //ModbusUART_Start();
    //isr_ModbusByteIn_StartEx(ModbusByteIn_isr);
    
    // UART2_Start();
    
    MessageTimer_Start();
    isr_NewMessage_StartEx(NewMessage_isr);
    
    // TEST  AREA===========================
    //IDAC_1_Start();
    
    uint8 val, val2;
    uint8 dir;
    uint8 event, event2;
    uint8 resolution=0;
   
//    CyDelay(500);
//    Nextion_SetPage("page0");
//    Nextion_SetText("t1", "H2SSSS");
//    Nextion_SetText("t2", "PPM");
    
    CyDelay(500);
    // END TEST AREA========================

    
    
    extern uint16_t slavePersent;  
    LED_Write(1);
    for(;;)
    {   
        
        if(val>=200)dir=0;
        if(val<=0)dir=1;
        if(dir)
           val++;
        else
           val--;   
//        Nextion_SendFloat("page0.x0",val,resolution); 
//        Nextion_SendInt("page0.j0", (val*100)/200);
//            uint32 gauge;
//            if(val<10)
//                gauge=350+val;
//            else if(val>0)
//                gauge=val-10;
            //if(!event && !event2){
                
                //Nextion_SendInt("page6.z0",gauge);  
                //Nextion_SendInt("page6.n0",resolution);
                //Nextion_SendWaveToForm(val);
                
                //Nextion_SendFloat2("page6.x0",val,resolution);
                //Nextion_SendInt2("page6.z0",gauge);  
                //Nextion_SendInt2("page6.n0",resolution);
                
            //}
            
        
        
        //CySysWatchdogFeed(CY_SYS_WDT_COUNTER0_MASK);
        SysWdtReset();
        
        /*Poll Sensor here so far */
        if(startI2CRead && !modbusRequestReceived){
            
            startI2CRead =0;
            LoadSensorInfo(); // Get data from sensor
            //runtime_PollSensor();
            
            if(bleConnected)//bleConnected variable is controlled by Stack_Handler() in runtime.c
                updateOurBleData();
                
            
        }
        
        
        
        /*Check Mdobus request here*/
        if(modbusRequestReceived){
            modbusRequestReceived=0;
            runtime_ProcessRequest();// Response to Modbus
            //LoadSensorInfo(); // Get data from sensor
            bytesIn =0;
            LED_Write(1);
        }
        
        
#ifdef DEEPSLEEP
        if(bleTimerExpired && !bleConnected && sleepEnable){
            bleTimerExpired=0;
            SysWdtReset();
            CySysWdtDisable( CY_SYS_WDT_COUNTER0_MASK | CY_SYS_WDT_COUNTER1_MASK ); 
            //GoToSleep();
        }
#endif
        
        // Process Ble events
        CyBle_ProcessEvents();
        
    }
}



/* [] END OF FILE */
