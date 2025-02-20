#if !defined(MODBUS_H) /* MODBUS_H */
#define MODBUS_H

#include <project.h>    

#define MODBUS_RX_BUFFER_SIZE 200    
#define MODBUS_TX_BUFFER_SIZE 256 
#define MODBUS_COMMAND_SIZE 8
    
#define MODBUS_READ_CMD     0x3    
#define MODBUS_WRITE_CMD    0x6
    
extern uint8_t modbusRequestReceived;
extern uint8_t rs232RequestReceived;
    
    
void modbusSend(uint8_t SlaveAddress, uint8_t Mode,  uint16_t StartRegAddress, uint16_t RegCount ); 
void modbusSendBulk(uint8 SlaveAddress, uint8 Mode, uint16 RegCount );
void modbusWriteResponse(uint8_t mySlaveAddr , uint8_t modbusCommand , uint16_t startRegister,uint16_t data);
void modbusFlush(uint16_t bytes);
uint16 modbus_GenerateCRC(uint8_t *msg, uint16_t msglen);  

void rs232SendBulk(uint8 SlaveAddress, uint8 Mode, uint16 RegCount );
void rs232WriteResponse(uint8_t mySlaveAddr , uint8_t modbusCommand , uint16_t startRegister,uint16_t data);
void rs232Flush(uint16_t bytes);   

#endif /* MODBUS */