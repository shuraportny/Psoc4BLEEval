#include "modbus.h"


uint8_t modbus_rxBuffer[MODBUS_RX_BUFFER_SIZE];
uint8_t modbus_txBuffer[MODBUS_TX_BUFFER_SIZE];

uint8_t bytesIn=0;
uint8_t modbusRequestReceived=0;


void modbusSend(uint8 SlaveAddress, uint8 Mode,  uint16 StartRegAddress, uint16 RegCount )
{
    uint16 crc;
    uint8 i;
    // Build msg 
    modbus_txBuffer[0] = (uint8) SlaveAddress;
    modbus_txBuffer[1] = (uint8) Mode;
    modbus_txBuffer[2] = (uint8) 2;//(RegCount >> 8);
    modbus_txBuffer[3] = (uint8) 11;//RegCount;
    modbus_txBuffer[4] = (uint8) 12; 
    crc = (uint16) modbus_GenerateCRC(modbus_txBuffer,7);
    modbus_txBuffer[5] = (uint8) (crc >> 8);
    modbus_txBuffer[6] = (uint8) (crc & 0xFF);
    TXEN_Write(1);
    for (i=0; i<7; i++) {
        ModbusUART_UartPutChar(modbus_txBuffer[i]); 
    }
    /*Wait until trasmission complete*/
    while (0u != (ModbusUART_SpiUartGetTxBufferSize() + ModbusUART_GET_TX_FIFO_SR_VALID));
    TXEN_Write(0);
}

void modbusSendBulk(uint8 SlaveAddress, uint8 Mode, uint16 RegCount )
{
    uint16 crc;
    uint8 i;
    uint16_t bytes =RegCount*2 ;
   
    modbus_txBuffer[0] = (uint8) SlaveAddress;
    modbus_txBuffer[1] = (uint8) Mode;
    modbus_txBuffer[2] = (uint8) bytes;
    crc = (uint16) modbus_GenerateCRC(modbus_txBuffer,bytes+5);
    modbus_txBuffer[bytes+3] = (uint8) (crc >> 8);
    modbus_txBuffer[bytes+4] = (uint8) (crc & 0xFF);
    modbusFlush(bytes+5); // bytes + preamble+ crc
}

//void rs232SendBulk(uint8 SlaveAddress, uint8 Mode, uint16 RegCount )
//{
//    uint16 crc;
//    uint8 i;
//    uint16_t bytes =RegCount*2 ;
//   
//    modbus_txBuffer[0] = (uint8) SlaveAddress;
//    modbus_txBuffer[1] = (uint8) Mode;
//    modbus_txBuffer[2] = (uint8) bytes;
//    crc = (uint16) modbus_GenerateCRC(modbus_txBuffer,bytes+5);
//    modbus_txBuffer[bytes+3] = (uint8) (crc >> 8);
//    modbus_txBuffer[bytes+4] = (uint8) (crc & 0xFF);
//    rs232Flush(bytes+5); // bytes + preamble+ crc
//}


//void rs232WriteResponse(uint8 SlaveAddress, uint8 Mode,  uint16 StartRegAddress, uint16 data )
//{
//    uint16 crc;
//    uint8 i;
//     
//    // Build msg 
//    modbus_txBuffer[0] = (uint8) SlaveAddress;
//    modbus_txBuffer[1] = (uint8) Mode;
//    modbus_txBuffer[2] = (uint8) (StartRegAddress>>8)&0xFF;
//    modbus_txBuffer[3] = (uint8) StartRegAddress & 0xFF;
//    modbus_txBuffer[4] = (uint8) (data << 8) & 0xFF ; 
//    modbus_txBuffer[5] = (uint8) data & 0xFF;
//    crc = (uint16) modbus_GenerateCRC(modbus_txBuffer,8);
//    modbus_txBuffer[6] = (uint8) (crc >> 8);
//    modbus_txBuffer[7] = (uint8) (crc & 0xFF);
//    
//    for (i=0; i<8; i++) {
//        RS232UART_PutChar(modbus_txBuffer[i]); 
//    }
//    
//    
//}


void modbusWriteResponse(uint8 SlaveAddress, uint8 Mode,  uint16 StartRegAddress, uint16 data )
{
    uint16 crc;
    uint8 i;
     
    // Build msg 
    modbus_txBuffer[0] = (uint8) SlaveAddress;
    modbus_txBuffer[1] = (uint8) Mode;
    
    modbus_txBuffer[2] = (uint8) (StartRegAddress>>8)&0xFF;
    modbus_txBuffer[3] = (uint8) StartRegAddress & 0xFF;
    
    modbus_txBuffer[4] = (uint8) (data << 8) & 0xFF ; 
    modbus_txBuffer[5] = (uint8) data & 0xFF;
    
    crc = (uint16) modbus_GenerateCRC(modbus_txBuffer,8);

    modbus_txBuffer[6] = (uint8) (crc >> 8);
    modbus_txBuffer[7] = (uint8) (crc & 0xFF);
    
    
    TXEN_Write(1);
    for (i=0; i<8; i++) {
        ModbusUART_UartPutChar(modbus_txBuffer[i]); 
    }
    /*Wait until trasmission complete*/
    while (0u != (ModbusUART_SpiUartGetTxBufferSize() + ModbusUART_GET_TX_FIFO_SR_VALID));
    TXEN_Write(0);
}


//void rs232Flush(uint16_t bytes){
//    for (uint16_t i=0; i<bytes; i++) {
//        RS232UART_PutChar(modbus_txBuffer[i]); 
//    }
//}


void modbusFlush(uint16_t bytes){
    TXEN_Write(1);
    CyDelay(10);
    for (uint16_t i=0; i<bytes; i++) {
        ModbusUART_UartPutChar(modbus_txBuffer[i]); 
        //CyDelay(2);
    }
    /*Wait until trasmission complete*/
    while (0u != (ModbusUART_SpiUartGetTxBufferSize() + ModbusUART_GET_TX_FIFO_SR_VALID));
    //CyDelay(2);
    TXEN_Write(0);    
}

uint16 modbus_GenerateCRC(uint8 *msg, uint16 msglen)
{
    uint16 crc = 0xFFFF;
    uint16 crcHigh = 0;
    uint16 crcLow = 0;
    int i,j = 0;

      for(i=0;i<msglen-2;i++){
        crc ^= msg[i];
        for(j=8; j!=0; j--){
          if((crc & 0x0001) != 0){
            crc >>= 1;
            crc ^= 0xA001;
          }
          else{
            crc >>= 1;
          }
        }
      }
    //bytes are wrong way round so doing a swap here..
    crcHigh = (crc & 0x00FF) <<8;
    crcLow = (crc & 0xFF00) >>8;
    crcHigh |= crcLow;
    crc = crcHigh;
    return crc;
}


void modbus_Reset(void){
    bytesIn =0;
}