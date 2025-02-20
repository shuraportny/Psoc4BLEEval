/***************************************************************************//**
* \file SerialNVRAM_1.c       
* \version 1.0
*
* \brief
* This file provides the source code to the API for the SerialNVRAM 
* Component.
* 
********************************************************************************
* Copyright (2017), Cypress Semiconductor Corporation.
******************************************************************************** 
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
* CYPRESS PROVIDES THIS SOFTWARE "AS IS" AND MAKES NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED 
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS 
* FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include "cytypes.h"
#include "SerialNVRAM_1.h"

/* Internal constants */
#define SerialNVRAM_1_DUMMY_BYTE                           (0X22U)

CY_INLINE static void SerialNVRAM_1_SetDefaultPins(void);

#if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
    static SerialNVRAM_1_status SerialNVRAM_1_SpiSelectDevice(uint8 nvramId);
    static SerialNVRAM_1_status SerialNVRAM_1_SpiDeSelectDevice(uint8 nvramId);
    static SerialNVRAM_1_status SerialNVRAM_1_SpiTxBusyCheck(void);
    static SerialNVRAM_1_status SerialNVRAM_1_SpiRxBufferCheck(void);
    static SerialNVRAM_1_status SerialNVRAM_1_SpiSetWriteEnable(uint8 nvramId);
    static SerialNVRAM_1_status SerialNVRAM_1_SpiBufferWrite(const uint8 dataWritePtr[], 
                                                                   uint32 totalDataCount);
    static SerialNVRAM_1_status SerialNVRAM_1_SpiBufferRead(uint8 dataReadPtr[], 
                                                                  uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiMemoryWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiMemoryRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiRtcRegWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiRtcRegRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiNvCommand(uint8 nvramId, 
                                                                           uint32 nvcmd);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiSerialNoWrite(uint8 nvramId,
                                                                               const uint8 *dataPtr);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiSerialNoRead(uint8 nvramId,
                                                                              uint8 *dataPtr);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiDevIdRead(uint8 nvramId, 
                                                                           uint8 *dataPtr, 
                                                                           uint32 iDLength);
#endif

#if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
    static uint32 SerialNVRAM_1_I2cDataWrite(const uint8 dataWritePtr[], uint32 totalDataCount);
    static uint32 SerialNVRAM_1_I2cDataRead(uint8 dataReadPtr[], uint32 totalDataCount);
    static SerialNVRAM_1_status SerialNVRAM_1_I2CSendStop(uint32 i2cStatus);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cMemoryWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cMemoryRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cRtcRegWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cRtcRegRead(uint8 nvramId, 
                                                                           uint32 addr, 
                                                                           uint8 *dataReadPtr, 
                                                                           uint32 totalDataCount);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cNvCommand(uint8 nvramId, 
                                                                           uint32 nvcmd);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cSerialNoWrite(uint8 nvramId,
                                                                               const uint8 *dataPtr);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cSerialNoRead(uint8 nvramId,
                                                                              uint8 *dataPtr);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cUniqueSleep(uint8 nvramId);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cUniqueSerialNoRead(uint8 nvramId,
                                                                                    uint8 *dataPtr);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cUniqueDevIdRead(uint8 nvramId,
                                                                                 uint8 *dataPtr,
                                                                                 uint32 iDLength);
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cDevIdRead(uint8 nvramId, 
                                                                           uint8 *dataPtr, 
                                                                           uint32 iDLength);
#endif

/** SerialNVRAM_1_initVar indicates whether the SerialNVRAM_1  component
*  has been initialized. The variable is initialized to 0 and set to 1 the first
*  time SerialNVRAM_1_Start() is called.
*  This allows the component to restart without reinitialization after the first 
*  call to the SerialNVRAM_1_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  SerialNVRAM_1_Init() function can be called before the 
*  SerialNVRAM_1_Start() function.
*/
uint8 SerialNVRAM_1_initVar = 0u;


/*******************************************************************************
* Function Name:   SerialNVRAM_1_SetDefaultPins
****************************************************************************//**
*
*  Sets the control pins to the default state.
*
*******************************************************************************/
CY_INLINE static void SerialNVRAM_1_SetDefaultPins(void) 
{   
    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        /* Disable the chip */
        SerialNVRAM_1_CS_0_OFF;
        #if (SerialNVRAM_1_CS1 < SerialNVRAM_1_SPI_CHIP_SELECT)
            SerialNVRAM_1_CS_1_OFF;
            #if (SerialNVRAM_1_CS2 < SerialNVRAM_1_SPI_CHIP_SELECT)
                SerialNVRAM_1_CS_2_OFF;
            #endif
                #if (SerialNVRAM_1_CS3 < SerialNVRAM_1_SPI_CHIP_SELECT)
                    SerialNVRAM_1_CS_3_OFF;
                #endif
        #endif
        #if (1 == SerialNVRAM_1_ENABLE_HOLD)
            SerialNVRAM_1_SetHold(SerialNVRAM_1_HIGH);
        #endif
        #if (1 == SerialNVRAM_1_ENABLE_WRITE_PROTECTION)
            SerialNVRAM_1_SetWp(SerialNVRAM_1_HIGH);
        #endif
    #endif

    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        #if (1 == SerialNVRAM_1_ENABLE_WRITE_PROTECTION)
            SerialNVRAM_1_SetWp(SerialNVRAM_1_LOW);
        #endif
    #endif
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_Init
****************************************************************************//**
*
*  The initialization routine for the NVRAM component. 
*   Initializes the SPI/I2C block, CS, WP, and Hold configurations.
*
*******************************************************************************/
void SerialNVRAM_1_Init(void) 
{   
    /* Start the communication interface */
    SerialNVRAM_1_InterfaceStart();
    
    /* Init the pins (CS, HOLD, WP) */
    SerialNVRAM_1_SetDefaultPins();
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_Start
****************************************************************************//**
*
*  The start function, initializes the SerialNVRAM with the default values.
*
* \globalvars
*   SerialNVRAM_1_initVar: The global variable, defines if the component  
*                             will be initialized to the schematic state. 
*
*******************************************************************************/
void SerialNVRAM_1_Start(void) 
{
    if(0u == SerialNVRAM_1_initVar)      
    {
        SerialNVRAM_1_Init();
        SerialNVRAM_1_initVar = 1u;      
    }
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_Stop
****************************************************************************//**
*
* Disables the Serial NVRAM component but does not stop the
* Master component.
*
*******************************************************************************/
void SerialNVRAM_1_Stop(void) 
{
    SerialNVRAM_1_SetDefaultPins();
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_GetStatus
****************************************************************************//**
*
* Returns the external device ready/busy status after the initiated 
* transfer is complete.
*
*  \note The function always returns SerialNVRAM_1_SUCCESS for F-RAM devices.
*
*  \param nvramId: CS for SPI, the slave address for I2C. 
* The nvramId parameter for I2C devices have the following I2C slave 
* address:  0 1 0 1 0 A2 A1 A0. The three LSB bits are configurable 
* slave address inputs A2, A1, A0. Some I2C NVRAMs use three LSB bits 
* as memory page select to address higher density than addressable through 
* dedicated address byte (s) (one or two bytes) sent after the I2C command byte. 
* For example 4Kb and 16Kb I2C F-RAMs use A0 and A2, A1,A0 bits respectively 
* as page select bits followed by 1-byte memory address. 
* Similarly, 1Mb device use A0 as page select address bit followed by 
* 2-byte memory address.
* The I2C NVRAM devices internally ignore the page select bit setting and 
* always send an ACK during the command cycle. However, page select bits are 
* internally used to set the memory page address for the subsequent access. 
* For example: the CY14C101I device has Pin A2 connected to the high level 
* and Pin A1 connected to the ground. This corresponds to valid 
* nvramId = 0xA4 or 0xA5 with lower or upper page address set.
*
*  \return 
*  status:
*  * SerialNVRAM_1_SUCCESS - data is sent/received and the component is ready 
*     to send/receive new data
*  * SerialNVRAM_1_DEVICE_BUSY - the component is sending/receiving previous
*      data or the device error.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_GetStatus(uint8 nvramId) 
{
    SerialNVRAM_1_status status;

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        uint8 dataByte;

        status = SerialNVRAM_1_StatusRegRead(nvramId, &dataByte);
        if (SerialNVRAM_1_SUCCESS == status)
        {
            if (SerialNVRAM_1_SPI_NOT_RDY != (dataByte & SerialNVRAM_1_SPI_NOT_RDY))
            {
                status = SerialNVRAM_1_SUCCESS;
            }
            else
            {
                status = SerialNVRAM_1_DEVICE_BUSY;
            }
        }
        else
        {
            status = SerialNVRAM_1_DEVICE_BUSY;
        }    
        
    #endif

    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        uint32 dataByte;
    
        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK;
    
        /* Set the I2C Memory selection mask */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_MEM_MASK;
    
        /*  Send the Start condition and slave ID for Write */
        dataByte = _I2CMasterSendStart((uint32)nvramId, 
                                                         _I2C_WRITE_XFER_MODE, 
                                                         SerialNVRAM_1_I2C_COM_TIMEOUT_MS);

        /* Send Stop */
        (void)_I2CMasterSendStop(SerialNVRAM_1_I2C_COM_TIMEOUT_MS);

        if (_I2C_MSTR_ERR_LB_NAK != dataByte)
        {
            status = SerialNVRAM_1_SUCCESS;
        }
        else
        {
            status = SerialNVRAM_1_DEVICE_BUSY;
        }   
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_MemoryWrite
****************************************************************************//**
*
* Writes the totalDataCount number of data into NVRAM.
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*
*  \param addr: The 1/2/3-byte NVRAM address for Write.
*  \param *dataWritePtr: The pointer to an array of data bytes to be written.
*  \param totalDataCount: The number of data bytes to be written.
*
* \return
* Error status:
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_MemoryWrite(uint8 nvramId, 
                                                     uint32 addr, 
                                                     const uint8 *dataWritePtr, 
                                                     uint32 totalDataCount) 
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    CYASSERT(dataWritePtr); /* dataWritePtr cannot be NULL */

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_SpiMemoryWrite(nvramId, 
                                                 addr, 
                                                 dataWritePtr, 
                                                 totalDataCount);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_I2cMemoryWrite(nvramId, 
                                                 addr, 
                                                 dataWritePtr, 
                                                 totalDataCount);
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_MemoryRead
****************************************************************************//**
*
* Reads the totalDataCount number of data from NVRAM. 
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*  \param addr: The 1/2/3-byte NVRAM address for Write.
*  \param *dataReadPtr: The pointer to an array for storing data bytes.
*  \param totalDataCount: The number of data bytes to be read.
*
* \return
* Error status:
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_MemoryRead(uint8 nvramId, 
                                                    uint32 addr, 
                                                    uint8 *dataReadPtr, 
                                                    uint32 totalDataCount)
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_SpiMemoryRead(nvramId, 
                                                addr, 
                                                dataReadPtr, 
                                                totalDataCount);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_I2cMemoryRead(nvramId, 
                                                addr, 
                                                dataReadPtr, 
                                                totalDataCount);
    #endif

    return status;
}


#if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_CurrentMemoryRead
    ****************************************************************************//**
    *
    * Reads totalDataCount number of the data current address of I2C NVRAM. 
    *
    *  \param nvramId: The slave address for I2C.
    *  The nvramId parameter for I2C devices has the following format: 
    *  0 0 0 0 0 A2 A1 A0. The R/W bit is not used.
    *  Three LSB bits define the slave address inputs A2, A1 or A2, A1, and A0 bits
    *  for the I2C devices that have A2, A1, and A0 bits for the page select.  
    *  Bit A0 is the page select bit and it equals to 1 for address from 0x10000.
    *  For example: the CY14C101I device has Pin A2 connected to the high level 
    *  and Pin A1 connected to the ground. This corresponds to 
    *  valid 0x04 for reading data with the address below 0x10000 and
    *  nvramId = 0x05 for reading data with the address from 0x10000.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A Communication error.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_CurrentMemoryRead(uint8 nvramId, 
                                                               uint8 *dataReadPtr, 
                                                               uint32 totalDataCount)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;
 
        CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */

        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK;
        
        /* Set the I2C Memory selection mask */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_MEM_MASK;
        
        /* Send the Start condition and slave ID for Read */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_READ_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);

        /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of the totalDataCount bytes */
            i2cStatus = SerialNVRAM_1_I2cDataRead(dataReadPtr, totalDataCount);
        }
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);

        return status;
    }
#endif


#if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_MemoryFastReadOpcode
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from SPI NVRAM using
    * the Fast Read command.
    *
    *  \param nvramId: CS for SPI
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * Error status:
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
    *     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_MemoryFastReadOpcode(uint8 nvramId, 
                                                                  uint32 addr, 
                                                                  uint8 *dataReadPtr, 
                                                                  uint32 totalDataCount)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */

        /* Select the F-RAM device */
        status = SerialNVRAM_1_SpiSelectDevice(nvramId);
        
        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Send the F-RAM Fast Read command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_SRAM_FAST_READ_CMD);   
            
            /* For densities greater than or equal to 1MBit, send a 3-byte address */
            #if (SerialNVRAM_1_DENSITY_1_MBIT <= SerialNVRAM_1_DENSITY)
                _SpiUartWriteTxData((addr & SerialNVRAM_1_MSB_ADDR_MASK)>>SerialNVRAM_1_MSB_ADDR_SHIFTBITS);
            #endif
        
            /* Send a 2-byte address */
            _SpiUartWriteTxData((addr & SerialNVRAM_1_ISB_ADDR_MASK)>>SerialNVRAM_1_ISB_ADDR_SHIFTBITS);
            _SpiUartWriteTxData(addr);
        
            /* Wait for the transmission to complete */
            status = SerialNVRAM_1_SpiTxBusyCheck();
            
            if (SerialNVRAM_1_SUCCESS == status)
            {
                /* Send the dummy byte to start receiving data */
                _SpiUartWriteTxData(SerialNVRAM_1_DUMMY_BYTE);
                
                /* Read the data bytes */
                status = SerialNVRAM_1_SpiBufferRead(dataReadPtr, totalDataCount);
            }
            
            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }

        
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_StatusRegWrite
    ****************************************************************************//**
    *
    * Writes the NVRAM Status register.
    *
    *  \param nvramId: CS for SPI.
    *  \param dataByte: The 1-byte status register data to be written.
    *
    * \return
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
    *     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_StatusRegWrite(uint8 nvramId, uint8 dataByte)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Send the WREN command */
        status = SerialNVRAM_1_SpiSetWriteEnable(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)SerialNVRAM_1_SpiSelectDevice(nvramId);

            /* Send Write Status Register command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_WRSR_CMD);

            /* Send the status register data */
            _SpiUartWriteTxData((uint32)dataByte);
            
            /* Wait for the transmission to complete */
            status = SerialNVRAM_1_SpiTxBusyCheck();

            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_StatusRegRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Status register. 
    *
    *  \param nvramId: CS for SPI.
    *  \param *dataByte: The pointer to the holding status register value.
    *
    * \return
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
    *     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_StatusRegRead(uint8 nvramId, uint8 *dataByte)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Clear the receive buffer */
        _SpiUartClearRxBuffer();

        /* Select the F-RAM device */
        status = SerialNVRAM_1_SpiSelectDevice(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Send the status register Read command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_RDSR_CMD);

            /* Send the dummy byte to receive data */
            _SpiUartWriteTxData(0x00U);

            /* Wait for the transmission to complete */
            status = SerialNVRAM_1_SpiTxBusyCheck();
        
            if (SerialNVRAM_1_SUCCESS == status)
            {
                /* Ensure data is received in the receive buffer */
                status = SerialNVRAM_1_SpiRxBufferCheck();
                
                /* Read the buffer twice because the second byte received 
                   is the status reg data 
                */
                *dataByte = (uint8)_SpiUartReadRxData(); 
                *dataByte = (uint8)_SpiUartReadRxData();
            }

            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }

    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_WriteProcessorCompanion
    ****************************************************************************//**
    *
    * Writes the SPI F-RAM processor companion register. 
    * This function is applicable for the devices which support WRPC and RDPC. 
    * Refer to the device datasheet for details.
    *
    *  \note To write the RTC register of the companion device, this function 
    *  should set the W bit of the RTC/Alarm Control register
    *  (SerialNVRAM_1_COMPANION_RTC_ALARM_CTL) and then write the RTC register.
    *  For example, the following code updates the Day register with value = 4:
    *  SerialNVRAM_1_status status;
    *  uint8 writeCommand = 2u;
    *  uint8 day = 4u;
    *  status = SerialNVRAM_1_WriteProcessorCompanion(SerialNVRAM_1_CS0,
    *                             SerialNVRAM_1_COMPANION_RTC_ALARM_CTL, 
    *                             &writeCommand, 1u);
    *  status = SerialNVRAM_1_WriteProcessorCompanion(SerialNVRAM_1_CS0,
    *                             SerialNVRAM_1_COMPANION_DAY_01_07, 
    *                             &day, 1u);
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 8-bit F-RAM Processor companion
    *  register address for Write.
    *  \param *dataPtr: The pointer to an array of data to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_WriteProcessorCompanion(uint8 nvramId,
                                                                     uint32 addr,
                                                                     const uint8 *dataPtr,
                                                                     uint32 totalDataCount)
    {
        SerialNVRAM_1_status status;

        /* Send the WREN command */
        status = SerialNVRAM_1_SpiSetWriteEnable(nvramId);
        
        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)SerialNVRAM_1_SpiSelectDevice(nvramId);

            /* Send the processor companion register Write command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_WRPC_CMD);
            
            /* Send 1 register address byte */
            _SpiUartWriteTxData(addr);
            
            /* Send the processor companion register */
            status = SerialNVRAM_1_SpiBufferWrite(dataPtr, totalDataCount);

            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId); 
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_ReadProcessorCompanion
    ****************************************************************************//**
    *
    * Reads the SPI F-RAM processor companion register. 
    * This function is applicable for the devices which support WRPC and RDPC. 
    * Refer to the device datasheet for details.
    *
    *  \note To read the data from the RTC register of the companion device, 
    *  this function should set the R bit of the RTC/Alarm Control register
    *  (SerialNVRAM_1_COMPANION_RTC_ALARM_CTL) and then read the RTC register.
    *  For example, the following code reads the Day register:
    *  SerialNVRAM_1_status status;
    *  uint8 readCommand = 1u;
    *  uint8 day = 4u;
    *  status = SerialNVRAM_1_WriteProcessorCompanion(SerialNVRAM_1_CS0, 
    *                             SerialNVRAM_1_COMPANION_RTC_ALARM_CTL, 
    *                             &readCommand, 1u);
    *  status = SerialNVRAM_1_ReadProcessorCompanion(SerialNVRAM_1_CS0, 
    *                             SerialNVRAM_1_COMPANION_DAY_01_07,
    *                             &day, 1u);
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 8-bit F-RAM Processor companion
    *  register address for Read.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_ReadProcessorCompanion(uint8 nvramId,
                                                                    uint32 addr,
                                                                    uint8 *dataReadPtr,
                                                                    uint32 totalDataCount)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Select the F-RAM device */
        status = SerialNVRAM_1_SpiSelectDevice(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Send the F-RAM processor companion register Read command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_RDPC_CMD);   
        
            /* Send 1 address byte */
            _SpiUartWriteTxData(addr);
        
            /* Read the data bytes */
            status = SerialNVRAM_1_SpiBufferRead(dataReadPtr, totalDataCount);
            
            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
#endif


#if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_MemCtrlRegWrite
    ****************************************************************************//**
    *
    * Writes to NVRAM Memory Control Register.    
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param dataByte: The 1-byte Memory Control register data to be written.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
    *     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_MemCtrlRegWrite(uint8 nvramId, uint8 dataByte)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
        
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_CR_MASK;

        /*  Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId,
                                                       _I2C_WRITE_XFER_MODE, 
                                                       SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the Memory Control Register address byte */
            i2cStatus = _I2CMasterWriteByte(SerialNVRAM_1_MEM_CTR_REG_ADDR, 
                                                              SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
            if (_I2C_MSTR_NO_ERROR == i2cStatus)
            {
               /* Send the data byte for Write */
               i2cStatus = _I2CMasterWriteByte((uint32)dataByte, 
                                                                 SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
            }
        }

        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus); 

        return status;
    }


    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_MemCtrlRegRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Memory Control Register content.  
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param *dataByte: The pointer for holding the Control register value.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_MemCtrlRegRead(uint8 nvramId, uint8 *dataByte)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
        
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_CR_MASK;

        /* Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        /* Write the the Memory Control Register address to the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the address byte */
            i2cStatus = _I2CMasterWriteByte(SerialNVRAM_1_MEM_CTR_REG_ADDR, 
                                                              SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = _I2CMasterSendRestart((uint32)nvramId, 
                                                                _I2C_READ_XFER_MODE, 
                                                                SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        /* Read the byte with NAK data */
        i2cStatus = _I2CMasterReadByte(_I2C_NAK_DATA, 
                                                         dataByte, 
                                                         SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus); 

        return status;
    }
#endif


/*******************************************************************************
* Function Name:   SerialNVRAM_1_Sleep
****************************************************************************//**
*
* Sends the NVRAM command for sleep.
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*  The nvramId parameter for the FM24VN10 families has the following I2C slave
*  address format: 0 1 0 1 0 A2 A1 A16. 
*  Bits A2 and A1 are the slave address inputs. 
*  Bit A16 is the page select bit and it can have any value for this function. 
*  Four FM24VN10 devices can be connected to I2C bus with the following
*  nvramId parameter values:
*  * 0x50 - Both A2 and A1 pins are connected to the ground.
*  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
*  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
*  * 0x56 – Both A2 and A1 pins are connected to the high level.
*
* \return 
* Error status
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_Sleep(uint8 nvramId)
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status =  SerialNVRAM_1_NvCommand(nvramId, SerialNVRAM_1_NVRAM_SLEEP_CMD);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        /* Check if the device is FM24V10 */
        if (SerialNVRAM_1_I2C_FM24V10_SLAVE_ID == (SerialNVRAM_1_I2C_FM24V10_SLAVE_ID & nvramId))
        {
            status = SerialNVRAM_1_I2cUniqueSleep(nvramId);
        }
        else
        {
            status = SerialNVRAM_1_I2cNvCommand(nvramId, SerialNVRAM_1_NVRAM_SLEEP_CMD);
        }  
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_NvCommand
****************************************************************************//**
*
* Sends the NVRAM command. This is supported by nvSRAM only. 
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*  \param nvcmd: The 8-bit NVRAM command.
*
* \return 
* Error status
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_NvCommand(uint8 nvramId, uint8 nvcmd)
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_SpiNvCommand(nvramId, (uint32)nvcmd);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_I2cNvCommand(nvramId, (uint32)nvcmd);
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_SerialNoWrite
****************************************************************************//**
*
* Writes the NVRAM Serial number. 
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*
*  \note This function is applicable for devices with a serial number in the 
*  Control registers map. 
*  The SerialNVRAM_1_RtcRegWrite()/SerialNVRAM_1_WriteProcessorCompanion() 
*  functions are used for devices with a serial number in the RTC / processor 
*  companion register map. For more detail, refer to the device datasheet.
*
*  \param *dataPtr: The pointer to an array of the serial number
*  data to be written.
*
* \return
* Error status
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_SerialNoWrite(uint8 nvramId, const uint8 *dataPtr)
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    CYASSERT(dataPtr); /* dataPtr cannot be NULL */

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_SpiSerialNoWrite(nvramId, dataPtr);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_I2cSerialNoWrite(nvramId, dataPtr);
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_SerialNoRead
****************************************************************************//**
*
* Reads the NVRAM Serial number.
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*  The nvramId parameter for the FM24VN10 families has the following
*  I2C slave address  format: 0 1 0 1 0 A2 A1 A16. 
*  Bits A2 and A1 are the slave address inputs. 
*  Bit A16 is the page select bit and it can have any value for this function. 
*  Four FM24VN10 devices can be connected to I2C bus with the following
*  nvramId parameter values:
*  * 0x50 - Both A2 and A1 pins are connected to the ground.
*  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
*  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
*  * 0x56 – Both A2 and A1 pins are connected to the high level.
*
*  \note This function is not applicable for devices with a serial number in 
*  RTC / processor companion register map.
*  The SerialNVRAM_1_RtcRegRead()/SerialNVRAM_1_ReadProcessorCompanion() 
*  functions are used for devices with a serial number in the RTC / processor 
*  companion register map. For more detail, refer to the device datasheet.
*
*  \param *dataPtr: The pointer to an array for storing serial number data.
*
* \return 
* Error status
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_SerialNoRead(uint8 nvramId, uint8 *dataPtr)
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    CYASSERT(dataPtr); /* dataPtr cannot be NULL */

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_SpiSerialNoRead(nvramId, dataPtr);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        /* Check if the device is FM24V10 */
        if (SerialNVRAM_1_I2C_FM24V10_SLAVE_ID == (SerialNVRAM_1_I2C_FM24V10_SLAVE_ID & nvramId))
        {
            status = SerialNVRAM_1_I2cUniqueSerialNoRead(nvramId, dataPtr);
        }
        else
        {
            status = SerialNVRAM_1_I2cSerialNoRead(nvramId, dataPtr);  
        }
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_DevIdRead
****************************************************************************//**
*
* Reads the NVRAM device ID. This is supported by nvSRAM and F-RAM above 128Kbit.
* A pre-defined ID length covers the following varying device's IDs across
* different product families: 
*  * CY14B101PA - The DevID size is 4 bytes
*  * FM25VN10   - The DevID size is 9 bytes
*  * CY15B104Q  - The DevID size is 9 bytes
*  * CY14B101I  - The DevID size is 4 bytes
*  * FM24VN10   - The DevID size is 3 bytes
*  * FM31L278   - The DevID size is 8 bytes
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*  The nvramId parameter for the FM24VN10 families has the I2C slave address  
*  following format: 0 1 0 1 0 A2 A1 A16. 
*  Bits A2 and A1 are the slave address inputs. 
*  Bit A16 is the page select bit and it can have any value for this function. 
*  Four FM24VN10 devices can be connected to I2C bus with the following
*  nvramId parameter values:
*  * 0x50 - Both A2 and A1 pins are connected to the ground.
*  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
*  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
*  * 0x56 – Both A2 and A1 pins are connected to the high level.

*  \param *dataPtr: The pointer to an array for storing the device ID.
*  \param IDLength: The four predefines for the ID length (3ByteDeviceID, 
*         4ByteDeviceID, 8ByteDeviceID, 9ByteDeviceID).
*
* \return 
* Error status
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_DevIdRead(uint8 nvramId, uint8 *dataPtr, uint8 iDLength)
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    CYASSERT(dataPtr); /* dataPtr cannot be NULL */

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_SpiDevIdRead(nvramId, dataPtr, (uint32)iDLength);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        /* Check if the device is FM24V10 */
        if (SerialNVRAM_1_I2C_FM24V10_SLAVE_ID == (SerialNVRAM_1_I2C_FM24V10_SLAVE_ID & nvramId))
        {
            status = SerialNVRAM_1_I2cUniqueDevIdRead(nvramId, dataPtr, (uint32)iDLength);
        }
        else
        {
            status = SerialNVRAM_1_I2cDevIdRead(nvramId, dataPtr, (uint32)iDLength); 
        }
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_RtcRegWrite
****************************************************************************//**
*
* Writes the totalDataCount number of data into NVRAM RTC / F-RAM 
* Processor Companion registers. 
*
*  \note To write the RTC register, this function 
*  should set the W bit of the Flags register
*  (SerialNVRAM_1_RTC_FLAGS) and then write the RTC register.
*
*  \param nvramId: CS for SPI, the slave address for I2C.
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*  \param addr: The 8-bit NVRAM RTC / F-RAM Proc companion register
*   address for Write.
*  \param *dataWritePtr: The pointer to an array of RTC data bytes to be written.
*  \param totalDataCount: The number of RTC data bytes to be written.
*
* \return 
* Error status
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_RtcRegWrite(uint8 nvramId, 
                                                     uint32 addr, 
                                                     const uint8 *dataWritePtr, 
                                                     uint32 totalDataCount)
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    CYASSERT(dataWritePtr); /* dataWritePtr cannot be NULL */

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_SpiRtcRegWrite(nvramId, 
                                                 addr, 
                                                 dataWritePtr, 
                                                 totalDataCount);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_I2cRtcRegWrite(nvramId, 
                                                 addr, 
                                                 dataWritePtr, 
                                                 totalDataCount);
    #endif

    return status;
}


/*******************************************************************************
* Function Name:   SerialNVRAM_1_RtcRegRead
****************************************************************************//**
*
* Reads the totalDataCount number of data from nvSRAM RTC / F-RAM Processor 
* Companion registers. 
*
*  \note To read the data from the RTC register of the companion device, 
*  this function should set the R bit of the Flags register
*  (SerialNVRAM_1_RTC_FLAGS) and then read the RTC register.
*
*  \param nvramId: CS for SPI, the slave address for I2C
*  For I2C devices see the detailed format in
*  SerialNVRAM_1_GetStatus() description.
*  \param addr: The 8-bit nvSRAM RTC / F-RAM Proc companion
*  register address for read.
*  \param *dataReadPtr: The pointer to an array for storing RTC data bytes.
*  \param totalDataCount: The number of RTC data bytes to be read.
*
* \return 
* Error status
*  * SerialNVRAM_1_SUCCESS - No errors.
*  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
*  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
*     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
*
*******************************************************************************/
SerialNVRAM_1_status SerialNVRAM_1_RtcRegRead(uint8 nvramId, 
                                    uint32 addr, 
                                    uint8 *dataReadPtr, 
                                    uint32 totalDataCount)
{
    SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

    CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */

    #if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_SpiRtcRegRead(nvramId, 
                                                addr, 
                                                dataReadPtr, 
                                                totalDataCount);
    #endif
    #if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
        status = SerialNVRAM_1_I2cRtcRegRead(nvramId, 
                                                addr, 
                                                dataReadPtr, 
                                                totalDataCount);
    #endif

    return status;
}


#if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_CurrentRtcRegRead
    ****************************************************************************//**
    *
    * Reads the current totalDataCount number of data from nvSRAM RTC / F-RAM 
    * Processor Companion registers. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param *dataReadPtr: The pointer to an array for storing RTC data bytes. 
    *  \param totalDataCount: The number of RTC data bytes to be read.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    SerialNVRAM_1_status SerialNVRAM_1_CurrentRtcRegRead(uint8 nvramId, 
                                                               uint8 *dataReadPtr, 
                                                               uint32 totalDataCount)
    {       
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;
 
        CYASSERT(dataReadPtr); /* dataReadPtr cannot be NULL */
 
        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK;

        /* Set the RTC Registers selection mask */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_RTCR_MASK;    

        /* Send the Start condition and slave ID for Read */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_READ_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);

         /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of the totalDataCount bytes */
            i2cStatus = SerialNVRAM_1_I2cDataRead(dataReadPtr, totalDataCount);
        }
       
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);

        return status;
    }
#endif


#if (1 == SerialNVRAM_1_ENABLE_WRITE_PROTECTION)
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SetWp
    ****************************************************************************//**
    *
    * Sets the WP pin to HIGH or LOW.
    *
    *  \param value:  HIGH (1), LOW (0). 
    *
    *  \note
    *  The Active LOW level for SPI NVRAM and Active HIGH level for I2C NVRAM
    *  prevent write operation to the memory and the Status register. Refer to 
    *  the device datasheet for the choices about the software and hardware write 
    *  protection.    
    *******************************************************************************/
    void SerialNVRAM_1_SetWp(uint8 value)
    {
        SerialNVRAM_1_WP_Write(value);
    }
#endif


#if ((SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE) &&\
    (1 == SerialNVRAM_1_ENABLE_HOLD))
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SetHold
    ****************************************************************************//**
    *
    * Sets the HOLD pin to HIGH or LOW.
    *
    *  \param value:  SerialNVRAM_1_HIGH (1), SerialNVRAM_1_LOW (0). 
    *
    *******************************************************************************/
    void SerialNVRAM_1_SetHold(uint8 value)
    {
        SerialNVRAM_1_HOLD_Write(value);
    }
#endif


#if (SerialNVRAM_1_INTERFACE_SPI_SCB == SerialNVRAM_1_INTERFACE)
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiSelectDevice
    ****************************************************************************//**
    *
    * Sets the CS pin to the low state for a device with an SPI interface.
    *
    *  \param nvramId: CS for SPI
    * * SerialNVRAM_1_CS0 - The SPI device connected to the CS_0 pin.
    * * SerialNVRAM_1_CS1 - The SPI device connected to the CS_1 pin.
    * * SerialNVRAM_1_CS2 - The SPI device connected to the CS_2 pin.
    * * SerialNVRAM_1_CS3 - The SPI device connected to the CS_3 pin.
    *
    * \return
    *  error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *
    *******************************************************************************/
    static SerialNVRAM_1_status SerialNVRAM_1_SpiSelectDevice(uint8 nvramId)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        switch(nvramId)
        {
            case SerialNVRAM_1_CS0:
            {
                SerialNVRAM_1_CS_0_ON;
                break;
            }
            case SerialNVRAM_1_CS1:
            {
                #if (SerialNVRAM_1_CS1 < SerialNVRAM_1_SPI_CHIP_SELECT)
                    SerialNVRAM_1_CS_1_ON;
                #else
                    status = SerialNVRAM_1_DEVICE_ERROR;
                #endif
                break;
            }
            case SerialNVRAM_1_CS2:
            {
                #if (SerialNVRAM_1_CS2 < SerialNVRAM_1_SPI_CHIP_SELECT)
                    SerialNVRAM_1_CS_2_ON;
                #else
                    status = SerialNVRAM_1_DEVICE_ERROR;
                #endif
                break;
            }
            case SerialNVRAM_1_CS3:
            {
                #if (SerialNVRAM_1_CS3 < SerialNVRAM_1_SPI_CHIP_SELECT)
                    SerialNVRAM_1_CS_3_ON;
                #else
                    status = SerialNVRAM_1_DEVICE_ERROR;
                #endif
                break;
            }
            default:
            {
                status = SerialNVRAM_1_DEVICE_ERROR;
                break;
            }
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiDeSelectDevice
    ****************************************************************************//**
    *
    * Sets the CS pin to the high state for a device with an SPI interface.
    *
    *  \param nvramId: CS for SPI
    * * SerialNVRAM_1_CS0 - The SPI device connected to the CS_0 pin.
    * * SerialNVRAM_1_CS1 - The SPI device connected to the CS_1 pin.
    * * SerialNVRAM_1_CS2 - The SPI device connected to the CS_2 pin.
    * * SerialNVRAM_1_CS3 - The SPI device connected to the CS_3 pin.
    *
    * \return
    *  error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *
    *******************************************************************************/
    static SerialNVRAM_1_status SerialNVRAM_1_SpiDeSelectDevice(uint8 nvramId)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        switch(nvramId)
        {
            case SerialNVRAM_1_CS0:
            {
                SerialNVRAM_1_CS_0_OFF;
                break;
            }
            case SerialNVRAM_1_CS1:
            {
                #if (SerialNVRAM_1_CS1 < SerialNVRAM_1_SPI_CHIP_SELECT)
                    SerialNVRAM_1_CS_1_OFF;
                #else
                    status = SerialNVRAM_1_DEVICE_ERROR;
                #endif
                break;
            }
            case SerialNVRAM_1_CS2:
            {
                #if (SerialNVRAM_1_CS2 < SerialNVRAM_1_SPI_CHIP_SELECT)
                    SerialNVRAM_1_CS_2_OFF;
                #else
                    status = SerialNVRAM_1_DEVICE_ERROR;
                #endif
                break;
            }
            case SerialNVRAM_1_CS3:
            {
                #if (SerialNVRAM_1_CS3 < SerialNVRAM_1_SPI_CHIP_SELECT)
                    SerialNVRAM_1_CS_3_OFF;
                #else
                    status = SerialNVRAM_1_DEVICE_ERROR;
                #endif
                break;
            }
            default:
            {
                status = SerialNVRAM_1_DEVICE_ERROR;
                break;
            }
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiTxBusyCheck
    ****************************************************************************//**
    *
    * Waits until the SPI bus is busy.
    *
    * \return
    * Error status
    *  * SerialNVRAM_1_SUCCESS - The TX transmission is complete.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
    *     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    static SerialNVRAM_1_status SerialNVRAM_1_SpiTxBusyCheck(void)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;
        uint32 timeout;

        /* Initialize a timeout */
        timeout = 0u;
        
        /* Wait for the transmission to complete */
        while ((0u != _SpiIsBusBusy()) || 
               (_INTR_MASTER_SPI_DONE != _GetMasterInterruptSource()))
        {
            /* Check for a communication timeout */
            if(SerialNVRAM_1_SPI_COM_TIMEOUT < timeout)
            {
                /* An error in the SPI communication */
                status = SerialNVRAM_1_TIMEOUT_ERROR;
                
                break;
            }
            timeout++;
        }
        
        _ClearMasterInterruptSource(_INTR_MASTER_SPI_DONE);
        
        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiRxBufferCheck
    ****************************************************************************//**
    *
    * Waits until the Rx buffer is empty.
    *
    * \return
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does
    *    not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    static SerialNVRAM_1_status SerialNVRAM_1_SpiRxBufferCheck(void)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;
        uint32 timeout;

        /* Initialize a timeout */
        timeout = 0u;
        
        /* Ensure data is received in the receive buffer */
        while(0U == _SpiUartGetRxBufferSize())
        {
            /* Check for a communication timeout */
            if(SerialNVRAM_1_SPI_COM_TIMEOUT < timeout)
            {
                /* An error in the SPI communication */
                status = SerialNVRAM_1_TIMEOUT_ERROR;
                
                break;
            }
            timeout++;
        }  
        
        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiSetWriteEnable
    ****************************************************************************//**
    *
    * Sends the WREN command.
    *
    *  \param nvramId: CS for SPI.
    *
    * \return
    * Error status   
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    static SerialNVRAM_1_status SerialNVRAM_1_SpiSetWriteEnable(uint8 nvramId) 
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Select the F-RAM device */
        status = SerialNVRAM_1_SpiSelectDevice(nvramId);
        
        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Send the WREN command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_WREN);
            
            /* Wait for the transmission to complete */
            status = SerialNVRAM_1_SpiTxBusyCheck();
            
            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
            
            /* Wait for 1 us to form enough of pulse duration */
            CyDelayUs(1u);
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiBufferWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM.
    *
    *  \param *dataWritePtr: The pointer to an array of data bytes to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return
    * Error status   
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    static SerialNVRAM_1_status SerialNVRAM_1_SpiBufferWrite(const uint8 dataWritePtr[], 
                                                                   uint32 totalDataCount) 
    {
        uint32 i;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;
        uint32 data;

        /* Wait for the transmission to complete */
        status = SerialNVRAM_1_SpiTxBusyCheck();
        
        if (SerialNVRAM_1_SUCCESS == status)
        {
            for (i = 0u; (i < totalDataCount); i++ )
            {
                /* Get the next byte from the array of data */
                data = (uint32)dataWritePtr[i];

                /* Send the data byte */
                _SpiUartWriteTxData(data);
                
                /* Wait for the transmission to complete */
                status = SerialNVRAM_1_SpiTxBusyCheck();
            }
        }

        return status;
    }
    

    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiBufferRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from the SPI Buffer. 
    *
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiBufferRead(uint8 dataReadPtr[], 
                                                                            uint32 totalDataCount)
    {
        uint32 i;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;
        uint32 data;

        /* Wait for the transmission to complete */
        status = SerialNVRAM_1_SpiTxBusyCheck();
        
        if (SerialNVRAM_1_SUCCESS == status)
        {
            /*  Read the data bytes from NVRAM */
            for (i = 0u; (i < totalDataCount); i++)
            {
                /* Clear the receive buffer */
                _SpiUartClearRxBuffer();

                /* Send the dummy byte to receive data */
                _SpiUartWriteTxData(0x00U);
                
                /* Wait for the transmission to complete */
                status = SerialNVRAM_1_SpiTxBusyCheck();
                
                if (SerialNVRAM_1_SUCCESS == status)
                {
                    /* Ensure data is received in the receive buffer */
                    status = SerialNVRAM_1_SpiRxBufferCheck();
                    
                    /* Read the data byte and store it in the read buffer  */
                    data = _SpiUartReadRxData();
                    dataReadPtr[i] = (uint8)data;
                }
            }
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiMemoryWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM.
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataWritePtr: The pointer to an array of data bytes to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return
    *  Error status   
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiMemoryWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount) 
    {
        SerialNVRAM_1_status status;

        /* Send the WREN command */
        status = SerialNVRAM_1_SpiSetWriteEnable(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)SerialNVRAM_1_SpiSelectDevice(nvramId);

            /* Send the F-RAM Write command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_SRAM_WRITE_CMD);   
            
            /* For densities greater than or equal to 1MBit, send a 3-byte address */
            #if (SerialNVRAM_1_DENSITY_1_MBIT <= SerialNVRAM_1_DENSITY)
                _SpiUartWriteTxData((addr & SerialNVRAM_1_MSB_ADDR_MASK)>>SerialNVRAM_1_MSB_ADDR_SHIFTBITS);
            #endif
        
            /* Send a 2-byte address */
            _SpiUartWriteTxData((addr & SerialNVRAM_1_ISB_ADDR_MASK)>>SerialNVRAM_1_ISB_ADDR_SHIFTBITS);
            _SpiUartWriteTxData(addr);

            /* Send the data bytes */
            status = SerialNVRAM_1_SpiBufferWrite(dataWritePtr, totalDataCount);

            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiMemoryRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from NVRAM. 
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiMemoryRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Select the F-RAM device */
        status = SerialNVRAM_1_SpiSelectDevice(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Send F-RAM Read command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_SRAM_READ_CMD);   
            
            /* For densities greater than or equal to 1MBit, send a 3-byte address */
            #if (SerialNVRAM_1_DENSITY_1_MBIT <= SerialNVRAM_1_DENSITY)
                _SpiUartWriteTxData((addr & SerialNVRAM_1_MSB_ADDR_MASK)>>SerialNVRAM_1_MSB_ADDR_SHIFTBITS);
            #endif
        
            /* Send a 2-byte address */
            _SpiUartWriteTxData((addr & SerialNVRAM_1_ISB_ADDR_MASK)>>SerialNVRAM_1_ISB_ADDR_SHIFTBITS);
            _SpiUartWriteTxData(addr);

            /* Read the data bytes */
            status = SerialNVRAM_1_SpiBufferRead(dataReadPtr, totalDataCount);

            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiRtcRegWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM RTC / F-RAM 
    * Processor Companion registers. 
    *
    *  \param nvramId: CS for SPIю
    *  \param addr: The 8-bit NVRAM RTC / F-RAM Proc companion
    *  register address for Write.
    *  \param *dataWritePtr: The pointer to an array of RTC data bytes to be written.
    *  \param totalDataCount: The number of RTC data bytes to be written.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiRtcRegWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount)
    {
        SerialNVRAM_1_status status;

        /* Send the WREN command */
        status = SerialNVRAM_1_SpiSetWriteEnable(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)SerialNVRAM_1_SpiSelectDevice(nvramId);

            /* Send the RTC Write command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_WRTC_CMD);   
                
            /* Send 1 address byte */
            _SpiUartWriteTxData(addr);

            /* Send the RTC data bytes */
            status = SerialNVRAM_1_SpiBufferWrite(dataWritePtr, totalDataCount);

            /* De-select the device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId); 
        }
        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiRtcRegRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from nvSRAM RTC / F-RAM Processor 
    * Companion registers. 
    *
    *  \param nvramId: CS for SPI.
    *  \param addr: The 8-bit nvSRAM RTC / F-RAM Proc companion
    *  register address for Read. 
    *  \param *dataReadPtr: The pointer to an array for storing RTC data bytes.
    *  \param totalDataCount: The number of RTC data bytes to be read.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiRtcRegRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Select the F-RAM device */
        status = SerialNVRAM_1_SpiSelectDevice(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Send the RTC Read command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_RDRTC_CMD);   
        
            /* Send 1 address byte */
            _SpiUartWriteTxData(addr);
        
            /* Read the RTC data bytes */
            status = SerialNVRAM_1_SpiBufferRead(dataReadPtr, totalDataCount);
            
            /* De-select the device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }


    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiNvCommand
    ****************************************************************************//**
    *
    * Sends the NVRAM command. This is supported by nvSRAM only. 
    *
    *  \param nvramId: CS for SPI.
    *  \param nvcmd: The 8-bit NVRAM command.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiNvCommand(uint8 nvramId, 
                                                                           uint32 nvcmd)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Send the WREN command */
        status = SerialNVRAM_1_SpiSetWriteEnable(nvramId);
        
        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)SerialNVRAM_1_SpiSelectDevice(nvramId);
            
            /* Send the nvcmd command */
            _SpiUartWriteTxData(nvcmd);
            
            /* Wait for the transmission to complete */
            status = SerialNVRAM_1_SpiTxBusyCheck();
            
            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiSerialNoWrite
    ****************************************************************************//**
    *
    * Writes the NVRAM Serial number.
    *
    *  \note  The processor companion devices, such as FM33256BG, 
    *  do not support this function. They have the Serial number storage 
    *  is in the RTC/companion space. 
    *  The SerialNVRAM_1_WriteProcessorCompanion() / 
    * SerialNVRAM_1_ReadProcessorCompanion()  functions are used to 
    *  write / read the serial number. Refer to the device datasheet for details. 
    *
    *  \param nvramId: CS for SPI.
    *  \param *dataPtr: The pointer to an array of serial number data to be written.
    *
    * \return
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiSerialNoWrite(uint8 nvramId, 
                                                                               const uint8 *dataPtr)
    {
        SerialNVRAM_1_status status;

        /* Send the WREN command */
        status = SerialNVRAM_1_SpiSetWriteEnable(nvramId);
        
        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Select the F-RAM device */
            (void)SerialNVRAM_1_SpiSelectDevice(nvramId);

            /* Send the Serial number Write command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_WRSN_CMD);
            
            /* Send the serial number */
            status = SerialNVRAM_1_SpiBufferWrite(dataPtr, SerialNVRAM_1_SERIAL_NUM_LENGTH);

            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiSerialNoRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Serial number.
    *
    *  \note  The processor companion devices, such as FM33256BG, 
    *  do not support this function. They have the Serial number storage 
    *  is in the RTC/companion space. 
    *  The SerialNVRAM_1_WriteProcessorCompanion() / 
    * SerialNVRAM_1_ReadProcessorCompanion()  functions are used to 
    *  write / read the serial number. Refer to the device datasheet for details.
    *
    *  \param nvramId: CS for SPI.
    *  \param *dataPtr: The pointer to an array for storing the serial number data.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiSerialNoRead(uint8 nvramId, 
                                                                              uint8 *dataPtr)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Clear the receive buffer */
        _SpiUartClearRxBuffer();

        /* Select the F-RAM device */
        status = SerialNVRAM_1_SpiSelectDevice(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {  
            /* Send the serial number Read command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_RDSN_CMD);

            /* Read the serial number data */
            status = SerialNVRAM_1_SpiBufferRead(dataPtr, SerialNVRAM_1_SERIAL_NUM_LENGTH);

            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }

    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_SpiDevIdRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Device ID. This is supported by nvSRAM and F-RAM above 128Kbit.
    * A pre-defined ID length covers the following varying device's IDs across
    * different product families: 
    *  * CY14B101PA - The DevID size is 4 bytes.
    *  * FM25VN10   - The DevID size is 9 bytes.
    *  * CY15B104Q  - The DevID size is 9 bytes.
    *  * CY14B101I  - The DevID size is 4 bytes.
    *  * FM24VN10   - The DevID size is 3 bytes.
    *  * FM31L278   - The DevID size is 8 bytes.
    *
    *  \param nvramId: CS for SPI.
    *  \param *dataPtr: The pointer to an array for storing a device ID.
    *  \param iDLength: The four predefines for the ID length:
    *         SerialNVRAM_1_3_BYTE_DEVICE_ID, 
    *         SerialNVRAM_1_4_BYTE_DEVICE_ID,
    *         SerialNVRAM_1_8_BYTE_DEVICE_ID, 
    *         SerialNVRAM_1_9_BYTE_DEVICE_ID.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does 
    *     not respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_SpiDevIdRead(uint8 nvramId,
                                                                           uint8 *dataPtr,
                                                                           uint32 iDLength)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Clear the receive buffer */
        _SpiUartClearRxBuffer();

        /* Select the F-RAM device */
        status = SerialNVRAM_1_SpiSelectDevice(nvramId);

        if (SerialNVRAM_1_SUCCESS == status)
        {
            /* Send the status register Read command */
            _SpiUartWriteTxData(SerialNVRAM_1_NVRAM_RDID_CMD);

            /* Read device ID data */
            status = SerialNVRAM_1_SpiBufferRead(dataPtr, iDLength);
            
            /* De-select the F-RAM device  */
            (void)SerialNVRAM_1_SpiDeSelectDevice(nvramId);
        }

        return status;
    }
#endif


#if (SerialNVRAM_1_INTERFACE_I2C_SCB == SerialNVRAM_1_INTERFACE)
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cDataWrite
    ****************************************************************************//**
    *
    * Sends the totalDataCount number of data.
    *
    *  \param *dataWritePtr: The pointer to an array of data bytes to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return 
    * error status
    * *  See SerialNVRAM_1_I2cDataRead() function for constants.
    *
    *******************************************************************************/
    static uint32 SerialNVRAM_1_I2cDataWrite(const uint8 dataWritePtr[], uint32 totalDataCount)
    {
        uint32 i;
        uint32 i2cStatus = _I2C_MSTR_NO_ERROR;
        uint32 data;

        /* Send data bytes for Write */
        for (i = 0u; (i < totalDataCount); i++ )
        {
            /* Get the next byte from the array of data */
            data = (uint32)dataWritePtr[i];
            
            /* Send the data byte */
            i2cStatus = _I2CMasterWriteByte(data, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
                       
            if (_I2C_MSTR_NO_ERROR != i2cStatus)
            {
                /* An I2C error */
                break;
            }
        }

        return i2cStatus;
    }

    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cDataRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from the I2C bus. 
    *
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of data bytes to be read.
    *
    * \return 
    * error status
    *  * _I2C_MSTR_NO_ERROR - No errors.
    *  * _I2C_MSTR_BUS_BUSY - Bus is busy.
    *  Nothing was sent on the bus.
    *  * _I2C_MSTR_NOT_READY - Master is not ready
    *  for to start transfer.
    *  * _I2C_MSTR_ERR_LB_NAK - Last byte was NAKed.
    *  * _I2C_MSTR_ERR_ARB_LOST - Master lost arbitration.
    *  * _I2C_MSTR_ERR_BUS_ERR - Master encountered a bus error.
    *  * _I2C_MSTR_ERR_ABORT_START - The start condition
    *     generation  was aborted due to beginning of Slave operation.
    *  * _I2C_MSTR_ERR_TIMEOUT - The function is timed out.
    *
    *******************************************************************************/
    static uint32 SerialNVRAM_1_I2cDataRead(uint8 dataReadPtr[], uint32 totalDataCount)
    {
        uint32 i;
        uint32 i2cStatus = _I2C_MSTR_NO_ERROR;
        uint8 i2cData;
        
        /* Read array of the totalDataCount bytes with ASK data */
        for (i = 0u; (i < (totalDataCount - 1u)); i++)
        {
            i2cStatus = _I2CMasterReadByte(_I2C_ACK_DATA, 
                                                             &i2cData, 
                                                             SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
            dataReadPtr[i] = i2cData;
        }
        
        /* Read the last byte with NAK data */
        i2cStatus = _I2CMasterReadByte(_I2C_NAK_DATA, 
                                                         &i2cData, 
                                                         SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        dataReadPtr[totalDataCount - 1u] = i2cData;

        return i2cStatus;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2CSendStop
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM.
    *
    *  \param i2cStatus: The status of the I2C communication.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_BUSY - The I2C bus or the NVRAM device is busy.
    *  * SerialNVRAM_1_DEVICE_ERROR - The NVRAM device is busy or
    *   wrong last address.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    static SerialNVRAM_1_status SerialNVRAM_1_I2CSendStop(uint32 i2cStatus)
    {
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Check for errors */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* No errors. Send Stop */
            i2cStatus = _I2CMasterSendStop(SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }
        else if ((_I2C_MSTR_BUS_BUSY == i2cStatus) ||
                (_I2C_MSTR_NOT_READY == i2cStatus))
        {
            /* The I2C bus is busy */
            status = SerialNVRAM_1_DEVICE_BUSY;
        }
        else if (_I2C_MSTR_ERR_LB_NAK == i2cStatus)     
        {
            /* The NVRAM device is busy or wrong last address */
            status = SerialNVRAM_1_DEVICE_ERROR;
            i2cStatus = _I2CMasterSendStop(SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }
        else
        {
            /* Other communications error */
            status = SerialNVRAM_1_COMMUNICATION_ERROR;
            i2cStatus = _I2CMasterSendStop(SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        return status;
    }
    

    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cMemoryWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM.
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataWritePtr: The pointer to an array of data bytes to be written.
    *  \param totalDataCount: The number of data bytes to be written.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_BUSY - The I2C bus or the NVRAM device is busy.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cMemoryWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount) 
    {
        uint32 i2cStatus;

        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
        
        /* Set the I2C Memory selection mask */
        nvramId |= SerialNVRAM_1_NVRAM_SEL_MEM_MASK;
        
        /* For densities > 1-Mbit, add the MSB bit in in the slave ID (bit0) */
        #if (SerialNVRAM_1_DENSITY_1_MBIT <= SerialNVRAM_1_DENSITY)
            nvramId |= (uint8)(((addr & SerialNVRAM_1_MSBIT_MASK)>>SerialNVRAM_1_MSB_ADDR_SHIFTBITS) &
                              SerialNVRAM_1_LSBIT_MASK);
        #endif

        /* Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ISB address byte */
            i2cStatus = _I2CMasterWriteByte(((addr & SerialNVRAM_1_ISB_ADDR_MASK)
                                                               >>SerialNVRAM_1_ISB_ADDR_SHIFTBITS), 
                                                             SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = _I2CMasterWriteByte(addr, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }
        
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send data bytes for Write */
            i2cStatus = SerialNVRAM_1_I2cDataWrite(dataWritePtr, totalDataCount);
        }
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cMemoryRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from NVRAM. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param addr: The 1/2/3-byte NVRAM address for Write.
    *  \param *dataReadPtr: The pointer to an array for storing data bytes.
    *  \param totalDataCount: The number of the data bytes to be read.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cMemoryRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;
    
        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
        
        /* Set the I2C Memory selection mask */
        nvramId |= SerialNVRAM_1_NVRAM_SEL_MEM_MASK;
    
        /* For densities > 1-Mbit, add the MSB bit in the slave ID (bit0) */
        #if (SerialNVRAM_1_DENSITY_1_MBIT <= SerialNVRAM_1_DENSITY)
            nvramId |= (uint8)(((addr & SerialNVRAM_1_MSBIT_MASK)>>SerialNVRAM_1_MSB_ADDR_SHIFTBITS) &
                              SerialNVRAM_1_LSBIT_MASK);
        #endif

        /* Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        /* Write the SRAM address to the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ISB address byte */
            i2cStatus = _I2CMasterWriteByte(((addr & SerialNVRAM_1_ISB_ADDR_MASK)
                                                              >>SerialNVRAM_1_ISB_ADDR_SHIFTBITS), 
                                                             SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = _I2CMasterWriteByte(addr, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = _I2CMasterSendRestart((uint32)nvramId, 
                                                                _I2C_READ_XFER_MODE, 
                                                                SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of totalDataCount bytes */
            i2cStatus = SerialNVRAM_1_I2cDataRead(dataReadPtr, totalDataCount);
        }
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);

        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cRtcRegWrite
    ****************************************************************************//**
    *
    * Writes the totalDataCount number of data into NVRAM RTC / F-RAM 
    * Processor Companion registers. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param addr: The 8-bit NVRAM RTC/F-RAM Proc companion
    *   register address for Write.
    *  \param *dataWritePtr: The pointer to an array of the RTC
    *  data bytes to be written.
    *  \param totalDataCount: The number of the RTC data bytes to be written.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cRtcRegWrite(uint8 nvramId, 
                                                                             uint32 addr, 
                                                                             const uint8 *dataWritePtr, 
                                                                             uint32 totalDataCount)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status  status = SerialNVRAM_1_SUCCESS;
        
        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
       
        /* Set RTC Registers selection mask */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_RTCR_MASK;

        /*  Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the register address byte */
            i2cStatus = _I2CMasterWriteByte(addr, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
            if (_I2C_MSTR_NO_ERROR == i2cStatus)
            {
                /* Send the data bytes for Write */
                i2cStatus = SerialNVRAM_1_I2cDataWrite(dataWritePtr, totalDataCount);
            }
        }

        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);     

        return status;
    }


    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cRtcRegRead
    ****************************************************************************//**
    *
    * Reads the totalDataCount number of data from nvSRAM RTC/F-RAM Processor 
    * Companion registers. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param addr: The 8-bit nvSRAM RTC/F-RAM Proc companion register address for Read.
    *  \param *dataReadPtr: The pointer to an array for storing the RTC data bytes.
    *  \param totalDataCount: The number of the RTC data bytes to be read.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cRtcRegRead(uint8 nvramId, 
                                                                            uint32 addr, 
                                                                            uint8 *dataReadPtr, 
                                                                            uint32 totalDataCount)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
       
        /* Set RTC Registers selection mask */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_RTCR_MASK;

        /* Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        /* Write the SRAM address to the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the RTC register address byte */
            i2cStatus = _I2CMasterWriteByte(addr, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }
        
        /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = _I2CMasterSendRestart((uint32)nvramId, 
                                                                _I2C_READ_XFER_MODE, 
                                                                SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of the totalDataCount bytes */
            i2cStatus = SerialNVRAM_1_I2cDataRead(dataReadPtr, totalDataCount);
        }
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);
        
        return status;
    }


    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cNvCommand
    ****************************************************************************//**
    *
    * Sends the NVRAM command. This is supported by nvSRAM only. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param nvcmd: The 8-bit NVRAM command.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cNvCommand(uint8 nvramId, 
                                                                           uint32 nvcmd)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
       
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_CR_MASK;

        /*  Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the Command Register address */
            i2cStatus = _I2CMasterWriteByte(SerialNVRAM_1_COMMAND_REG_ADDR, 
                                                              SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
            if (_I2C_MSTR_NO_ERROR == i2cStatus)
            {
               /* Send the data byte for Write */
               i2cStatus = _I2CMasterWriteByte(nvcmd, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
            }
        }

        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);

        return status;
    }
   
   
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cSerialNoWrite
    ****************************************************************************//**
    *
    * Writes the NVRAM Serial number. 
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param *dataPtr: The pointer to an array of serial number data to be written.
    *
    * \return
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cSerialNoWrite(uint8 nvramId,
                                                                               const uint8 *dataPtr)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status  status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
       
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_CR_MASK;

        /*  Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the Serial Number address byte */
            i2cStatus = _I2CMasterWriteByte(SerialNVRAM_1_SERIAL_NUM_REG_ADDR,
                                                              SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
            if (_I2C_MSTR_NO_ERROR == i2cStatus)
            {
                /* Send the data bytes for Write */
                i2cStatus = SerialNVRAM_1_I2cDataWrite(dataPtr, SerialNVRAM_1_SERIAL_NUM_LENGTH);
            }
        }

        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);  
        
        return status;
    }
   
        
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cSerialNoRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Serial number.
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param *dataPtr: The pointer to an array for storing the serial number data.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cSerialNoRead(uint8 nvramId,
                                                                              uint8 *dataPtr)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
       
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_CR_MASK;

        /* Send the Start condition and slave ID */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE,
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        /* Write the Serial Number address to the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = _I2CMasterWriteByte(SerialNVRAM_1_SERIAL_NUM_REG_ADDR,
                                                              SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }
        
        /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = _I2CMasterSendRestart((uint32)nvramId,
                                                                _I2C_READ_XFER_MODE,
                                                                SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of SerialNVRAM_1_SERIAL_NUM_LENGTH bytes */
            i2cStatus = SerialNVRAM_1_I2cDataRead(dataPtr, SerialNVRAM_1_SERIAL_NUM_LENGTH);
        }
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);
        
        return status;
    }  

    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cUniqueSleep
    ****************************************************************************//**
    *
    * Sends the NVRAM command for sleep for the I2C devices with
    *  the unique serial number. (Example, FM24V10).
    *
    *  \param nvramId: Еhe slave address for I2C
    *  The nvramId parameter for the FM24VN10 families has the following format: 
    *  0 1 0 1 0 A2 A1 A16. 
    *  Bits A2 and A1 are the slave address inputs. 
    *  Bit A16 is the page select bit and it can have any value for this function. 
    *  Four FM24VN10 devices can be connected to I2C bus with the following
    *  nvramId parameter values:
    *  * 0x50 - Both A2 and A1 pins are connected to the ground.
    *  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
    *  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
    *  * 0x56 – Both A2 and A1 pins are connected to the high level.
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_TIMEOUT_ERROR - The device does not 
    *     respond or SerialNVRAM_1_SPI_COM_TIMEOUT elapsed.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cUniqueSleep(uint8 nvramId)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = (nvramId & SerialNVRAM_1_I2C_RSVD_SLAVE_ADDR_MASK) << 1u; 
        
        /* Send the Start condition and Reserved Slave ID */
        i2cStatus = _I2CMasterSendStart(SerialNVRAM_1_RSVD_SLAVE_ID, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        /* Write the slave ID to the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the address byte */
            i2cStatus = _I2CMasterWriteByte((uint32)nvramId, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and Reserved Slave ID */
            (void)_I2CMasterSendRestart(SerialNVRAM_1_RSVD_SLAVE_SLEEP_ID, 
                                                                _I2C_WRITE_XFER_MODE, 
                                                                SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);
        
        return status;
    }

        
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cUniqueSerialNoRead
    ****************************************************************************//**
    *
    * Reads the NVRAM Serial number for the I2C devices with
    *  the unique serial number. (Example, FM24V10).
    *
    *  \param nvramId: The slave address for I2C.
    *  The nvramId parameter for the FM24VN10 families has the following format: 
    *  0 1 0 1 0 A2 A1 A16. 
    *  Bits A2 and A1 are the slave address inputs. 
    *  Bit A16 is the page select bit and it can have any value for this function. 
    *  Four FM24VN10 devices can be connected to I2C bus with the following
    *  nvramId parameter values:
    *  * 0x50 - Both A2 and A1 pins are connected to the ground.
    *  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
    *  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
    *  * 0x56 – Both A2 and A1 pins are connected to the high level.
    *  \param *dataPtr: The pointer to an array for storing the serial number data.
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cUniqueSerialNoRead(uint8 nvramId,
                                                                                    uint8 *dataPtr)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = (nvramId & SerialNVRAM_1_I2C_RSVD_SLAVE_ADDR_MASK) << 1u; 
        
        /* Send the Start condition and Reserved Slave ID */
        i2cStatus = _I2CMasterSendStart(SerialNVRAM_1_RSVD_SLAVE_ID, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        /* Write the slave ID to the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = _I2CMasterWriteByte((uint32)nvramId, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and Reserved Slave ID to read the serial number. */
            i2cStatus = _I2CMasterSendRestart(SerialNVRAM_1_RSVD_SLAVE_SERIAL_NUM_ID, 
                                                                _I2C_READ_XFER_MODE, 
                                                                SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of SerialNVRAM_1_SERIAL_NUM_LENGTH bytes */
            i2cStatus = SerialNVRAM_1_I2cDataRead(dataPtr, SerialNVRAM_1_SERIAL_NUM_LENGTH);
        }
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);
        
        return status;
    }
    
    
    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cUniqueDevIdRead
    ****************************************************************************//**
    *
    * Reads the NVRAM device ID for the devices with unique serial number
    * (for example, FM24VN10 device).
    * A pre-defined ID length covers the following varying device's IDs across
    * different product families: 
    *  * FM24VN10   - The DevID size is 3 bytes.
    *
    *  \param nvramId: The slave address for I2C.
    *  The nvramId parameter for the FM24VN10 families has the following format: 
    *  0 1 0 1 0 A2 A1 A16. 
    *  Bits A2 and A1 are the slave address inputs. 
    *  Bit A16 is the page select bit and it can have any value for this function. 
    *  Four FM24VN10 devices can be connected to I2C bus with the following
    *  nvramId parameter values:
    *  * 0x50 - Both A2 and A1 pins are connected to the ground.
    *  * 0x52 - Pin A2 connected to the ground and Pin A1 connected to the high level.
    *  * 0x54 - Pin A2 connected to the high level and Pin A1 connected to the ground.
    *  * 0x56 – Both A2 and A1 pins are connected to the high level.
    *  \param *dataPtr: The pointer to an array for storing the device ID.
    *  \param IDLength: The ID length (3ByteDeviceID for the FM24VN10 device).    
    *
    * \return 
    * Error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cUniqueDevIdRead(uint8 nvramId,
                                                                           uint8 *dataPtr,
                                                                           uint32 iDLength)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;

        /* Apply the mask to unused bits */
        nvramId = (nvramId & SerialNVRAM_1_I2C_RSVD_SLAVE_ADDR_MASK) << 1u; 
        
        /* Send the Start condition and Reserved Slave ID */
        i2cStatus = _I2CMasterSendStart(SerialNVRAM_1_RSVD_SLAVE_ID, 
                                                          _I2C_WRITE_XFER_MODE, 
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);

        /* Write the slave ID to the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = _I2CMasterWriteByte((uint32)nvramId, SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and Reserved Slave ID to read the device ID */
            i2cStatus = _I2CMasterSendRestart(SerialNVRAM_1_RSVD_SLAVE_DEV_ID, 
                                                                _I2C_READ_XFER_MODE, 
                                                                SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of SerialNVRAM_1_SERIAL_NUM_LENGTH bytes */
            i2cStatus = SerialNVRAM_1_I2cDataRead(dataPtr, iDLength);
        }

        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);

        return status;
    }

    /*******************************************************************************
    * Function Name:   SerialNVRAM_1_I2cDevIdRead
    ****************************************************************************//**
    *
    * Reads the NVRAM device ID. This is supported by nvSRAM and F-RAM above 128Kbit.
    * A pre-defined ID length covers the following varying device IDs across
    * different product families: 
    *  * CY14B101PA - The DevID size is 4 bytes.
    *  * FM25VN10   - The DevID size is 9 bytes.
    *  * CY15B104Q  - The DevID size is 9 bytes.
    *  * CY14B101I  - The DevID size is 4 bytes.
    *  * FM31L278   - The DevID size is 8 bytes.
    *
    *  \note This function is not applicable for the FM24VN10 devices. 
    *  The SerialNVRAM_1_UniqueDevIdRead() function is used
    *  FM24VN10 devices. For more detail, refer to the device datasheet.
    *
    *  \param nvramId: The slave address for I2C.
    *  For I2C devices see the detailed format in
    *  SerialNVRAM_1_GetStatus() description.
    *  \param *dataPtr: The pointer to an array for storing the device ID.
    *  \param iDLength: The four pre-defines for the ID length (3ByteDeviceID, 
    *         4ByteDeviceID, 8ByteDeviceID, 9ByteDeviceID).
    *
    * \return 
    * error status
    *  * SerialNVRAM_1_SUCCESS - No errors.
    *  * SerialNVRAM_1_DEVICE_ERROR - The wrong device or a device error.
    *  * SerialNVRAM_1_COMMUNICATION_ERROR - A communication error.
    *
    *******************************************************************************/
    CY_INLINE static SerialNVRAM_1_status SerialNVRAM_1_I2cDevIdRead(uint8 nvramId,
                                                                           uint8 *dataPtr,
                                                                           uint32 iDLength)
    {
        uint32 i2cStatus;
        SerialNVRAM_1_status status = SerialNVRAM_1_SUCCESS;
    
        /* Apply the mask to unused bits */
        nvramId = nvramId & SerialNVRAM_1_I2C_SLAVE_ADDR_MASK; 
       
        /* Set the Control Registers Slave Address */
        nvramId = nvramId | SerialNVRAM_1_NVRAM_SEL_CR_MASK;

        /* Send the Start condition and slave ID for Write */
        i2cStatus = _I2CMasterSendStart((uint32)nvramId, 
                                                          _I2C_WRITE_XFER_MODE,
                                                          SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        
        /* Write the Device ID address to the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the LSB address byte */
            i2cStatus = _I2CMasterWriteByte(SerialNVRAM_1_DEVICE_ID_REG_ADDR,
                                                              SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }
        
        /* Read data from the slave */
        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Send the ReStart condition and slave ID for Read */
            i2cStatus = _I2CMasterSendRestart((uint32)nvramId, 
                                                                _I2C_READ_XFER_MODE,
                                                                SerialNVRAM_1_I2C_COM_TIMEOUT_MS);
        }

        if (_I2C_MSTR_NO_ERROR == i2cStatus)
        {
            /* Read the array of iDLength bytes */
            i2cStatus = SerialNVRAM_1_I2cDataRead(dataPtr, iDLength);
        }
        
        /* Send Stop and get the error status */
        status = SerialNVRAM_1_I2CSendStop(i2cStatus);

        return status;
    }    
#endif


/* [] END OF FILE */
