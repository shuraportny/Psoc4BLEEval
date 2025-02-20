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




void Nextion_SendEndOfCommand(){
    UART2_PutChar(0xFF);
    UART2_PutChar(0xFF);
    UART2_PutChar(0xFF);
}

void Nextion_SetPage(char* id){
    char buf[50];
    memset(buf, 0 , sizeof(buf));
    uint32 len = sprintf(buf, "page %s",id) ;
    UART2_PutString(buf);
    Nextion_SendEndOfCommand();
}

void Nextion_SendFloat(char* obj, uint32 val,  uint8 res){
    char buf[50];
    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "%s.vvs1=%d",obj,res) ;
    UART2_PutString(buf);
    Nextion_SendEndOfCommand();
    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "%s.val=%lu",obj,val) ;
    UART2_PutString(buf);
    Nextion_SendEndOfCommand();
}

void Nextion_SendInt(char* obj, uint32 val){
    char buf[50];
    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "%s.val=%lu",obj,val) ;
    UART2_PutString(buf);
    Nextion_SendEndOfCommand();
}

void Nextion_SetText(char* obj,char* txt){
    char buf[50];
    memset(buf, 0 , sizeof(buf));
    sprintf(buf, "%s.txt=\"%s\"",obj,txt) ;
    UART2_PutString(buf);
    Nextion_SendEndOfCommand();

}


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
    ModbusUART_Start();
    isr_ModbusByteIn_StartEx(ModbusByteIn_isr);
    
     UART2_Start();
    
    MessageTimer_Start();
    isr_NewMessage_StartEx(NewMessage_isr);
    
    // TEST  AREA===========================
    //IDAC_1_Start();
    
    uint8 val, val2;
    uint8 dir;
    uint8 event, event2;
    uint8 resolution=0;
   
    CyDelay(500);
    Nextion_SetPage("page0");
    Nextion_SetText("t1", "H2SSSS");
    Nextion_SetText("t2", "PPM");
    
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
        Nextion_SendFloat("page0.x0",val,resolution); 
        Nextion_SendInt("page0.j0", (val*100)/200);
        uint32 gauge;
        if(val<10)
            gauge=350+val;
        else if(val>0)
            gauge=val-10;
        
        Nextion_SendInt("page6.z0",gauge);  
        Nextion_SendInt("page6.n0",resolution);
        
                
                
                        
        
        
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
