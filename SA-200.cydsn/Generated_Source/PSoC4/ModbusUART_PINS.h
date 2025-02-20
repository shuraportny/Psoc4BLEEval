/***************************************************************************//**
* \file ModbusUART_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_ModbusUART_H)
#define CY_SCB_PINS_ModbusUART_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define ModbusUART_REMOVE_RX_WAKE_SDA_MOSI_PIN  (1u)
#define ModbusUART_REMOVE_RX_SDA_MOSI_PIN      (1u)
#define ModbusUART_REMOVE_TX_SCL_MISO_PIN      (1u)
#define ModbusUART_REMOVE_CTS_SCLK_PIN      (1u)
#define ModbusUART_REMOVE_RTS_SS0_PIN      (1u)
#define ModbusUART_REMOVE_SS1_PIN                 (1u)
#define ModbusUART_REMOVE_SS2_PIN                 (1u)
#define ModbusUART_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define ModbusUART_REMOVE_I2C_PINS                (1u)
#define ModbusUART_REMOVE_SPI_MASTER_PINS         (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define ModbusUART_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define ModbusUART_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define ModbusUART_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define ModbusUART_REMOVE_SPI_SLAVE_PINS          (1u)
#define ModbusUART_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define ModbusUART_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define ModbusUART_REMOVE_UART_TX_PIN             (0u)
#define ModbusUART_REMOVE_UART_RX_TX_PIN          (1u)
#define ModbusUART_REMOVE_UART_RX_PIN             (1u)
#define ModbusUART_REMOVE_UART_RX_WAKE_PIN        (0u)
#define ModbusUART_REMOVE_UART_RTS_PIN            (1u)
#define ModbusUART_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define ModbusUART_RX_WAKE_SDA_MOSI_PIN (0u == ModbusUART_REMOVE_RX_WAKE_SDA_MOSI_PIN)
#define ModbusUART_RX_SDA_MOSI_PIN     (0u == ModbusUART_REMOVE_RX_SDA_MOSI_PIN)
#define ModbusUART_TX_SCL_MISO_PIN     (0u == ModbusUART_REMOVE_TX_SCL_MISO_PIN)
#define ModbusUART_CTS_SCLK_PIN     (0u == ModbusUART_REMOVE_CTS_SCLK_PIN)
#define ModbusUART_RTS_SS0_PIN     (0u == ModbusUART_REMOVE_RTS_SS0_PIN)
#define ModbusUART_SS1_PIN                (0u == ModbusUART_REMOVE_SS1_PIN)
#define ModbusUART_SS2_PIN                (0u == ModbusUART_REMOVE_SS2_PIN)
#define ModbusUART_SS3_PIN                (0u == ModbusUART_REMOVE_SS3_PIN)

/* Mode defined pins */
#define ModbusUART_I2C_PINS               (0u == ModbusUART_REMOVE_I2C_PINS)
#define ModbusUART_SPI_MASTER_PINS        (0u == ModbusUART_REMOVE_SPI_MASTER_PINS)
#define ModbusUART_SPI_MASTER_SCLK_PIN    (0u == ModbusUART_REMOVE_SPI_MASTER_SCLK_PIN)
#define ModbusUART_SPI_MASTER_MOSI_PIN    (0u == ModbusUART_REMOVE_SPI_MASTER_MOSI_PIN)
#define ModbusUART_SPI_MASTER_MISO_PIN    (0u == ModbusUART_REMOVE_SPI_MASTER_MISO_PIN)
#define ModbusUART_SPI_MASTER_SS0_PIN     (0u == ModbusUART_REMOVE_SPI_MASTER_SS0_PIN)
#define ModbusUART_SPI_MASTER_SS1_PIN     (0u == ModbusUART_REMOVE_SPI_MASTER_SS1_PIN)
#define ModbusUART_SPI_MASTER_SS2_PIN     (0u == ModbusUART_REMOVE_SPI_MASTER_SS2_PIN)
#define ModbusUART_SPI_MASTER_SS3_PIN     (0u == ModbusUART_REMOVE_SPI_MASTER_SS3_PIN)
#define ModbusUART_SPI_SLAVE_PINS         (0u == ModbusUART_REMOVE_SPI_SLAVE_PINS)
#define ModbusUART_SPI_SLAVE_MOSI_PIN     (0u == ModbusUART_REMOVE_SPI_SLAVE_MOSI_PIN)
#define ModbusUART_SPI_SLAVE_MISO_PIN     (0u == ModbusUART_REMOVE_SPI_SLAVE_MISO_PIN)
#define ModbusUART_UART_TX_PIN            (0u == ModbusUART_REMOVE_UART_TX_PIN)
#define ModbusUART_UART_RX_TX_PIN         (0u == ModbusUART_REMOVE_UART_RX_TX_PIN)
#define ModbusUART_UART_RX_PIN            (0u == ModbusUART_REMOVE_UART_RX_PIN)
#define ModbusUART_UART_RX_WAKE_PIN       (0u == ModbusUART_REMOVE_UART_RX_WAKE_PIN)
#define ModbusUART_UART_RTS_PIN           (0u == ModbusUART_REMOVE_UART_RTS_PIN)
#define ModbusUART_UART_CTS_PIN           (0u == ModbusUART_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
    #include "ModbusUART_uart_rx_wake_i2c_sda_spi_mosi.h"
#endif /* (ModbusUART_RX_SDA_MOSI) */

#if (ModbusUART_RX_SDA_MOSI_PIN)
    #include "ModbusUART_uart_rx_i2c_sda_spi_mosi.h"
#endif /* (ModbusUART_RX_SDA_MOSI) */

#if (ModbusUART_TX_SCL_MISO_PIN)
    #include "ModbusUART_uart_tx_i2c_scl_spi_miso.h"
#endif /* (ModbusUART_TX_SCL_MISO) */

#if (ModbusUART_CTS_SCLK_PIN)
    #include "ModbusUART_uart_cts_spi_sclk.h"
#endif /* (ModbusUART_CTS_SCLK) */

#if (ModbusUART_RTS_SS0_PIN)
    #include "ModbusUART_uart_rts_spi_ss0.h"
#endif /* (ModbusUART_RTS_SS0_PIN) */

#if (ModbusUART_SS1_PIN)
    #include "ModbusUART_spi_ss1.h"
#endif /* (ModbusUART_SS1_PIN) */

#if (ModbusUART_SS2_PIN)
    #include "ModbusUART_spi_ss2.h"
#endif /* (ModbusUART_SS2_PIN) */

#if (ModbusUART_SS3_PIN)
    #include "ModbusUART_spi_ss3.h"
#endif /* (ModbusUART_SS3_PIN) */

#if (ModbusUART_I2C_PINS)
    #include "ModbusUART_scl.h"
    #include "ModbusUART_sda.h"
#endif /* (ModbusUART_I2C_PINS) */

#if (ModbusUART_SPI_MASTER_PINS)
#if (ModbusUART_SPI_MASTER_SCLK_PIN)
    #include "ModbusUART_sclk_m.h"
#endif /* (ModbusUART_SPI_MASTER_SCLK_PIN) */

#if (ModbusUART_SPI_MASTER_MOSI_PIN)
    #include "ModbusUART_mosi_m.h"
#endif /* (ModbusUART_SPI_MASTER_MOSI_PIN) */

#if (ModbusUART_SPI_MASTER_MISO_PIN)
    #include "ModbusUART_miso_m.h"
#endif /*(ModbusUART_SPI_MASTER_MISO_PIN) */
#endif /* (ModbusUART_SPI_MASTER_PINS) */

#if (ModbusUART_SPI_SLAVE_PINS)
    #include "ModbusUART_sclk_s.h"
    #include "ModbusUART_ss_s.h"

#if (ModbusUART_SPI_SLAVE_MOSI_PIN)
    #include "ModbusUART_mosi_s.h"
#endif /* (ModbusUART_SPI_SLAVE_MOSI_PIN) */

#if (ModbusUART_SPI_SLAVE_MISO_PIN)
    #include "ModbusUART_miso_s.h"
#endif /*(ModbusUART_SPI_SLAVE_MISO_PIN) */
#endif /* (ModbusUART_SPI_SLAVE_PINS) */

#if (ModbusUART_SPI_MASTER_SS0_PIN)
    #include "ModbusUART_ss0_m.h"
#endif /* (ModbusUART_SPI_MASTER_SS0_PIN) */

#if (ModbusUART_SPI_MASTER_SS1_PIN)
    #include "ModbusUART_ss1_m.h"
#endif /* (ModbusUART_SPI_MASTER_SS1_PIN) */

#if (ModbusUART_SPI_MASTER_SS2_PIN)
    #include "ModbusUART_ss2_m.h"
#endif /* (ModbusUART_SPI_MASTER_SS2_PIN) */

#if (ModbusUART_SPI_MASTER_SS3_PIN)
    #include "ModbusUART_ss3_m.h"
#endif /* (ModbusUART_SPI_MASTER_SS3_PIN) */

#if (ModbusUART_UART_TX_PIN)
    #include "ModbusUART_tx.h"
#endif /* (ModbusUART_UART_TX_PIN) */

#if (ModbusUART_UART_RX_TX_PIN)
    #include "ModbusUART_rx_tx.h"
#endif /* (ModbusUART_UART_RX_TX_PIN) */

#if (ModbusUART_UART_RX_PIN)
    #include "ModbusUART_rx.h"
#endif /* (ModbusUART_UART_RX_PIN) */

#if (ModbusUART_UART_RX_WAKE_PIN)
    #include "ModbusUART_rx_wake.h"
#endif /* (ModbusUART_UART_RX_WAKE_PIN) */

#if (ModbusUART_UART_RTS_PIN)
    #include "ModbusUART_rts.h"
#endif /* (ModbusUART_UART_RTS_PIN) */

#if (ModbusUART_UART_CTS_PIN)
    #include "ModbusUART_cts.h"
#endif /* (ModbusUART_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (ModbusUART_RX_SDA_MOSI_PIN)
    #define ModbusUART_RX_SDA_MOSI_HSIOM_REG   (*(reg32 *) ModbusUART_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    #define ModbusUART_RX_SDA_MOSI_HSIOM_PTR   ( (reg32 *) ModbusUART_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    
    #define ModbusUART_RX_SDA_MOSI_HSIOM_MASK      (ModbusUART_uart_rx_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define ModbusUART_RX_SDA_MOSI_HSIOM_POS       (ModbusUART_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
    #define ModbusUART_RX_SDA_MOSI_HSIOM_SEL_GPIO  (ModbusUART_uart_rx_i2c_sda_spi_mosi__0__HSIOM_GPIO)
    #define ModbusUART_RX_SDA_MOSI_HSIOM_SEL_I2C   (ModbusUART_uart_rx_i2c_sda_spi_mosi__0__HSIOM_I2C)
    #define ModbusUART_RX_SDA_MOSI_HSIOM_SEL_SPI   (ModbusUART_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SPI)
    #define ModbusUART_RX_SDA_MOSI_HSIOM_SEL_UART  (ModbusUART_uart_rx_i2c_sda_spi_mosi__0__HSIOM_UART)
    
#elif (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
    #define ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG   (*(reg32 *) ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    #define ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_PTR   ( (reg32 *) ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    
    #define ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_MASK      (ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_POS       (ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
    #define ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_SEL_GPIO  (ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_GPIO)
    #define ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_SEL_I2C   (ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_I2C)
    #define ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_SEL_SPI   (ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SPI)
    #define ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_SEL_UART  (ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_UART)    
   
    #define ModbusUART_RX_WAKE_SDA_MOSI_INTCFG_REG (*(reg32 *) ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define ModbusUART_RX_WAKE_SDA_MOSI_INTCFG_PTR ( (reg32 *) ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define ModbusUART_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS  (ModbusUART_uart_rx_wake_i2c_sda_spi_mosi__SHIFT)
    #define ModbusUART_RX_WAKE_SDA_MOSI_INTCFG_TYPE_MASK ((uint32) ModbusUART_INTCFG_TYPE_MASK << \
                                                                           ModbusUART_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins ModbusUART_RX_SDA_MOSI_PIN or ModbusUART_RX_WAKE_SDA_MOSI_PIN present.*/
#endif /* (ModbusUART_RX_SDA_MOSI_PIN) */

#if (ModbusUART_TX_SCL_MISO_PIN)
    #define ModbusUART_TX_SCL_MISO_HSIOM_REG   (*(reg32 *) ModbusUART_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    #define ModbusUART_TX_SCL_MISO_HSIOM_PTR   ( (reg32 *) ModbusUART_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    
    #define ModbusUART_TX_SCL_MISO_HSIOM_MASK      (ModbusUART_uart_tx_i2c_scl_spi_miso__0__HSIOM_MASK)
    #define ModbusUART_TX_SCL_MISO_HSIOM_POS       (ModbusUART_uart_tx_i2c_scl_spi_miso__0__HSIOM_SHIFT)
    #define ModbusUART_TX_SCL_MISO_HSIOM_SEL_GPIO  (ModbusUART_uart_tx_i2c_scl_spi_miso__0__HSIOM_GPIO)
    #define ModbusUART_TX_SCL_MISO_HSIOM_SEL_I2C   (ModbusUART_uart_tx_i2c_scl_spi_miso__0__HSIOM_I2C)
    #define ModbusUART_TX_SCL_MISO_HSIOM_SEL_SPI   (ModbusUART_uart_tx_i2c_scl_spi_miso__0__HSIOM_SPI)
    #define ModbusUART_TX_SCL_MISO_HSIOM_SEL_UART  (ModbusUART_uart_tx_i2c_scl_spi_miso__0__HSIOM_UART)
#endif /* (ModbusUART_TX_SCL_MISO_PIN) */

#if (ModbusUART_CTS_SCLK_PIN)
    #define ModbusUART_CTS_SCLK_HSIOM_REG   (*(reg32 *) ModbusUART_uart_cts_spi_sclk__0__HSIOM)
    #define ModbusUART_CTS_SCLK_HSIOM_PTR   ( (reg32 *) ModbusUART_uart_cts_spi_sclk__0__HSIOM)
    
    #define ModbusUART_CTS_SCLK_HSIOM_MASK      (ModbusUART_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define ModbusUART_CTS_SCLK_HSIOM_POS       (ModbusUART_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define ModbusUART_CTS_SCLK_HSIOM_SEL_GPIO  (ModbusUART_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define ModbusUART_CTS_SCLK_HSIOM_SEL_I2C   (ModbusUART_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define ModbusUART_CTS_SCLK_HSIOM_SEL_SPI   (ModbusUART_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define ModbusUART_CTS_SCLK_HSIOM_SEL_UART  (ModbusUART_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (ModbusUART_CTS_SCLK_PIN) */

#if (ModbusUART_RTS_SS0_PIN)
    #define ModbusUART_RTS_SS0_HSIOM_REG   (*(reg32 *) ModbusUART_uart_rts_spi_ss0__0__HSIOM)
    #define ModbusUART_RTS_SS0_HSIOM_PTR   ( (reg32 *) ModbusUART_uart_rts_spi_ss0__0__HSIOM)
    
    #define ModbusUART_RTS_SS0_HSIOM_MASK      (ModbusUART_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define ModbusUART_RTS_SS0_HSIOM_POS       (ModbusUART_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define ModbusUART_RTS_SS0_HSIOM_SEL_GPIO  (ModbusUART_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define ModbusUART_RTS_SS0_HSIOM_SEL_I2C   (ModbusUART_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define ModbusUART_RTS_SS0_HSIOM_SEL_SPI   (ModbusUART_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1)
    #define ModbusUART_RTS_SS0_HSIOM_SEL_UART  (ModbusUART_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(ModbusUART_CY_SCBIP_V0 || ModbusUART_CY_SCBIP_V1) */
#endif /* (ModbusUART_RTS_SS0_PIN) */

#if (ModbusUART_SS1_PIN)
    #define ModbusUART_SS1_HSIOM_REG  (*(reg32 *) ModbusUART_spi_ss1__0__HSIOM)
    #define ModbusUART_SS1_HSIOM_PTR  ( (reg32 *) ModbusUART_spi_ss1__0__HSIOM)
    
    #define ModbusUART_SS1_HSIOM_MASK     (ModbusUART_spi_ss1__0__HSIOM_MASK)
    #define ModbusUART_SS1_HSIOM_POS      (ModbusUART_spi_ss1__0__HSIOM_SHIFT)
    #define ModbusUART_SS1_HSIOM_SEL_GPIO (ModbusUART_spi_ss1__0__HSIOM_GPIO)
    #define ModbusUART_SS1_HSIOM_SEL_I2C  (ModbusUART_spi_ss1__0__HSIOM_I2C)
    #define ModbusUART_SS1_HSIOM_SEL_SPI  (ModbusUART_spi_ss1__0__HSIOM_SPI)
#endif /* (ModbusUART_SS1_PIN) */

#if (ModbusUART_SS2_PIN)
    #define ModbusUART_SS2_HSIOM_REG     (*(reg32 *) ModbusUART_spi_ss2__0__HSIOM)
    #define ModbusUART_SS2_HSIOM_PTR     ( (reg32 *) ModbusUART_spi_ss2__0__HSIOM)
    
    #define ModbusUART_SS2_HSIOM_MASK     (ModbusUART_spi_ss2__0__HSIOM_MASK)
    #define ModbusUART_SS2_HSIOM_POS      (ModbusUART_spi_ss2__0__HSIOM_SHIFT)
    #define ModbusUART_SS2_HSIOM_SEL_GPIO (ModbusUART_spi_ss2__0__HSIOM_GPIO)
    #define ModbusUART_SS2_HSIOM_SEL_I2C  (ModbusUART_spi_ss2__0__HSIOM_I2C)
    #define ModbusUART_SS2_HSIOM_SEL_SPI  (ModbusUART_spi_ss2__0__HSIOM_SPI)
#endif /* (ModbusUART_SS2_PIN) */

#if (ModbusUART_SS3_PIN)
    #define ModbusUART_SS3_HSIOM_REG     (*(reg32 *) ModbusUART_spi_ss3__0__HSIOM)
    #define ModbusUART_SS3_HSIOM_PTR     ( (reg32 *) ModbusUART_spi_ss3__0__HSIOM)
    
    #define ModbusUART_SS3_HSIOM_MASK     (ModbusUART_spi_ss3__0__HSIOM_MASK)
    #define ModbusUART_SS3_HSIOM_POS      (ModbusUART_spi_ss3__0__HSIOM_SHIFT)
    #define ModbusUART_SS3_HSIOM_SEL_GPIO (ModbusUART_spi_ss3__0__HSIOM_GPIO)
    #define ModbusUART_SS3_HSIOM_SEL_I2C  (ModbusUART_spi_ss3__0__HSIOM_I2C)
    #define ModbusUART_SS3_HSIOM_SEL_SPI  (ModbusUART_spi_ss3__0__HSIOM_SPI)
#endif /* (ModbusUART_SS3_PIN) */

#if (ModbusUART_I2C_PINS)
    #define ModbusUART_SCL_HSIOM_REG  (*(reg32 *) ModbusUART_scl__0__HSIOM)
    #define ModbusUART_SCL_HSIOM_PTR  ( (reg32 *) ModbusUART_scl__0__HSIOM)
    
    #define ModbusUART_SCL_HSIOM_MASK     (ModbusUART_scl__0__HSIOM_MASK)
    #define ModbusUART_SCL_HSIOM_POS      (ModbusUART_scl__0__HSIOM_SHIFT)
    #define ModbusUART_SCL_HSIOM_SEL_GPIO (ModbusUART_sda__0__HSIOM_GPIO)
    #define ModbusUART_SCL_HSIOM_SEL_I2C  (ModbusUART_sda__0__HSIOM_I2C)
    
    #define ModbusUART_SDA_HSIOM_REG  (*(reg32 *) ModbusUART_sda__0__HSIOM)
    #define ModbusUART_SDA_HSIOM_PTR  ( (reg32 *) ModbusUART_sda__0__HSIOM)
    
    #define ModbusUART_SDA_HSIOM_MASK     (ModbusUART_sda__0__HSIOM_MASK)
    #define ModbusUART_SDA_HSIOM_POS      (ModbusUART_sda__0__HSIOM_SHIFT)
    #define ModbusUART_SDA_HSIOM_SEL_GPIO (ModbusUART_sda__0__HSIOM_GPIO)
    #define ModbusUART_SDA_HSIOM_SEL_I2C  (ModbusUART_sda__0__HSIOM_I2C)
#endif /* (ModbusUART_I2C_PINS) */

#if (ModbusUART_SPI_SLAVE_PINS)
    #define ModbusUART_SCLK_S_HSIOM_REG   (*(reg32 *) ModbusUART_sclk_s__0__HSIOM)
    #define ModbusUART_SCLK_S_HSIOM_PTR   ( (reg32 *) ModbusUART_sclk_s__0__HSIOM)
    
    #define ModbusUART_SCLK_S_HSIOM_MASK      (ModbusUART_sclk_s__0__HSIOM_MASK)
    #define ModbusUART_SCLK_S_HSIOM_POS       (ModbusUART_sclk_s__0__HSIOM_SHIFT)
    #define ModbusUART_SCLK_S_HSIOM_SEL_GPIO  (ModbusUART_sclk_s__0__HSIOM_GPIO)
    #define ModbusUART_SCLK_S_HSIOM_SEL_SPI   (ModbusUART_sclk_s__0__HSIOM_SPI)
    
    #define ModbusUART_SS0_S_HSIOM_REG    (*(reg32 *) ModbusUART_ss0_s__0__HSIOM)
    #define ModbusUART_SS0_S_HSIOM_PTR    ( (reg32 *) ModbusUART_ss0_s__0__HSIOM)
    
    #define ModbusUART_SS0_S_HSIOM_MASK       (ModbusUART_ss0_s__0__HSIOM_MASK)
    #define ModbusUART_SS0_S_HSIOM_POS        (ModbusUART_ss0_s__0__HSIOM_SHIFT)
    #define ModbusUART_SS0_S_HSIOM_SEL_GPIO   (ModbusUART_ss0_s__0__HSIOM_GPIO)  
    #define ModbusUART_SS0_S_HSIOM_SEL_SPI    (ModbusUART_ss0_s__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_SLAVE_PINS) */

#if (ModbusUART_SPI_SLAVE_MOSI_PIN)
    #define ModbusUART_MOSI_S_HSIOM_REG   (*(reg32 *) ModbusUART_mosi_s__0__HSIOM)
    #define ModbusUART_MOSI_S_HSIOM_PTR   ( (reg32 *) ModbusUART_mosi_s__0__HSIOM)
    
    #define ModbusUART_MOSI_S_HSIOM_MASK      (ModbusUART_mosi_s__0__HSIOM_MASK)
    #define ModbusUART_MOSI_S_HSIOM_POS       (ModbusUART_mosi_s__0__HSIOM_SHIFT)
    #define ModbusUART_MOSI_S_HSIOM_SEL_GPIO  (ModbusUART_mosi_s__0__HSIOM_GPIO)
    #define ModbusUART_MOSI_S_HSIOM_SEL_SPI   (ModbusUART_mosi_s__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_SLAVE_MOSI_PIN) */

#if (ModbusUART_SPI_SLAVE_MISO_PIN)
    #define ModbusUART_MISO_S_HSIOM_REG   (*(reg32 *) ModbusUART_miso_s__0__HSIOM)
    #define ModbusUART_MISO_S_HSIOM_PTR   ( (reg32 *) ModbusUART_miso_s__0__HSIOM)
    
    #define ModbusUART_MISO_S_HSIOM_MASK      (ModbusUART_miso_s__0__HSIOM_MASK)
    #define ModbusUART_MISO_S_HSIOM_POS       (ModbusUART_miso_s__0__HSIOM_SHIFT)
    #define ModbusUART_MISO_S_HSIOM_SEL_GPIO  (ModbusUART_miso_s__0__HSIOM_GPIO)
    #define ModbusUART_MISO_S_HSIOM_SEL_SPI   (ModbusUART_miso_s__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_SLAVE_MISO_PIN) */

#if (ModbusUART_SPI_MASTER_MISO_PIN)
    #define ModbusUART_MISO_M_HSIOM_REG   (*(reg32 *) ModbusUART_miso_m__0__HSIOM)
    #define ModbusUART_MISO_M_HSIOM_PTR   ( (reg32 *) ModbusUART_miso_m__0__HSIOM)
    
    #define ModbusUART_MISO_M_HSIOM_MASK      (ModbusUART_miso_m__0__HSIOM_MASK)
    #define ModbusUART_MISO_M_HSIOM_POS       (ModbusUART_miso_m__0__HSIOM_SHIFT)
    #define ModbusUART_MISO_M_HSIOM_SEL_GPIO  (ModbusUART_miso_m__0__HSIOM_GPIO)
    #define ModbusUART_MISO_M_HSIOM_SEL_SPI   (ModbusUART_miso_m__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_MASTER_MISO_PIN) */

#if (ModbusUART_SPI_MASTER_MOSI_PIN)
    #define ModbusUART_MOSI_M_HSIOM_REG   (*(reg32 *) ModbusUART_mosi_m__0__HSIOM)
    #define ModbusUART_MOSI_M_HSIOM_PTR   ( (reg32 *) ModbusUART_mosi_m__0__HSIOM)
    
    #define ModbusUART_MOSI_M_HSIOM_MASK      (ModbusUART_mosi_m__0__HSIOM_MASK)
    #define ModbusUART_MOSI_M_HSIOM_POS       (ModbusUART_mosi_m__0__HSIOM_SHIFT)
    #define ModbusUART_MOSI_M_HSIOM_SEL_GPIO  (ModbusUART_mosi_m__0__HSIOM_GPIO)
    #define ModbusUART_MOSI_M_HSIOM_SEL_SPI   (ModbusUART_mosi_m__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_MASTER_MOSI_PIN) */

#if (ModbusUART_SPI_MASTER_SCLK_PIN)
    #define ModbusUART_SCLK_M_HSIOM_REG   (*(reg32 *) ModbusUART_sclk_m__0__HSIOM)
    #define ModbusUART_SCLK_M_HSIOM_PTR   ( (reg32 *) ModbusUART_sclk_m__0__HSIOM)
    
    #define ModbusUART_SCLK_M_HSIOM_MASK      (ModbusUART_sclk_m__0__HSIOM_MASK)
    #define ModbusUART_SCLK_M_HSIOM_POS       (ModbusUART_sclk_m__0__HSIOM_SHIFT)
    #define ModbusUART_SCLK_M_HSIOM_SEL_GPIO  (ModbusUART_sclk_m__0__HSIOM_GPIO)
    #define ModbusUART_SCLK_M_HSIOM_SEL_SPI   (ModbusUART_sclk_m__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_MASTER_SCLK_PIN) */

#if (ModbusUART_SPI_MASTER_SS0_PIN)
    #define ModbusUART_SS0_M_HSIOM_REG    (*(reg32 *) ModbusUART_ss0_m__0__HSIOM)
    #define ModbusUART_SS0_M_HSIOM_PTR    ( (reg32 *) ModbusUART_ss0_m__0__HSIOM)
    
    #define ModbusUART_SS0_M_HSIOM_MASK       (ModbusUART_ss0_m__0__HSIOM_MASK)
    #define ModbusUART_SS0_M_HSIOM_POS        (ModbusUART_ss0_m__0__HSIOM_SHIFT)
    #define ModbusUART_SS0_M_HSIOM_SEL_GPIO   (ModbusUART_ss0_m__0__HSIOM_GPIO)
    #define ModbusUART_SS0_M_HSIOM_SEL_SPI    (ModbusUART_ss0_m__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_MASTER_SS0_PIN) */

#if (ModbusUART_SPI_MASTER_SS1_PIN)
    #define ModbusUART_SS1_M_HSIOM_REG    (*(reg32 *) ModbusUART_ss1_m__0__HSIOM)
    #define ModbusUART_SS1_M_HSIOM_PTR    ( (reg32 *) ModbusUART_ss1_m__0__HSIOM)
    
    #define ModbusUART_SS1_M_HSIOM_MASK       (ModbusUART_ss1_m__0__HSIOM_MASK)
    #define ModbusUART_SS1_M_HSIOM_POS        (ModbusUART_ss1_m__0__HSIOM_SHIFT)
    #define ModbusUART_SS1_M_HSIOM_SEL_GPIO   (ModbusUART_ss1_m__0__HSIOM_GPIO)
    #define ModbusUART_SS1_M_HSIOM_SEL_SPI    (ModbusUART_ss1_m__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_MASTER_SS1_PIN) */

#if (ModbusUART_SPI_MASTER_SS2_PIN)
    #define ModbusUART_SS2_M_HSIOM_REG    (*(reg32 *) ModbusUART_ss2_m__0__HSIOM)
    #define ModbusUART_SS2_M_HSIOM_PTR    ( (reg32 *) ModbusUART_ss2_m__0__HSIOM)
    
    #define ModbusUART_SS2_M_HSIOM_MASK       (ModbusUART_ss2_m__0__HSIOM_MASK)
    #define ModbusUART_SS2_M_HSIOM_POS        (ModbusUART_ss2_m__0__HSIOM_SHIFT)
    #define ModbusUART_SS2_M_HSIOM_SEL_GPIO   (ModbusUART_ss2_m__0__HSIOM_GPIO)
    #define ModbusUART_SS2_M_HSIOM_SEL_SPI    (ModbusUART_ss2_m__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_MASTER_SS2_PIN) */

#if (ModbusUART_SPI_MASTER_SS3_PIN)
    #define ModbusUART_SS3_M_HSIOM_REG    (*(reg32 *) ModbusUART_ss3_m__0__HSIOM)
    #define ModbusUART_SS3_M_HSIOM_PTR    ( (reg32 *) ModbusUART_ss3_m__0__HSIOM)
    
    #define ModbusUART_SS3_M_HSIOM_MASK      (ModbusUART_ss3_m__0__HSIOM_MASK)
    #define ModbusUART_SS3_M_HSIOM_POS       (ModbusUART_ss3_m__0__HSIOM_SHIFT)
    #define ModbusUART_SS3_M_HSIOM_SEL_GPIO  (ModbusUART_ss3_m__0__HSIOM_GPIO)
    #define ModbusUART_SS3_M_HSIOM_SEL_SPI   (ModbusUART_ss3_m__0__HSIOM_SPI)
#endif /* (ModbusUART_SPI_MASTER_SS3_PIN) */

#if (ModbusUART_UART_RX_PIN)
    #define ModbusUART_RX_HSIOM_REG   (*(reg32 *) ModbusUART_rx__0__HSIOM)
    #define ModbusUART_RX_HSIOM_PTR   ( (reg32 *) ModbusUART_rx__0__HSIOM)
    
    #define ModbusUART_RX_HSIOM_MASK      (ModbusUART_rx__0__HSIOM_MASK)
    #define ModbusUART_RX_HSIOM_POS       (ModbusUART_rx__0__HSIOM_SHIFT)
    #define ModbusUART_RX_HSIOM_SEL_GPIO  (ModbusUART_rx__0__HSIOM_GPIO)
    #define ModbusUART_RX_HSIOM_SEL_UART  (ModbusUART_rx__0__HSIOM_UART)
#endif /* (ModbusUART_UART_RX_PIN) */

#if (ModbusUART_UART_RX_WAKE_PIN)
    #define ModbusUART_RX_WAKE_HSIOM_REG   (*(reg32 *) ModbusUART_rx_wake__0__HSIOM)
    #define ModbusUART_RX_WAKE_HSIOM_PTR   ( (reg32 *) ModbusUART_rx_wake__0__HSIOM)
    
    #define ModbusUART_RX_WAKE_HSIOM_MASK      (ModbusUART_rx_wake__0__HSIOM_MASK)
    #define ModbusUART_RX_WAKE_HSIOM_POS       (ModbusUART_rx_wake__0__HSIOM_SHIFT)
    #define ModbusUART_RX_WAKE_HSIOM_SEL_GPIO  (ModbusUART_rx_wake__0__HSIOM_GPIO)
    #define ModbusUART_RX_WAKE_HSIOM_SEL_UART  (ModbusUART_rx_wake__0__HSIOM_UART)
#endif /* (ModbusUART_UART_WAKE_RX_PIN) */

#if (ModbusUART_UART_CTS_PIN)
    #define ModbusUART_CTS_HSIOM_REG   (*(reg32 *) ModbusUART_cts__0__HSIOM)
    #define ModbusUART_CTS_HSIOM_PTR   ( (reg32 *) ModbusUART_cts__0__HSIOM)
    
    #define ModbusUART_CTS_HSIOM_MASK      (ModbusUART_cts__0__HSIOM_MASK)
    #define ModbusUART_CTS_HSIOM_POS       (ModbusUART_cts__0__HSIOM_SHIFT)
    #define ModbusUART_CTS_HSIOM_SEL_GPIO  (ModbusUART_cts__0__HSIOM_GPIO)
    #define ModbusUART_CTS_HSIOM_SEL_UART  (ModbusUART_cts__0__HSIOM_UART)
#endif /* (ModbusUART_UART_CTS_PIN) */

#if (ModbusUART_UART_TX_PIN)
    #define ModbusUART_TX_HSIOM_REG   (*(reg32 *) ModbusUART_tx__0__HSIOM)
    #define ModbusUART_TX_HSIOM_PTR   ( (reg32 *) ModbusUART_tx__0__HSIOM)
    
    #define ModbusUART_TX_HSIOM_MASK      (ModbusUART_tx__0__HSIOM_MASK)
    #define ModbusUART_TX_HSIOM_POS       (ModbusUART_tx__0__HSIOM_SHIFT)
    #define ModbusUART_TX_HSIOM_SEL_GPIO  (ModbusUART_tx__0__HSIOM_GPIO)
    #define ModbusUART_TX_HSIOM_SEL_UART  (ModbusUART_tx__0__HSIOM_UART)
#endif /* (ModbusUART_UART_TX_PIN) */

#if (ModbusUART_UART_RX_TX_PIN)
    #define ModbusUART_RX_TX_HSIOM_REG   (*(reg32 *) ModbusUART_rx_tx__0__HSIOM)
    #define ModbusUART_RX_TX_HSIOM_PTR   ( (reg32 *) ModbusUART_rx_tx__0__HSIOM)
    
    #define ModbusUART_RX_TX_HSIOM_MASK      (ModbusUART_rx_tx__0__HSIOM_MASK)
    #define ModbusUART_RX_TX_HSIOM_POS       (ModbusUART_rx_tx__0__HSIOM_SHIFT)
    #define ModbusUART_RX_TX_HSIOM_SEL_GPIO  (ModbusUART_rx_tx__0__HSIOM_GPIO)
    #define ModbusUART_RX_TX_HSIOM_SEL_UART  (ModbusUART_rx_tx__0__HSIOM_UART)
#endif /* (ModbusUART_UART_RX_TX_PIN) */

#if (ModbusUART_UART_RTS_PIN)
    #define ModbusUART_RTS_HSIOM_REG      (*(reg32 *) ModbusUART_rts__0__HSIOM)
    #define ModbusUART_RTS_HSIOM_PTR      ( (reg32 *) ModbusUART_rts__0__HSIOM)
    
    #define ModbusUART_RTS_HSIOM_MASK     (ModbusUART_rts__0__HSIOM_MASK)
    #define ModbusUART_RTS_HSIOM_POS      (ModbusUART_rts__0__HSIOM_SHIFT)    
    #define ModbusUART_RTS_HSIOM_SEL_GPIO (ModbusUART_rts__0__HSIOM_GPIO)
    #define ModbusUART_RTS_HSIOM_SEL_UART (ModbusUART_rts__0__HSIOM_UART)    
#endif /* (ModbusUART_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define ModbusUART_HSIOM_DEF_SEL      (0x00u)
#define ModbusUART_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for ModbusUART_CY_SCBIP_V0 
* and ModbusUART_CY_SCBIP_V1. It is not recommended to use them for 
* ModbusUART_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define ModbusUART_HSIOM_UART_SEL     (0x09u)
#define ModbusUART_HSIOM_I2C_SEL      (0x0Eu)
#define ModbusUART_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX   (0u)
#define ModbusUART_RX_SDA_MOSI_PIN_INDEX       (0u)
#define ModbusUART_TX_SCL_MISO_PIN_INDEX       (1u)
#define ModbusUART_CTS_SCLK_PIN_INDEX       (2u)
#define ModbusUART_RTS_SS0_PIN_INDEX       (3u)
#define ModbusUART_SS1_PIN_INDEX                  (4u)
#define ModbusUART_SS2_PIN_INDEX                  (5u)
#define ModbusUART_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define ModbusUART_RX_WAKE_SDA_MOSI_PIN_MASK ((uint32) 0x01u << ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX)
#define ModbusUART_RX_SDA_MOSI_PIN_MASK     ((uint32) 0x01u << ModbusUART_RX_SDA_MOSI_PIN_INDEX)
#define ModbusUART_TX_SCL_MISO_PIN_MASK     ((uint32) 0x01u << ModbusUART_TX_SCL_MISO_PIN_INDEX)
#define ModbusUART_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << ModbusUART_CTS_SCLK_PIN_INDEX)
#define ModbusUART_RTS_SS0_PIN_MASK     ((uint32) 0x01u << ModbusUART_RTS_SS0_PIN_INDEX)
#define ModbusUART_SS1_PIN_MASK                ((uint32) 0x01u << ModbusUART_SS1_PIN_INDEX)
#define ModbusUART_SS2_PIN_MASK                ((uint32) 0x01u << ModbusUART_SS2_PIN_INDEX)
#define ModbusUART_SS3_PIN_MASK                ((uint32) 0x01u << ModbusUART_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define ModbusUART_INTCFG_TYPE_MASK           (0x03u)
#define ModbusUART_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define ModbusUART_PIN_DM_ALG_HIZ  (0u)
#define ModbusUART_PIN_DM_DIG_HIZ  (1u)
#define ModbusUART_PIN_DM_OD_LO    (4u)
#define ModbusUART_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define ModbusUART_DM_MASK    (0x7u)
#define ModbusUART_DM_SIZE    (3u)
#define ModbusUART_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) ModbusUART_DM_MASK << (ModbusUART_DM_SIZE * (pos)))) >> \
                                                              (ModbusUART_DM_SIZE * (pos)) )

#if (ModbusUART_TX_SCL_MISO_PIN)
    #define ModbusUART_CHECK_TX_SCL_MISO_PIN_USED \
                (ModbusUART_PIN_DM_ALG_HIZ != \
                    ModbusUART_GET_P4_PIN_DM(ModbusUART_uart_tx_i2c_scl_spi_miso_PC, \
                                                   ModbusUART_uart_tx_i2c_scl_spi_miso_SHIFT))
#endif /* (ModbusUART_TX_SCL_MISO_PIN) */

#if (ModbusUART_RTS_SS0_PIN)
    #define ModbusUART_CHECK_RTS_SS0_PIN_USED \
                (ModbusUART_PIN_DM_ALG_HIZ != \
                    ModbusUART_GET_P4_PIN_DM(ModbusUART_uart_rts_spi_ss0_PC, \
                                                   ModbusUART_uart_rts_spi_ss0_SHIFT))
#endif /* (ModbusUART_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define ModbusUART_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define ModbusUART_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define ModbusUART_SET_HSIOM_SEL(reg, mask, pos, sel) ModbusUART_SET_REGISTER_BITS(reg, mask, pos, sel)
#define ModbusUART_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        ModbusUART_SET_REGISTER_BITS(reg, mask, pos, intType)
#define ModbusUART_SET_INP_DIS(reg, mask, val) ModbusUART_SET_REGISTER_BIT(reg, mask, val)

/* ModbusUART_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (ModbusUART_CY_SCBIP_V0)
#if (ModbusUART_I2C_PINS)
    #define ModbusUART_SET_I2C_SCL_DR(val) ModbusUART_scl_Write(val)

    #define ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) \
                          ModbusUART_SET_HSIOM_SEL(ModbusUART_SCL_HSIOM_REG,  \
                                                         ModbusUART_SCL_HSIOM_MASK, \
                                                         ModbusUART_SCL_HSIOM_POS,  \
                                                         (sel))
    #define ModbusUART_WAIT_SCL_SET_HIGH  (0u == ModbusUART_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
    #define ModbusUART_SET_I2C_SCL_DR(val) \
                            ModbusUART_uart_rx_wake_i2c_sda_spi_mosi_Write(val)

    #define ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) \
                    ModbusUART_SET_HSIOM_SEL(ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG,  \
                                                   ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_MASK, \
                                                   ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define ModbusUART_WAIT_SCL_SET_HIGH  (0u == ModbusUART_uart_rx_wake_i2c_sda_spi_mosi_Read())

#elif (ModbusUART_RX_SDA_MOSI_PIN)
    #define ModbusUART_SET_I2C_SCL_DR(val) \
                            ModbusUART_uart_rx_i2c_sda_spi_mosi_Write(val)


    #define ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) \
                            ModbusUART_SET_HSIOM_SEL(ModbusUART_RX_SDA_MOSI_HSIOM_REG,  \
                                                           ModbusUART_RX_SDA_MOSI_HSIOM_MASK, \
                                                           ModbusUART_RX_SDA_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define ModbusUART_WAIT_SCL_SET_HIGH  (0u == ModbusUART_uart_rx_i2c_sda_spi_mosi_Read())

#else
    #define ModbusUART_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define ModbusUART_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define ModbusUART_WAIT_SCL_SET_HIGH  (0u)
#endif /* (ModbusUART_I2C_PINS) */

/* SCB I2C: sda signal */
#if (ModbusUART_I2C_PINS)
    #define ModbusUART_WAIT_SDA_SET_HIGH  (0u == ModbusUART_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (ModbusUART_TX_SCL_MISO_PIN)
    #define ModbusUART_WAIT_SDA_SET_HIGH  (0u == ModbusUART_uart_tx_i2c_scl_spi_miso_Read())
#else
    #define ModbusUART_WAIT_SDA_SET_HIGH  (0u)
#endif /* (ModbusUART_MOSI_SCL_RX_PIN) */
#endif /* (ModbusUART_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (ModbusUART_RX_SDA_MOSI_PIN)
    #define ModbusUART_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (ModbusUART_RX_WAKE_SDA_MOSI_PIN)
    #define ModbusUART_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) ModbusUART_uart_rx_wake_i2c_sda_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(ModbusUART_UART_RX_WAKE_PIN)
    #define ModbusUART_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) ModbusUART_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (ModbusUART_RX_SDA_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define ModbusUART_REMOVE_MOSI_SCL_RX_WAKE_PIN    ModbusUART_REMOVE_RX_WAKE_SDA_MOSI_PIN
#define ModbusUART_REMOVE_MOSI_SCL_RX_PIN         ModbusUART_REMOVE_RX_SDA_MOSI_PIN
#define ModbusUART_REMOVE_MISO_SDA_TX_PIN         ModbusUART_REMOVE_TX_SCL_MISO_PIN
#ifndef ModbusUART_REMOVE_SCLK_PIN
#define ModbusUART_REMOVE_SCLK_PIN                ModbusUART_REMOVE_CTS_SCLK_PIN
#endif /* ModbusUART_REMOVE_SCLK_PIN */
#ifndef ModbusUART_REMOVE_SS0_PIN
#define ModbusUART_REMOVE_SS0_PIN                 ModbusUART_REMOVE_RTS_SS0_PIN
#endif /* ModbusUART_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define ModbusUART_MOSI_SCL_RX_WAKE_PIN   ModbusUART_RX_WAKE_SDA_MOSI_PIN
#define ModbusUART_MOSI_SCL_RX_PIN        ModbusUART_RX_SDA_MOSI_PIN
#define ModbusUART_MISO_SDA_TX_PIN        ModbusUART_TX_SCL_MISO_PIN
#ifndef ModbusUART_SCLK_PIN
#define ModbusUART_SCLK_PIN               ModbusUART_CTS_SCLK_PIN
#endif /* ModbusUART_SCLK_PIN */
#ifndef ModbusUART_SS0_PIN
#define ModbusUART_SS0_PIN                ModbusUART_RTS_SS0_PIN
#endif /* ModbusUART_SS0_PIN */

#if (ModbusUART_MOSI_SCL_RX_WAKE_PIN)
    #define ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_REG     ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_PTR     ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_MASK    ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define ModbusUART_MOSI_SCL_RX_WAKE_HSIOM_POS     ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_REG    ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_PTR    ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define ModbusUART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  ModbusUART_RX_WAKE_SDA_MOSI_HSIOM_REG
#endif /* (ModbusUART_RX_WAKE_SDA_MOSI_PIN) */

#if (ModbusUART_MOSI_SCL_RX_PIN)
    #define ModbusUART_MOSI_SCL_RX_HSIOM_REG      ModbusUART_RX_SDA_MOSI_HSIOM_REG
    #define ModbusUART_MOSI_SCL_RX_HSIOM_PTR      ModbusUART_RX_SDA_MOSI_HSIOM_PTR
    #define ModbusUART_MOSI_SCL_RX_HSIOM_MASK     ModbusUART_RX_SDA_MOSI_HSIOM_MASK
    #define ModbusUART_MOSI_SCL_RX_HSIOM_POS      ModbusUART_RX_SDA_MOSI_HSIOM_POS
#endif /* (ModbusUART_MOSI_SCL_RX_PIN) */

#if (ModbusUART_MISO_SDA_TX_PIN)
    #define ModbusUART_MISO_SDA_TX_HSIOM_REG      ModbusUART_TX_SCL_MISO_HSIOM_REG
    #define ModbusUART_MISO_SDA_TX_HSIOM_PTR      ModbusUART_TX_SCL_MISO_HSIOM_REG
    #define ModbusUART_MISO_SDA_TX_HSIOM_MASK     ModbusUART_TX_SCL_MISO_HSIOM_REG
    #define ModbusUART_MISO_SDA_TX_HSIOM_POS      ModbusUART_TX_SCL_MISO_HSIOM_REG
#endif /* (ModbusUART_MISO_SDA_TX_PIN_PIN) */

#if (ModbusUART_SCLK_PIN)
    #ifndef ModbusUART_SCLK_HSIOM_REG
    #define ModbusUART_SCLK_HSIOM_REG     ModbusUART_CTS_SCLK_HSIOM_REG
    #define ModbusUART_SCLK_HSIOM_PTR     ModbusUART_CTS_SCLK_HSIOM_PTR
    #define ModbusUART_SCLK_HSIOM_MASK    ModbusUART_CTS_SCLK_HSIOM_MASK
    #define ModbusUART_SCLK_HSIOM_POS     ModbusUART_CTS_SCLK_HSIOM_POS
    #endif /* ModbusUART_SCLK_HSIOM_REG */
#endif /* (ModbusUART_SCLK_PIN) */

#if (ModbusUART_SS0_PIN)
    #ifndef ModbusUART_SS0_HSIOM_REG
    #define ModbusUART_SS0_HSIOM_REG      ModbusUART_RTS_SS0_HSIOM_REG
    #define ModbusUART_SS0_HSIOM_PTR      ModbusUART_RTS_SS0_HSIOM_PTR
    #define ModbusUART_SS0_HSIOM_MASK     ModbusUART_RTS_SS0_HSIOM_MASK
    #define ModbusUART_SS0_HSIOM_POS      ModbusUART_RTS_SS0_HSIOM_POS
    #endif /* ModbusUART_SS0_HSIOM_REG */
#endif /* (ModbusUART_SS0_PIN) */

#define ModbusUART_MOSI_SCL_RX_WAKE_PIN_INDEX ModbusUART_RX_WAKE_SDA_MOSI_PIN_INDEX
#define ModbusUART_MOSI_SCL_RX_PIN_INDEX      ModbusUART_RX_SDA_MOSI_PIN_INDEX
#define ModbusUART_MISO_SDA_TX_PIN_INDEX      ModbusUART_TX_SCL_MISO_PIN_INDEX
#ifndef ModbusUART_SCLK_PIN_INDEX
#define ModbusUART_SCLK_PIN_INDEX             ModbusUART_CTS_SCLK_PIN_INDEX
#endif /* ModbusUART_SCLK_PIN_INDEX */
#ifndef ModbusUART_SS0_PIN_INDEX
#define ModbusUART_SS0_PIN_INDEX              ModbusUART_RTS_SS0_PIN_INDEX
#endif /* ModbusUART_SS0_PIN_INDEX */

#define ModbusUART_MOSI_SCL_RX_WAKE_PIN_MASK ModbusUART_RX_WAKE_SDA_MOSI_PIN_MASK
#define ModbusUART_MOSI_SCL_RX_PIN_MASK      ModbusUART_RX_SDA_MOSI_PIN_MASK
#define ModbusUART_MISO_SDA_TX_PIN_MASK      ModbusUART_TX_SCL_MISO_PIN_MASK
#ifndef ModbusUART_SCLK_PIN_MASK
#define ModbusUART_SCLK_PIN_MASK             ModbusUART_CTS_SCLK_PIN_MASK
#endif /* ModbusUART_SCLK_PIN_MASK */
#ifndef ModbusUART_SS0_PIN_MASK
#define ModbusUART_SS0_PIN_MASK              ModbusUART_RTS_SS0_PIN_MASK
#endif /* ModbusUART_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_ModbusUART_H) */


/* [] END OF FILE */
