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

#include "runtime.h"
#include "modbus.h"
#include "sensor.h"
#include "i2c_master.h"

//extern S_Sensor s;
char firmwareVersion[10];

uint8_t sensor[DATA_LENGTH];
extern uint8_t modbus_rxBuffer[MODBUS_RX_BUFFER_SIZE];
extern uint8_t modbus_txBuffer[MODBUS_TX_BUFFER_SIZE];

uint8_t rs232RxBuffer[RS232_RX_BUFFER_SIZE];
//uint8_t rs232TxBuffer[MODBUS_TX_BUFFER_SIZE];
uint8_t rs232RequestReceived=0;

uint8_t mySlaveAddr,msa;
uint16_t i2cPeriod;
uint16_t sleepPeriod;

uint8_t bytesIn;;

uint8_t startI2CRead;
uint8_t startI2CWrite;

uint8_t sendCommand=0;
uint8_t deepSleep;
uint8_t sleepEnable;

uint8_t BleControl;

uint16_t slavePersent; 
uint16_t sleepCnt; 

uint8  arr[DATA_LENGTH]; // input I2C buffer
S_I2C  txarr; // output I2C data structure      

void Test_Increment(uint8 reg , uint8 bytes_to_send){
    txarr.reg=reg;
    for(uint8 i =0 ;i<bytes_to_send;i++ ){
         txarr.data[i]+=1;
    }
    CyDelay(1000);
    slave_WriteDataRaw(0, bytes_to_send, &txarr.reg);
}



void InitSystem(){
    
    
    mySlaveAddr = EEPROM_GetMyAddress();
    msa = mySlaveAddr;
    i2cPeriod = EEPROM_GetI2CPeriod();
    
    
    #ifdef DEEPSLEEP
    sleepPeriod = EEPROM_GetSleepPeriod();    
    sleepEnable = (sleepPeriod>= MINIMAL_SLEEP_PERIOD)? 1:0;
    BLETimer_Start();
    BLETimer_Stop();
    SetSleepPeriod(sleepPeriod);
    BLETimer_Start();
    #endif
    
    sensor[DEVTYPEMSB] = 0;
    sensor[DEVTYPELSB] = 21;
    
    strncpy(firmwareVersion, FIRMWARE_VISION, 10);
    
    char SysSerialNumber[] = "11111111"; 
    uint32 SensorSerialNumber = 0x123456; 
    
    char str[12];
    memset(str , 0 , sizeof(str));
    remove_trailing_spaces(str, (char*) &sensor[COMPAUND1]);
    
    char BleName[30];
    memset(BleName, 0 , sizeof(BleName));
    strcpy( BleName, "SA-200-" );
    strncat(BleName, str,strlen(str) );
    strcat(BleName, " ");
    strncat(BleName, (char*)&sensor[SERIALNUMBER1],6 );
    
    CyBle_GapSetLocalName( BleName );
    //CyBle_DissSetCharacteristicValue(CYBLE_DIS_SYSTEM_ID, 8, (uint8 *)SysSerialNumber);
    memset(str , 0 , sizeof(str));
    strncpy(&str[2], (char*)&sensor[SERIALNUMBER1],6);
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_SYSTEM_ID, 8, (uint8 *)&str);
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_FIRMWARE_REV, 10, (uint8 *)FIRMWARE_VISION);
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_SOFTWARE_REV, 10, (uint8 *)FIRMWARE_VISION);
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_SERIAL_NUMBER, 12, (uint8 *)&sensor[SERIALNUMBER1]);
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_HARDWARE_REV, 4, (uint8 *)HARDWARE_VISION);
    
    
    
}

uint8_t EEPROM_GetMyAddress(void){
    uint8_t myaddr;
    myaddr =  i2c_Read_8(EEPROM_I2C_ADDRESS,EEPROM_MY_ADDRESS_REG );
    CyDelay(50);
    if(myaddr==0xFF)
        myaddr = MODBUS_MY_DEFAULT_ADDRESS;
    return myaddr;
}

void EEPROM_SetMyAddress(uint8_t addr){
    i2c_write_8(EEPROM_I2C_ADDRESS,EEPROM_MY_ADDRESS_REG,addr);
    CyDelay(100);
}

uint16_t EEPROM_GetI2CPeriod(void){
    uint16_t i2c_period;
    i2c_period =  (i2c_Read_8(EEPROM_I2C_ADDRESS,EEPROM_I2C_PERIOD_MSB_REG ))<<8;
    CyDelay(50);
    i2c_period +=  i2c_Read_8(EEPROM_I2C_ADDRESS,EEPROM_I2C_PERIOD_LSB_REG );
    CyDelay(50);
    if((i2c_period==0xFFFF)||((i2c_period<MINIMAL_DEFAULT_I2C_PERIOD)))
        i2c_period = MINIMAL_DEFAULT_I2C_PERIOD;
    return i2c_period;
}

void EEPROM_SetI2CPeriod(uint16_t period){
    i2c_write_8(EEPROM_I2C_ADDRESS,EEPROM_I2C_PERIOD_MSB_REG,(period>>8)&0xFF);
    CyDelay(100);
    i2c_write_8(EEPROM_I2C_ADDRESS,EEPROM_I2C_PERIOD_LSB_REG, period & 0xFF );
    CyDelay(100);
}


uint16_t EEPROM_GetSleepPeriod(void){
    uint16_t sleep_period;
    sleep_period =  (i2c_Read_8(EEPROM_I2C_ADDRESS,EEPROM_SLEEP_PERIOD_MSB_REG ))<<8;
    CyDelay(50);
    sleep_period +=  i2c_Read_8(EEPROM_I2C_ADDRESS,EEPROM_SLEEP_PERIOD_LSB_REG );
    CyDelay(50);
    if(sleep_period==0xFFFF)
        sleep_period = DEFAULT_SLEEP_PERIOD;
    return sleep_period;
}

void EEPROM_SetSleepPeriod(uint16_t period){
    i2c_write_8(EEPROM_I2C_ADDRESS,EEPROM_SLEEP_PERIOD_MSB_REG,(period>>8)&0xFF);
    CyDelay(100);
    i2c_write_8(EEPROM_I2C_ADDRESS,EEPROM_SLEEP_PERIOD_LSB_REG, period & 0xFF );
    CyDelay(100);
    
}

int32_t LoadSensorInfo(void){
    uint32_t status;
    status = i2c_status(I2C_SLAVE_ADDR);
    //memset(sensor, 0 , sizeof(sensor));    
    if(status !=I2C_I2C_MSTR_NO_ERROR)
        sensor[STATUSLSB]=POLL_SENSOR_STATUS_ABSENT; 
    else{
        sensor[STATUSLSB]=POLL_SENSOR_STATUS_OK;
        // Here we get all sensor data
        slave_ReadDataRaw(0, (DATA_LENGTH) ,&sensor[SYSREADING1] );
    }
    
    
      
    
    return status;
}


void runtime_PollSensor(void){
    
    //uint8 data = i2c_Read_8( I2C_SLAVE_ADDR,  I2C_SYS_READING_OFFSET );
    slave_ReadDataRaw(0, 20 ,&sensor[SYSREADING1] );
    return;    
}

void runtime_CtrlSensor(uint8_t reg, uint16 data){
    //slave_WriteDataRaw(I2C_SLAVE_ADDR, reg , data);
    i2c_write_16(I2C_SLAVE_ADDR ,reg ,  data);
    return;
}


void runtime_ProcessRequest(void){
    uint16_t regsToSend;
    uint16_t  startRegister;
    uint8_t  modbusCommand;
    uint16_t data;
    
    // Is this my packet?
    if( (mySlaveAddr != modbus_rxBuffer[0]) && (modbus_rxBuffer[0]!= MODBUS_BROADCAST_ADDRESS) ) {   // mySlaveAddr is initialized in initSensor() now
        return;
    }    
    
    uint16 crc;
    uint16 recvdcrc = (modbus_rxBuffer[6]<<8)+modbus_rxBuffer[7];
    crc = (uint16) modbus_GenerateCRC(modbus_rxBuffer,8);
    if(crc!=recvdcrc) return;
    
    
    modbusCommand = modbus_rxBuffer[1];
    
    // Broadcast request for My Slave Address
    if(modbus_rxBuffer[0]==MODBUS_BROADCAST_ADDRESS){
        if ( MODBUS_READ_CMD == modbusCommand){
            startRegister = modbus_rxBuffer[3];
            regsToSend = modbus_rxBuffer[5];
            modbus_txBuffer[3] = 0;
            modbus_txBuffer[4] = mySlaveAddr;
            modbusSendBulk(MODBUS_BROADCAST_ADDRESS , modbusCommand , regsToSend);     
        }
        return;
    }
    
    
    
    
    if ( MODBUS_READ_CMD == modbusCommand){
        // Send Read Response to Modbus Master
        startRegister = modbus_rxBuffer[3];
        regsToSend = modbus_rxBuffer[5];
        uint8_t idx=3;
        uint8_t byteCount = regsToSend;
        if(startRegister>=MODBUS_ADDRESS_REG){
            switch(startRegister){
                case MODBUS_ADDRESS_REG:
                    modbus_txBuffer[idx++] = 0 ;
                    modbus_txBuffer[idx++] = mySlaveAddr ;
                    if((--byteCount)==0) break;
                    
                case MODBUS_I2C_PERIOD_REG:
                    modbus_txBuffer[idx++] = (i2cPeriod>>8)&0xFF;
                    modbus_txBuffer[idx++] = i2cPeriod&0xFF;
                    if((--byteCount)==0) break;
                case MODBUS_SLEEP_PERIOD_REG:
                    modbus_txBuffer[idx++] = (sleepPeriod>>8)&0xFF;
                    modbus_txBuffer[idx++] = sleepPeriod&0xFF;
                    if((--byteCount)==0) break;
                case MODBUS_DEBUG_REG:    
                    modbus_txBuffer[idx++] = (slavePersent>>8)&0xFF;
                    modbus_txBuffer[idx++] = slavePersent&0xFF;
                    if((--byteCount)==0)break;
                    
                case MODBUS_FM_VERSION_REG:    
                    modbus_txBuffer[idx++] = firmwareVersion[0];
                    modbus_txBuffer[idx++] = firmwareVersion[1];
                    if((--byteCount)==0)break;
                case MODBUS_FM_VERSION_REG+1:    
                    modbus_txBuffer[idx++] = firmwareVersion[2];
                    modbus_txBuffer[idx++] = firmwareVersion[3];
                    if((--byteCount)==0)break; 
                case MODBUS_FM_VERSION_REG+2:    
                    modbus_txBuffer[idx++] = firmwareVersion[4];
                    modbus_txBuffer[idx++] = firmwareVersion[5];
                    if((--byteCount)==0)break;
                case MODBUS_FM_VERSION_REG+3:    
                    modbus_txBuffer[idx++] = firmwareVersion[6];
                    modbus_txBuffer[idx++] = firmwareVersion[7];
                    if((--byteCount)==0)break;  
                case MODBUS_FM_VERSION_REG+4:    
                    modbus_txBuffer[idx++] = firmwareVersion[8];
                    modbus_txBuffer[idx++] = firmwareVersion[9];
                    break;    
                    
                    
            }
            modbusSendBulk(mySlaveAddr , modbusCommand , regsToSend); 
        }
        else{
            for(uint16 i=0;i<regsToSend*2;i++){
                modbus_txBuffer[3+i] = sensor[startRegister*2+2+i];
            }
            //memcpy(&modbus_txBuffer[3], &sensor[startRegister*2+2], regsToSend*2);
            modbusSendBulk(mySlaveAddr , modbusCommand , regsToSend); 
            //Test_Increment(startRegister , regsToSend);
        } 
    }
    
    
    
    
    
    if ( MODBUS_WRITE_CMD == modbusCommand){
        // send Write response
        startRegister = modbus_rxBuffer[2];  // register address high byte 
        startRegister = (startRegister<<8) +modbus_rxBuffer[3]; // register address low byte
        data = modbus_rxBuffer[4];   // high byte to write
        data = (data << 8)+ modbus_rxBuffer[5]; // low byte to write
        
        if(startRegister ==MODBUS_ADDRESS_REG){
            // Setting My Modbus address
            mySlaveAddr = data;
            EEPROM_SetMyAddress(data);
        }else if (startRegister ==MODBUS_I2C_PERIOD_REG){
            // Setting I2C Period
            if(data<MINIMAL_DEFAULT_I2C_PERIOD)
                data = MINIMAL_DEFAULT_I2C_PERIOD;
            i2cPeriod = data;
            EEPROM_SetI2CPeriod(data);
        }
        else if (startRegister ==MODBUS_SLEEP_PERIOD_REG){
            // Setting I2C Period
            if(data<MINIMAL_SLEEP_PERIOD)
                data = 0;
            sleepPeriod = data;
            sleepEnable = (sleepPeriod>= MINIMAL_SLEEP_PERIOD)? 1:0;
            EEPROM_SetSleepPeriod(data);
            SetSleepPeriod(data);
        }
        else if(startRegister>2){
            //Send Command to Sensor
            runtime_CtrlSensor( (startRegister-1)*2 , data);
        }
        // Send Response to Modbus Master
        modbusWriteResponse(mySlaveAddr, modbusCommand , startRegister, data);
    }
    return;    
}


//void runtime_RS232ProcessRequest(void){
//    uint16_t regsToSend;
//    uint8_t  startRegister;
//    uint8_t  modbusCommand;
//    uint16_t data;
//    
//    // Is this my packet?
//    if( (mySlaveAddr != rs232RxBuffer[0]) && (rs232RxBuffer[0]!= MODBUS_BROADCAST_ADDRESS) ) {   // mySlaveAddr is initialized in initSensor() now
//        memset(&modbus_txBuffer[0] , 0 , sizeof(modbus_txBuffer));
//        memcpy(&modbus_txBuffer[0] , rs232RxBuffer , 10);
//        return;
//    }    
//    
//    modbusCommand = rs232RxBuffer[1];
//    
//    // Broadcast request for My Slave Address
//    if(rs232RxBuffer[0]==MODBUS_BROADCAST_ADDRESS){
//        if ( MODBUS_READ_CMD == modbusCommand){
//            startRegister = rs232RxBuffer[3];
//            regsToSend = rs232RxBuffer[5];
//            modbus_txBuffer[3] = 0;
//            modbus_txBuffer[4] = mySlaveAddr;
//            rs232SendBulk(MODBUS_BROADCAST_ADDRESS , modbusCommand , regsToSend);     
//        }
//        return;
//    }
//    
//    
//    if ( MODBUS_READ_CMD == modbusCommand){
//        // Send Read Response to Modbus Master
//        startRegister = rs232RxBuffer[3];
//        regsToSend = rs232RxBuffer[5];
//        uint8_t idx=3;
//        uint8_t byteCount = regsToSend;
//        if(startRegister>=MODBUS_ADDRESS_REG){
//            switch(startRegister){
//                case MODBUS_ADDRESS_REG:
//                    modbus_txBuffer[idx++] = 0 ;
//                    modbus_txBuffer[idx++] = mySlaveAddr ;
//                    if((--byteCount)==0) break;
//                    
//                case MODBUS_I2C_PERIOD_REG:
//                    modbus_txBuffer[idx++] = (i2cPeriod>>8)&0xFF;
//                    modbus_txBuffer[idx++] = i2cPeriod&0xFF;
//                    if((--byteCount)==0) break;
//                case MODBUS_SLEEP_PERIOD_REG:
//                    modbus_txBuffer[idx++] = (sleepPeriod>>8)&0xFF;
//                    modbus_txBuffer[idx++] = sleepPeriod&0xFF;
//                    break;  
//            }
//            rs232SendBulk(mySlaveAddr , modbusCommand , regsToSend); 
//        }
//        else{
//            memcpy(&modbus_txBuffer[3], &sensor[startRegister*2+2], regsToSend*2);
//            rs232SendBulk(mySlaveAddr , modbusCommand , regsToSend); 
//            //Test_Increment(startRegister , regsToSend);
//        } 
//    }
//    
//    if ( MODBUS_WRITE_CMD == modbusCommand){
//        // send Write response
//        startRegister = rs232RxBuffer[2];  // register address high byte 
//        startRegister = (startRegister<<8) +rs232RxBuffer[3]; // register address low byte
//        data = rs232RxBuffer[4];   // high byte to write
//        data = (data << 8)+ rs232RxBuffer[5]; // low byte to write
//        
//        if(startRegister ==MODBUS_ADDRESS_REG){
//            // Setting My Modbus address
//            mySlaveAddr = data;
//            EEPROM_SetMyAddress(data);
//        }else if (startRegister ==MODBUS_I2C_PERIOD_REG){
//            // Setting I2C Period
//            i2cPeriod = data;
//            EEPROM_SetI2CPeriod(data);
//        }
//        else if (startRegister ==MODBUS_SLEEP_PERIOD_REG){
//            // Setting I2C Period
//            sleepPeriod = data;
//            EEPROM_SetSleepPeriod(data);
//            SetSleepPeriod(data);
//        }
//        else if(startRegister>2){
//            //Send Command to Sensor
//            runtime_CtrlSensor( (startRegister-1)*2 , data);
//        }
//        // Send Response to Modbus Master
//        rs232WriteResponse(mySlaveAddr, modbusCommand , startRegister, data);
//    }
//    return;    
//}



void GoToSleep(){
    bytesIn=0;
    deepSleep=1;
    LED_Write(0);
    ModbusUART_Sleep();
    
    
    
    
    CySysPmDeepSleep();
    ModbusUART_Wakeup();
    
    //RS232UART_RestoreConfig() ;
    //RS232UART_Wakeup();
    
}

void LEDShow(void){
    LED_Write(deepSleep);
}


//uint8 BleNotifyReading;

void BLE_Start(){
    CyBle_Start(Stack_Handler);
}


void updateData(void){
    uint8_t sys[4];
    
    
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    if( CyBle_GetState() != CYBLE_STATE_CONNECTED ) return;
    
    /* Update sys gas reading value */
    sys[0] =  sensor[SYSREADING1];
    sys[1] =  sensor[SYSREADING2];
    sys[2] =  sensor[SYSREADING3];
    sys[3] =  sensor[SYSREADING4];
    
    
    
    
    /* Update sys remote control value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_REMOTE_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.BleControl;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for remote control value */
    if( System.BleNotifyControl && ( System.BleControl != System.BleControlPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.BleControlPrevious = System.BleControl;
    }
    
    
    
    tempHandle.attrHandle = CYBLE_SGA1_SYS_READING_CHAR_HANDLE;
    tempHandle.value.val= (uint8* )&sys;
    tempHandle.value.len = 4;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    if(System.BleNotifyReading){
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        Sensor.ReadingPrevious = Sensor.Reading;
    }
    
    /* Update SENSOR_STATUS value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_STATUS_CHAR_HANDLE;
    tempHandle.value.val=(uint8*)&sensor[CALSTATUSMSB];
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    if(System.BleNotifyReading){
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        Sensor.StatusPrevious = Sensor.Status;
    }
    
    
    /* Update SENSOR_NOTE value */
    tempHandle.attrHandle = CYBLE_SGA2_SENSOR_GAS_NOTE_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&sensor[COMPAUND1];
    tempHandle.value.len = 10;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    
    /* Update SENSOR_PIN value */
    tempHandle.attrHandle = CYBLE_SGA2_PIN_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&sensor[UNIT1];
    tempHandle.value.len = 4;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    // Indication of SYS REMOTE control
//    switch(BleControl){
//    case 10: LED_Write(0); LED3_Write(0); break;
//    case 20: LED_Write(0); LED3_Write(1); break;
//    default: LED_Write(1); LED3_Write(1); break;    
//    }
    
}



void updateOurBleData()
{
    uint8 testVal8 = 0;
    uint16 testVal16 = 0;
    uint32 testVal32 = 0;
    
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle;
    
    /* Update sys gas reading value */
    uint8_t sys[4];
    sys[0] =  sensor[SYSREADING1];
    sys[1] =  sensor[SYSREADING2];
    sys[2] =  sensor[SYSREADING3];
    sys[3] =  sensor[SYSREADING4];
    
    
    if( CyBle_GetState() != CYBLE_STATE_CONNECTED ) return;

    /* Update sys remote control value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_REMOTE_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&sensor[SYSREMOTEMSB];//&System.BleControl;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for remote control value */
    if( System.BleNotifyControl && ( System.BleControl != System.BleControlPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.BleControlPrevious = System.BleControl;
    }

    /* Update sys gas reading value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_READING_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&sys;//&testVal8;
    tempHandle.value.len = 4;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for Sensor Reading */
    if( System.BleNotifyReading)// && ( Sensor.Reading != Sensor.ReadingPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        Sensor.ReadingPrevious = Sensor.Reading;
    }

    /* Update sys remote status value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_STATUS_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&sensor[STATUSMSB];//&System.Status;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for Sensor Status */
    if( System.BleNotifyStatus)// && ( System.Status != System.StatusPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.StatusPrevious = System.Status;
    }

    /* Update CAN Channel value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_CAN_CHAN_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CanChannel;//&Sensor.CountsHalfScale;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update CAN Node ID value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_CAN_ID_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&mySlaveAddr;//&System.CanNodeId;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update SYS_CAL_LOOP value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_CAL_LOOP_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.BleCalLoop;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update SYS_ADC value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_ADC_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.AdcCounts;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for AdcCounts */
    if( System.BleNotifyAdcCounts && ( System.AdcCounts != System.AdcCountsPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.AdcCountsPrevious = System.AdcCounts;
    }

    /* Update SYS_ALERT_1 value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_ALERT_1_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&testVal8;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update SYS_ALERT_2 value */
    tempHandle.attrHandle = CYBLE_SGA1_SYS_ALERT_2_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&testVal8;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update PIN value */
    tempHandle.attrHandle = CYBLE_SGA2_PIN_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.Pin;
    tempHandle.value.len = 4;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update SENSOR_TYPE value ( This is actually mfg ) */
    tempHandle.attrHandle = CYBLE_SGA2_SENSOR_TYPE_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&testVal8;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update gas range value */
    uint8_t rangeLE[2];
    rangeLE[0] = sensor[FULLSCALERANGE4];
    rangeLE[1] = sensor[FULLSCALERANGE3];
    tempHandle.attrHandle = CYBLE_SGA2_SENSOR_RANGE_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&rangeLE[0]; //&sensor[FULLSCALERANGE3];//&testVal8;  
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update SENSOR_NOTE value */
    tempHandle.attrHandle = CYBLE_SGA2_SENSOR_GAS_NOTE_CHAR_HANDLE;
    char str[12];
    remove_trailing_spaces(str, (char*)&sensor[COMPAUND1]);
    strcat(str, " ");
    strncat(str ,(char*)&sensor[UNIT1], 4 );
    tempHandle.value.val = (uint8*)str;
    tempHandle.value.len = 10;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update SENSOR_TAG value */
    tempHandle.attrHandle = CYBLE_SGA2_SENSOR_TAG_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.SensorTag;
    tempHandle.value.len = SENSOR_TAG_LENGTH;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update temperature */
    tempHandle.attrHandle = CYBLE_SGA2_SENSOR_TEMPERATURE_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&sensor[TEMPERATURELSB];//&testVal8;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for Sensor CalLevel */
//    if( System.BleNotifyTemperature && ( Sensor.Temperature != Sensor.TemperaturePrevious ) )
//    {
//        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
//        Sensor.TemperaturePrevious = Sensor.Temperature;
//    }

    /* Update SENSOR_CAL_LEVEL value */
    tempHandle.attrHandle = CYBLE_SGA2_SENSOR_CAL_LEVEL_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&testVal8;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for Sensor CalLevel */
//    if( System.BleNotifyCalLevel && ( Sensor.CalLevel != Sensor.CalLevelPrevious ) )
//    {
//        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
//        Sensor.CalLevelPrevious = Sensor.CalLevel;
//    }

    /* Update CAL_Z_COUNTS value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_Z_COUNTS_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalZCounts;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update CAL_ZERO_ERROR value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_ZERO_ERROR_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalZeroError;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for System.CalZeroError */
    if( System.BleNotifyCalZeroError && ( System.CalZeroError != System.CalZeroErrorPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.CalZeroErrorPrevious = System.CalZeroError;
    }

    /* Update CAL_STEP value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_STEP_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalStep;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for Sensor Life */
    if( System.BleNotifyCalStep && ( System.CalStep != System.CalStepPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.CalStepPrevious = System.CalStep;
    }

    /* Update CAL_SPEED value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_SPEED_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalSpeed;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for System.CalSpeed */
    if( System.BleNotifyCalSpeed && ( System.CalSpeed != System.CalSpeedPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.CalSpeedPrevious = System.CalSpeed;
    }

    /* Update CAL_AS_FOUND value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_AS_FOUND_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalAsFound;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for System.CalAsFound */
    if( System.BleNotifyCalAsFound && ( System.CalAsFound != System.CalAsFoundPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.CalAsFoundPrevious = System.CalAsFound;
    }

    /* Update CAL_ADJUSTED value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_ADJUSTED_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalAdjusted;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for System.CalAsFound */
    if( System.BleNotifyCalAdjusted && ( System.CalAdjusted != System.CalAdjustedPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.CalAdjustedPrevious = System.CalAdjusted;
    }

    /* Update CAL_COUNTS value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_COUNTS_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalCounts;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);

    /* Update SENSOR_LIFE value */
    tempHandle.attrHandle = CYBLE_SGA2_SENSOR_LIFE_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&testVal8;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for Sensor Life */
//    if( System.BleNotifyLife && ( Sensor.Life != Sensor.LifePrevious ) )
//    {
//        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
//        Sensor.LifePrevious = Sensor.Life;
//    }

    /* Update CAL_CLEARING value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_CLEARING_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalClearing;
    tempHandle.value.len = 2;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for Sensor CalClearing */
    if( System.BleNotifyCalClearing && ( System.CalClearing != System.CalClearingPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.CalClearingPrevious = System.CalClearing;
    }

    /* Update CAL_SPAN_ERROR value */
    tempHandle.attrHandle = CYBLE_SGA2_CAL_SPAN_ERROR_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.CalSpanError;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for System.CalSpanError */
    if( System.BleNotifyCalSpanError && ( System.CalSpanError != System.CalSpanErrorPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.CalSpanErrorPrevious = System.CalSpanError;
    }

    /* Update CALIBRATION_STATUS value */
    tempHandle.attrHandle = CYBLE_SGA2_CALIBRATION_STATUS_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&sensor[CALSTATUSMSB]; //&System.CalibrationStatus;
    tempHandle.value.len = 2;//1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for System.CalibrationStatus */
    if( System.BleNotifyCalibrationStatus)// && ( System.CalibrationStatus != System.CalibrationStatusPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.CalibrationStatusPrevious = System.CalibrationStatus;
    }
    /* Update READING_SCALED value */
    tempHandle.attrHandle = CYBLE_SGA2_READING_SCALED_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&testVal8;
    tempHandle.value.len = 4;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for Sensor.ReadingScaled */
//    if( System.BleNotifyReadingScaled && ( Sensor.ReadingScaled != Sensor.ReadingScaledPrevious ) )
//    {
//        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
//        Sensor.ReadingScaledPrevious = Sensor.ReadingScaled;
//    }

    /* Update ALERT_STATUS value */
    tempHandle.attrHandle = CYBLE_SGA2_ALERT_STATUS_CHAR_HANDLE;
    tempHandle.value.val = (uint8*)&System.AlertStatus;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,0);
    /* If notifications have been requested for System.AlertStatus */
    if( System.BleNotifyAlertStatus && ( System.AlertStatus != System.AlertStatusPrevious ) )
    {
        CyBle_GattsNotification( cyBle_connHandle, &tempHandle );               /* Notify the client */
        System.AlertStatusPrevious = System.AlertStatus;
    }

}




int capsenseNotify;
uint8_t bleConnected;

CYBLE_CONN_HANDLE_T connectionHandle;

/* define the test register to switch the PA/LNA hardware control pins */
#define CYREG_SRSS_TST_DDFT_CTRL 0x40030008

//void Stack_Handler(uint32 eventCode, void *eventParam){
//    
//    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
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
//            bleConnected =0;
//            BLETimer_Start();
//            
//            break;
//            
//        case CYBLE_EVT_GATT_CONNECT_IND:
//            connectionHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;
//            bleConnected =1;
//            
//#ifdef DEEPSLEEP            
//            ResetBLETimer();
//#endif            
//            //updateData();
//            updateOurBleData();
//            
//            break;
//        
//        case CYBLE_EVT_GATTS_WRITE_REQ:
//            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
//            
//            /* Requests to write variables */
//            /* It's our sgaBleRemote variable */            
//            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_REMOTE_CHAR_HANDLE)
//            {
//                /* Only update and respond if the write to the GATT Database is allowed */
//                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
//                {
//                    BleControl = wrReqParam->handleValPair.value.val[0];      /* Update our local copy */
//                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
//                }
//                
//                // send i2c command here?
//                runtime_CtrlSensor( CYBLE_SGA1_SYS_REMOTE_CHAR_HANDLE+2 , BleControl);
//            }
//            
//            /* It's a request for notifications for our Sensor.Reading (SYS_READING) */
//            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_READING_SYS_READING_CCCD_DESC_HANDLE )
//            {
//                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
//                System.BleNotifyReading = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
//                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
//            }
//            
//            /* It's a request for notifications for our Sensor.Status (SYS_STATUS) */
//            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
//            {
//                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
//                System.BleNotifyReading = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
//                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
//            }
//            break;
//            
//            break;
//        default:
//            break;    
//    }
//    
//    
//    
//    
//    
//    
//}


/*******************************************************************************
* Function Name: Stack_Handler
********************************************************************************
* Summary:
*  Stack handler for BLE communications.
* 
* Parameters:
*  eventCode
*  eventParam
*
* Return:
*  None
*
*******************************************************************************/
void Stack_Handler( uint32 eventCode, void *eventParam )
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;    

    switch( eventCode )                                                         /* Handle any BLE events */
    {
        case CYBLE_EVT_STACK_ON:                                                /* Handle BLE stack started */
            /* Mandatory events to be handled by BLE application code */
            /* Enable the Skyworks SE2438T PA/LNA */
            CSD_Write(1);
            CPS_Write(1);
            /* Configure the Link Layer to automatically switch PA control pin P3[2] and LNA control pin P3[3] */
            CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLESS_RF_CONFIG), 0x0331);
            CY_SET_XTND_REG32((void CYFAR *)(CYREG_SRSS_TST_DDFT_CTRL), 0x80000302);
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:                                 /* Handle BLE disconnection */
            CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );             /* Start advertising */
            bleConnected =0;
            BLETimer_Start();
            if( System.BleInAuxCalState == TRUE ) System.BleControl = 0;        /* In loop cal or other non normal state */
            break;
        case CYBLE_EVT_GATT_CONNECT_IND:                                        /* Handle BLE connection */
            //updateData();
            updateOurBleData();                                                 /* Update the GATT DB with our data */
            connectionHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;
            bleConnected =1;
            
#ifdef DEEPSLEEP            
            ResetBLETimer();
#endif            
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:                                           /* Handle a write request from client */
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;          /* Get the attribute trying to be written */

            /* Requests to write variables */
            /* It's our sgaBleRemote variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_REMOTE_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    System.BleControl = wrReqParam->handleValPair.value.val[0];      /* Update our local copy */
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
                }
                runtime_CtrlSensor( CYBLE_SGA1_SYS_REMOTE_CHAR_HANDLE+2 , System.BleControl); //??? Needs testing!!!!!!
            }
            /* It's our CAN Node ID variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_CAN_ID_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    System.CanNodeId = wrReqParam->handleValPair.value.val[0];  /* Update our local copy */
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
//                    FM24VN10_Write_8( SYS_I2C_FRAM_ADDR_B0, SYS_EE8_CAN_NODE_ID, System.CanNodeId );
//                    if( SA100_I2C_INSTALLED ) SA100I2C_Write_8( SA100_CEC_I2C_ADDR, SA100_I2C_CanNodeId, System.CanNodeId );
//                    SA100CEC_Write_8( CEC_OD_SYS_U8_CANNodeID, 0, System.CanNodeId );
//                    SA100CEC_Reset( CEC_RESET_COMMS );
                }
            }
            /* It's our CAN Channel variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_CAN_CHAN_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    System.CanChannel = wrReqParam->handleValPair.value.val[0];  /* Update our local copy */
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
//                    FM24VN10_Write_8( SYS_I2C_FRAM_ADDR_B0, SYS_EE8_CAN_CHANNEL, System.CanChannel);
//                    if( SA100_I2C_INSTALLED ) SA100I2C_Write_8( SA100_CEC_I2C_ADDR, SA100_I2C_CanChannel, System.CanChannel );
//                    SA100CEC_Write_8( CEC_OD_SYS_U8_channel, 0, System.CanChannel );
//                    SA100CEC_Reset( CEC_RESET_COMMS );
                }
            }
            /* It's our ALERT_1 variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_ALERT_1_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
                }
            }
            /* It's our ALERT_2 variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_ALERT_2_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
                }
            }
            /* It's our PIN variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_PIN_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */

                }
            }
            /* It's our SENSOR_TAG variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_SENSOR_TAG_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
//                    for( uint8 i = 0; i < SENSOR_TAG_LENGTH; i++ )
//                    {
//                        System.SensorTag[i] = wrReqParam->handleValPair.value.val[i];  /* Update our local copy */
//                    }
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
//                    SysSaveSensorTagString();
                }
            }
            /* It's our SENSOR_CAL_LEVEL variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_SENSOR_CAL_LEVEL_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
                }                    
            }
            /* It's our CAL LOOP Channel variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_CAL_LOOP_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    System.BleCalLoop = wrReqParam->handleValPair.value.val[1];  /* Update our local copy */
                    System.BleCalLoop <<=8;
                    System.BleCalLoop |= wrReqParam->handleValPair.value.val[0];  /* Update our local copy */
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
                }
            }
            /* It's our CalibrationStatus variable */            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CALIBRATION_STATUS_CHAR_HANDLE)
            {
                /* Only update and respond if the write to the GATT Database is allowed */
                if(CYBLE_GATT_ERR_NONE == CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED))
                {
                    System.CalibrationStatus = wrReqParam->handleValPair.value.val[0];  /* Update our local copy */
                    CyBle_GattsWriteRsp(cyBle_connHandle);                      /* respond to the client */
                }
            }

            /* Request for Notifications */
            /* It's a request for notifications for our System.BleControl (SYS_REMOTE) */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_REMOTE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyControl = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our Sensor.Reading (SYS_READING) */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_READING_SYS_READING_CCCD_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyReading = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our Sensor.Status (SYS_STATUS) */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyStatus = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.AdcCounts (SYS_ADC) */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA1_SYS_ADC_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyAdcCounts = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our Sensor.Temperature */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_SENSOR_TEMPERATURE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyTemperature = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our Sensor.CalLevel */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_SENSOR_CAL_LEVEL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalLevel = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.CalZeroError */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CAL_ZERO_ERROR_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalZeroError = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.CalStep */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CAL_STEP_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalStep = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.CalSpeed */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CAL_SPEED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalSpeed = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.CalAsFound */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CAL_AS_FOUND_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalAsFound = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.CalAdjusted */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CAL_ADJUSTED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalAdjusted = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our Sensor.Life */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_SENSOR_LIFE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyLife = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our Sensor.CalClearing */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CAL_CLEARING_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalClearing = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.CalSpanError */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CAL_SPAN_ERROR_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalSpanError = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.CalibrationStatus */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_CALIBRATION_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyCalibrationStatus = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our Sensor.ReadingScaled */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_READING_SCALED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyReadingScaled = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            /* It's a request for notifications for our System.AlertStatus */
            if( wrReqParam->handleValPair.attrHandle == CYBLE_SGA2_ALERT_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE )
            {
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair,0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                System.BleNotifyAlertStatus = wrReqParam->handleValPair.value.val[0] & 0x01; /* Update local notification state */
                CyBle_GattsWriteRsp(cyBle_connHandle);                          /* respond to the client */
            }
            break;
        default:
            break;
            
    }
}



void ResetBLETimer(){
    BLETimer_Stop();
    BLETimer_WriteCounter(0);
}

void SetSleepPeriod(uint16_t period){
    BLETimer_Stop();
    BLETimer_WritePeriod(period);
    BLETimer_WriteCounter(0);
}

// if BLE gets disconnected we put MCU to Deeep Sleep Mode


void SysWdtInit( void )
{
//    /* Determin reset cause and proceed accordingly */
//    if(CySysGetResetReason(CY_SYS_RESET_WDT) == CY_SYS_RESET_WDT){
//        for(uint8_t i =0; i<20;i++){
//             LED_Write(~LED_Read());
//            CyDelay(50);
//        }
//    }else{
//        for(uint8_t i =0; i<6;i++){
//             LED_Write(~LED_Read());
//            CyDelay(200);
//        }
//    }
    
//    if ( 0u == CySysGetResetReason( CY_SYS_RESET_WDT ) )                        /* Startup after PowerUp/XRES event. */
//    {
//        CyDelay( 500 /* msecs */);                                             /* Delay so user can detect normal reset. */
//    }else{                                                                      /* Startup after WDT reset event. */
//        
//        /* Create fault condition(s) here with a delay. */
//        /* Danger output needs to be set appropiately here */
//        //System.AlertBits = SYS_ALERT_BIT_FAULT;
//        //System.AlertStatus = SYS_ALERT_FAULT;
//        //SA100CEC_UpdateRuntimeValues( SENSORS_CALC_READING_WARMUP );
//        //SAFETY_OUTPUT_Write( SYS_SAFE_NO );
//        //MC_RGBResetCauseWDT
//        //CyDelay( 10000 /* msecs */);                                             /* Delay so user can detect WDT reset. */
//        
//        
//    }

    /* Setup the Watchdog timer environment */
    //WdtIsr_StartEx( SysWdtIsrHandler );                                            /* Setup ISR for interrupts at WDT counter 0 events. */
    CyGlobalIntEnable;                                                          /* Enable global interrupts. */
	
	/* Set WDT counter 0 to generate interrupt on match */
	CySysWdtWriteMode( CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_INT );
	CySysWdtWriteMatch( CY_SYS_WDT_COUNTER0, WDT_COUNT0_MATCH );
	CySysWdtWriteClearOnMatch( CY_SYS_WDT_COUNTER0, 1u );

    CySysWdtWriteCascade( CY_SYS_WDT_CASCADE_01 );                              /* Enable WDT counters 0 and 1 cascade */
    
	/* Set WDT counter 1 to generate reset on match */
	CySysWdtWriteMatch( CY_SYS_WDT_COUNTER1, WDT_COUNT1_MATCH );
	CySysWdtWriteMode( CY_SYS_WDT_COUNTER1, CY_SYS_WDT_MODE_RESET );
    CySysWdtWriteClearOnMatch( CY_SYS_WDT_COUNTER1, 1u );
	
	CySysWdtEnable( CY_SYS_WDT_COUNTER0_MASK | CY_SYS_WDT_COUNTER1_MASK );      /* Enable WDT counters 0 and 1 */
	
	/* Lock WDT registers and try to disable WDT counters 0 and 1 */
	CySysWdtLock();
	CySysWdtDisable( CY_SYS_WDT_COUNTER1_MASK );
	CySysWdtUnlock();
}




void SysWdtReset( void )
{
	CySysWdtResetCounters( CY_SYS_WDT_COUNTER0_RESET );                         /* Reset WDT counter 0 */
    CySysWdtResetCounters( CY_SYS_WDT_COUNTER1_RESET );                         /* Reset WDT counter 1 */
    CyDelayUs( 200 );                                                           /* Pause 200ms */
}


void remove_trailing_spaces(char* dst, char *str){
    int i=0;
    int len = strlen(str);
    while(i<len){
        if(str[i] == ' '){
            dst[i] = '\0';
        }else{
            dst[i] =str[i];
        }
        i++;
    }
}


/* [] END OF FILE */
