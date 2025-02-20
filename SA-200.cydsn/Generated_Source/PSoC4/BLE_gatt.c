/***************************************************************************//**
* \file CYBLE_gatt.c
* \version 3.40
* 
* \brief
*  This file contains the source code for the GATT API of the BLE Component.
* 
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "BLE_eventHandler.h"


/***************************************
* Global variables
***************************************/

CYBLE_STATE_T cyBle_state;

#if ((CYBLE_MODE_PROFILE) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))
    
#if(CYBLE_MODE_PROFILE)
    #if defined(__ARMCC_VERSION)
        CY_ALIGN(CYDEV_FLS_ROW_SIZE) const CY_BLE_FLASH_STORAGE cyBle_flashStorage CY_SECTION(".cy_checksum_exclude") =
    #elif defined (__GNUC__)
        const CY_BLE_FLASH_STORAGE cyBle_flashStorage CY_SECTION(".cy_checksum_exclude")
            CY_ALIGN(CYDEV_FLS_ROW_SIZE) =
    #elif defined (__ICCARM__)
        #pragma data_alignment=CY_FLASH_SIZEOF_ROW
        #pragma location=".cy_checksum_exclude"
        const CY_BLE_FLASH_STORAGE cyBle_flashStorage =
    #endif  /* (__ARMCC_VERSION) */
    {
        { 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u }, 
        {{
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        }}, 
        0x26u, /* CYBLE_GATT_DB_CCCD_COUNT */ 
        0x05u, /* CYBLE_GAP_MAX_BONDED_DEVICE */ 
    };
#endif /* (CYBLE_MODE_PROFILE) */

#endif  /* (CYBLE_MODE_PROFILE) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */

#if(CYBLE_GATT_ROLE_SERVER)
    
    const CYBLE_GATTS_T cyBle_gatts =
{
    0x000Cu,    /* Handle of the GATT service */
    0x000Eu,    /* Handle of the Service Changed characteristic */
    0x000Fu,    /* Handle of the Client Characteristic Configuration descriptor */
};
    
    static uint8 cyBle_attValues[0x0238u] = {
    /* Device Name */
    (uint8)'A', (uint8)'l', (uint8)'e', (uint8)'x', (uint8)'P', (uint8)'o', (uint8)'r', (uint8)'t', (uint8)'S',
    (uint8)'A', (uint8)'-', (uint8)'2', (uint8)'0', (uint8)'0',

    /* Appearance */
    0x00u, 0x00u,

    /* Peripheral Preferred Connection Parameters */
    0x28u, 0x00u, 0x38u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x00u,

    /* Central Address Resolution */
    0x00u,

    /* Resolvable Private Address Only */
    0x00u,

    /* Service Changed */
    0x00u, 0x00u, 0x00u, 0x00u,

    /* SYS_REMOTE */
    0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'R', (uint8)'E', (uint8)'M', (uint8)'O', (uint8)'T',
    (uint8)'E',

    /* SYS_READING */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'R', (uint8)'E', (uint8)'A', (uint8)'D', (uint8)'I',
    (uint8)'N', (uint8)'G',

    /* SYS_STATUS */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'S', (uint8)'T', (uint8)'A', (uint8)'T', (uint8)'U',
    (uint8)'S',

    /* SYS_CAN_CHAN */
    0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'C', (uint8)'A', (uint8)'N', (uint8)'_', (uint8)'C',
    (uint8)'H', (uint8)'A', (uint8)'N',

    /* SYS_CAN_ID */
    0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'C', (uint8)'A', (uint8)'N', (uint8)'_', (uint8)'I',
    (uint8)'D',

    /* SYS_CAL_LOOP */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'L',
    (uint8)'O', (uint8)'O', (uint8)'P',

    /* SYS_ADC */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'A', (uint8)'D', (uint8)'C',

    /* SYS_ALERT_1 */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'A', (uint8)'L', (uint8)'E', (uint8)'R', (uint8)'T',
    (uint8)'_', (uint8)'1',

    /* SYS_ALERT_2 */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'A', (uint8)'L', (uint8)'E', (uint8)'R', (uint8)'T',
    (uint8)'_', (uint8)'2',

    /* SYS_ALERT_1_ASC */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'A', (uint8)'L', (uint8)'E', (uint8)'R', (uint8)'T',
    (uint8)'_', (uint8)'1', (uint8)'_', (uint8)'A', (uint8)'S', (uint8)'C',

    /* SYS_ALERT_2_ASC */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'A', (uint8)'L', (uint8)'E', (uint8)'R', (uint8)'T',
    (uint8)'_', (uint8)'2', (uint8)'_', (uint8)'A', (uint8)'S', (uint8)'C',

    /* SYS_FRACTIONAL */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'Y', (uint8)'S', (uint8)'_', (uint8)'F', (uint8)'R', (uint8)'A', (uint8)'C', (uint8)'T',
    (uint8)'I', (uint8)'O', (uint8)'N', (uint8)'A', (uint8)'L',

    /* Manufacturer Name String */
    (uint8)'S', (uint8)'a', (uint8)'f', (uint8)'e', (uint8)'g', (uint8)'u', (uint8)'a', (uint8)'r', (uint8)'d',
    (uint8)' ', (uint8)'A', (uint8)'n', (uint8)'a', (uint8)'l', (uint8)'y', (uint8)'t', (uint8)'i', (uint8)'c',
    (uint8)'s',

    /* Model Number String */
    (uint8)'S', (uint8)'A', (uint8)'-', (uint8)'1', (uint8)'A', (uint8)'Q',

    /* Serial Number String */
    (uint8)'S', (uint8)'N', (uint8)'0', (uint8)'0', (uint8)'1', (uint8)'\0', (uint8)'\0', (uint8)'\0', (uint8)'\0',
    (uint8)'\0', (uint8)'\0', (uint8)'\0',

    /* Hardware Revision String */
    (uint8)' ', (uint8)' ', (uint8)'R', (uint8)'2',

    /* Firmware Revision String */
    (uint8)'F', (uint8)'W', (uint8)'0', (uint8)'1',

    /* Software Revision String */
    (uint8)'N', (uint8)'A',

    /* System ID */
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,

    /* IEEE 11073-20601 Regulatory Certification Data List */
    0x00u,

    /* PnP ID */
    0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,

    /* PIN */
    (uint8)'0', (uint8)'0', (uint8)'0', (uint8)'0',

    /* Characteristic User Description */
    (uint8)'P', (uint8)'I', (uint8)'N',

    /* SENSOR_TYPE */
    0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'E', (uint8)'N', (uint8)'S', (uint8)'O', (uint8)'R', (uint8)'_', (uint8)'T', (uint8)'Y',
    (uint8)'P', (uint8)'E',

    /* SENSOR_RANGE */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'E', (uint8)'N', (uint8)'S', (uint8)'O', (uint8)'R', (uint8)'_', (uint8)'R', (uint8)'A',
    (uint8)'N', (uint8)'G', (uint8)'E',

    /* SENSOR_GAS_NOTE */
    (uint8)'T', (uint8)'Y', (uint8)'P', (uint8)'U', (uint8)'N', (uint8)'K', (uint8)'N', (uint8)'O', (uint8)'W',
    (uint8)'N',

    /* Characteristic User Description */
    (uint8)'S', (uint8)'E', (uint8)'N', (uint8)'S', (uint8)'O', (uint8)'R', (uint8)'_', (uint8)'G', (uint8)'A',
    (uint8)'S', (uint8)'_', (uint8)'N', (uint8)'O', (uint8)'T', (uint8)'E',

    /* SENSOR_TAG */
    (uint8)'S', (uint8)'A', (uint8)'F', (uint8)'E', (uint8)'G', (uint8)'U', (uint8)'A', (uint8)'R', (uint8)'D',
    (uint8)' ', (uint8)'A', (uint8)'N', (uint8)'A', (uint8)'L', (uint8)'Y', (uint8)'T', (uint8)'I', (uint8)'C',
    (uint8)'S',

    /* Characteristic User Description */
    (uint8)'S', (uint8)'E', (uint8)'N', (uint8)'S', (uint8)'O', (uint8)'R', (uint8)'_', (uint8)'T', (uint8)'A',
    (uint8)'G',

    /* SENSOR_TEMPERATURE */
    0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'E', (uint8)'N', (uint8)'S', (uint8)'O', (uint8)'R', (uint8)'_', (uint8)'T', (uint8)'E',
    (uint8)'M', (uint8)'P', (uint8)'E', (uint8)'R', (uint8)'A', (uint8)'T', (uint8)'U', (uint8)'R', (uint8)'E',

    /* SENSOR_CAL_LEVEL */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'E', (uint8)'N', (uint8)'S', (uint8)'O', (uint8)'R', (uint8)'_', (uint8)'C', (uint8)'A',
    (uint8)'L', (uint8)'_', (uint8)'L', (uint8)'E', (uint8)'V', (uint8)'E', (uint8)'L',

    /* CAL_Z_COUNTS */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'Z', (uint8)'_', (uint8)'C', (uint8)'O', (uint8)'U',
    (uint8)'N', (uint8)'T', (uint8)'S',

    /* ZERO_READING */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'Z', (uint8)'E', (uint8)'R', (uint8)'O', (uint8)'_', (uint8)'R', (uint8)'E', (uint8)'A', (uint8)'D',
    (uint8)'I', (uint8)'N', (uint8)'G',

    /* CAL_ZERO_ERROR */
    0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'Z', (uint8)'E', (uint8)'R', (uint8)'O', (uint8)'_',
    (uint8)'E', (uint8)'R', (uint8)'R', (uint8)'O', (uint8)'R',

    /* CAL_STEP */
    0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'S', (uint8)'T', (uint8)'E', (uint8)'P',

    /* CAL_SPEED */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'S', (uint8)'P', (uint8)'E', (uint8)'E', (uint8)'D',

    /* CAL_AS_FOUND */
    0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'A', (uint8)'S', (uint8)'_', (uint8)'F', (uint8)'O',
    (uint8)'U', (uint8)'N', (uint8)'D',

    /* CAL_ADJUSTED */
    0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'A', (uint8)'D', (uint8)'J', (uint8)'U', (uint8)'S',
    (uint8)'T', (uint8)'E', (uint8)'D',

    /* CAL_COUNTS */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'C', (uint8)'O', (uint8)'U', (uint8)'N', (uint8)'T',
    (uint8)'S',

    /* SENSOR_LIFE */
    0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'E', (uint8)'N', (uint8)'S', (uint8)'O', (uint8)'R', (uint8)'_', (uint8)'L', (uint8)'I',
    (uint8)'F', (uint8)'E',

    /* CAL_CLEARING */
    0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'C', (uint8)'L', (uint8)'E', (uint8)'A', (uint8)'R',
    (uint8)'I', (uint8)'N', (uint8)'G',

    /* CAL_SPAN_ERROR */
    0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'_', (uint8)'S', (uint8)'P', (uint8)'A', (uint8)'N', (uint8)'_',
    (uint8)'E', (uint8)'R', (uint8)'R', (uint8)'O', (uint8)'R',

    /* CALIBRATION_STATUS */
    0x00u,

    /* Characteristic User Description */
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'I', (uint8)'B', (uint8)'R', (uint8)'A', (uint8)'T', (uint8)'I',
    (uint8)'O', (uint8)'N', (uint8)'_', (uint8)'S', (uint8)'T', (uint8)'A', (uint8)'T', (uint8)'U', (uint8)'S',

    /* READING_SCALED */
    0x00u, 0x00u, 0x00u, 0x00u,

    /* Characteristic User Description */
    (uint8)'R', (uint8)'E', (uint8)'A', (uint8)'D', (uint8)'I', (uint8)'N', (uint8)'G', (uint8)'_', (uint8)'S',
    (uint8)'C', (uint8)'A', (uint8)'L', (uint8)'E', (uint8)'D',

    /* ALERT_STATUS */
    0x00u,

    /* Characteristic User Description */
    (uint8)'A', (uint8)'L', (uint8)'E', (uint8)'R', (uint8)'T', (uint8)'_', (uint8)'S', (uint8)'T', (uint8)'A',
    (uint8)'T', (uint8)'U', (uint8)'S',

};
#if(CYBLE_GATT_DB_CCCD_COUNT != 0u)
uint8 cyBle_attValuesCCCD[CYBLE_GATT_DB_CCCD_COUNT];
#endif /* CYBLE_GATT_DB_CCCD_COUNT != 0u */

CYBLE_GATTS_ATT_GEN_VAL_LEN_T cyBle_attValuesLen[CYBLE_GATT_DB_ATT_VAL_COUNT] = {
    { 0x000Eu, (void *)&cyBle_attValues[0] }, /* Device Name */
    { 0x0002u, (void *)&cyBle_attValues[14] }, /* Appearance */
    { 0x0008u, (void *)&cyBle_attValues[16] }, /* Peripheral Preferred Connection Parameters */
    { 0x0001u, (void *)&cyBle_attValues[24] }, /* Central Address Resolution */
    { 0x0001u, (void *)&cyBle_attValues[25] }, /* Resolvable Private Address Only */
    { 0x0004u, (void *)&cyBle_attValues[26] }, /* Service Changed */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[0] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[30] }, /* SYS_REMOTE */
    { 0x000Au, (void *)&cyBle_attValues[31] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[2] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[41] }, /* SYS_READING */
    { 0x000Bu, (void *)&cyBle_attValues[43] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[4] }, /* SYS_READING_CCCD */
    { 0x0002u, (void *)&cyBle_attValues[54] }, /* SYS_STATUS */
    { 0x000Au, (void *)&cyBle_attValues[56] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[6] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[66] }, /* SYS_CAN_CHAN */
    { 0x000Cu, (void *)&cyBle_attValues[67] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[79] }, /* SYS_CAN_ID */
    { 0x000Au, (void *)&cyBle_attValues[80] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValues[90] }, /* SYS_CAL_LOOP */
    { 0x000Cu, (void *)&cyBle_attValues[92] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValues[104] }, /* SYS_ADC */
    { 0x0007u, (void *)&cyBle_attValues[106] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[8] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[113] }, /* SYS_ALERT_1 */
    { 0x000Bu, (void *)&cyBle_attValues[115] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValues[126] }, /* SYS_ALERT_2 */
    { 0x000Bu, (void *)&cyBle_attValues[128] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValues[139] }, /* SYS_ALERT_1_ASC */
    { 0x000Fu, (void *)&cyBle_attValues[141] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValues[156] }, /* SYS_ALERT_2_ASC */
    { 0x000Fu, (void *)&cyBle_attValues[158] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValues[173] }, /* SYS_FRACTIONAL */
    { 0x000Eu, (void *)&cyBle_attValues[175] }, /* Characteristic User Description */
    { 0x0013u, (void *)&cyBle_attValues[189] }, /* Manufacturer Name String */
    { 0x0006u, (void *)&cyBle_attValues[208] }, /* Model Number String */
    { 0x000Cu, (void *)&cyBle_attValues[214] }, /* Serial Number String */
    { 0x0004u, (void *)&cyBle_attValues[226] }, /* Hardware Revision String */
    { 0x0004u, (void *)&cyBle_attValues[230] }, /* Firmware Revision String */
    { 0x0002u, (void *)&cyBle_attValues[234] }, /* Software Revision String */
    { 0x0008u, (void *)&cyBle_attValues[236] }, /* System ID */
    { 0x0001u, (void *)&cyBle_attValues[244] }, /* IEEE 11073-20601 Regulatory Certification Data List */
    { 0x0007u, (void *)&cyBle_attValues[245] }, /* PnP ID */
    { 0x0004u, (void *)&cyBle_attValues[252] }, /* PIN */
    { 0x0003u, (void *)&cyBle_attValues[256] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[259] }, /* SENSOR_TYPE */
    { 0x000Bu, (void *)&cyBle_attValues[260] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValues[271] }, /* SENSOR_RANGE */
    { 0x000Cu, (void *)&cyBle_attValues[273] }, /* Characteristic User Description */
    { 0x000Au, (void *)&cyBle_attValues[285] }, /* SENSOR_GAS_NOTE */
    { 0x000Fu, (void *)&cyBle_attValues[295] }, /* Characteristic User Description */
    { 0x0013u, (void *)&cyBle_attValues[310] }, /* SENSOR_TAG */
    { 0x000Au, (void *)&cyBle_attValues[329] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[339] }, /* SENSOR_TEMPERATURE */
    { 0x0012u, (void *)&cyBle_attValues[340] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[10] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[358] }, /* SENSOR_CAL_LEVEL */
    { 0x0010u, (void *)&cyBle_attValues[360] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[12] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[376] }, /* CAL_Z_COUNTS */
    { 0x000Cu, (void *)&cyBle_attValues[378] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValues[390] }, /* ZERO_READING */
    { 0x000Cu, (void *)&cyBle_attValues[392] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[14] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[404] }, /* CAL_ZERO_ERROR */
    { 0x000Eu, (void *)&cyBle_attValues[405] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[16] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[419] }, /* CAL_STEP */
    { 0x0008u, (void *)&cyBle_attValues[420] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[18] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[428] }, /* CAL_SPEED */
    { 0x0009u, (void *)&cyBle_attValues[430] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[20] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[439] }, /* CAL_AS_FOUND */
    { 0x000Cu, (void *)&cyBle_attValues[440] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[22] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[452] }, /* CAL_ADJUSTED */
    { 0x000Cu, (void *)&cyBle_attValues[453] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[24] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[465] }, /* CAL_COUNTS */
    { 0x000Au, (void *)&cyBle_attValues[467] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[477] }, /* SENSOR_LIFE */
    { 0x000Bu, (void *)&cyBle_attValues[478] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[26] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[489] }, /* CAL_CLEARING */
    { 0x000Cu, (void *)&cyBle_attValues[491] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[28] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[503] }, /* CAL_SPAN_ERROR */
    { 0x000Eu, (void *)&cyBle_attValues[504] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[30] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[518] }, /* CALIBRATION_STATUS */
    { 0x0012u, (void *)&cyBle_attValues[519] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[32] }, /* Client Characteristic Configuration */
    { 0x0004u, (void *)&cyBle_attValues[537] }, /* READING_SCALED */
    { 0x000Eu, (void *)&cyBle_attValues[541] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[34] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[555] }, /* ALERT_STATUS */
    { 0x000Cu, (void *)&cyBle_attValues[556] }, /* Characteristic User Description */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[36] }, /* Client Characteristic Configuration */
};

const CYBLE_GATTS_DB_T cyBle_gattDB[0x99u] = {
    { 0x0001u, 0x2800u /* Primary service                     */, 0x00000001u /*           */, 0x000Bu, {{0x1800u, NULL}}                           },
    { 0x0002u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0003u, {{0x2A00u, NULL}}                           },
    { 0x0003u, 0x2A00u /* Device Name                         */, 0x01020001u /* rd        */, 0x0003u, {{0x000Eu, (void *)&cyBle_attValuesLen[0]}} },
    { 0x0004u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0005u, {{0x2A01u, NULL}}                           },
    { 0x0005u, 0x2A01u /* Appearance                          */, 0x01020001u /* rd        */, 0x0005u, {{0x0002u, (void *)&cyBle_attValuesLen[1]}} },
    { 0x0006u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0007u, {{0x2A04u, NULL}}                           },
    { 0x0007u, 0x2A04u /* Peripheral Preferred Connection Par */, 0x01020001u /* rd        */, 0x0007u, {{0x0008u, (void *)&cyBle_attValuesLen[2]}} },
    { 0x0008u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0009u, {{0x2AA6u, NULL}}                           },
    { 0x0009u, 0x2AA6u /* Central Address Resolution          */, 0x01020001u /* rd        */, 0x0009u, {{0x0001u, (void *)&cyBle_attValuesLen[3]}} },
    { 0x000Au, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x000Bu, {{0x2AC9u, NULL}}                           },
    { 0x000Bu, 0x2AC9u /* Resolvable Private Address Only     */, 0x01020001u /* rd        */, 0x000Bu, {{0x0001u, (void *)&cyBle_attValuesLen[4]}} },
    { 0x000Cu, 0x2800u /* Primary service                     */, 0x00000001u /*           */, 0x000Fu, {{0x1801u, NULL}}                           },
    { 0x000Du, 0x2803u /* Characteristic                      */, 0x00200001u /* ind       */, 0x000Fu, {{0x2A05u, NULL}}                           },
    { 0x000Eu, 0x2A05u /* Service Changed                     */, 0x01200000u /* ind       */, 0x000Fu, {{0x0004u, (void *)&cyBle_attValuesLen[5]}} },
    { 0x000Fu, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x000Fu, {{0x0002u, (void *)&cyBle_attValuesLen[6]}} },
    { 0x0010u, 0x2800u /* Primary service                     */, 0x00000001u /*           */, 0x0038u, {{0xB82Cu, NULL}}                           },
    { 0x0011u, 0x2803u /* Characteristic                      */, 0x001A0001u /* rd,wr,ntf */, 0x0014u, {{0x14A7u, NULL}}                           },
    { 0x0012u, 0x14A7u /* SYS_REMOTE                          */, 0x011A0101u /* rd,wr,ntf */, 0x0014u, {{0x0001u, (void *)&cyBle_attValuesLen[7]}} },
    { 0x0013u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0013u, {{0x000Au, (void *)&cyBle_attValuesLen[8]}} },
    { 0x0014u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0014u, {{0x0002u, (void *)&cyBle_attValuesLen[9]}} },
    { 0x0015u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x0018u, {{0x3EEBu, NULL}}                           },
    { 0x0016u, 0x3EEBu /* SYS_READING                         */, 0x01120001u /* rd,ntf    */, 0x0018u, {{0x0002u, (void *)&cyBle_attValuesLen[10]}} },
    { 0x0017u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0017u, {{0x000Bu, (void *)&cyBle_attValuesLen[11]}} },
    { 0x0018u, 0x2902u /* SYS_READING_CCCD                    */, 0x010A0101u /* rd,wr     */, 0x0018u, {{0x0002u, (void *)&cyBle_attValuesLen[12]}} },
    { 0x0019u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x001Cu, {{0x38C9u, NULL}}                           },
    { 0x001Au, 0x38C9u /* SYS_STATUS                          */, 0x01120001u /* rd,ntf    */, 0x001Cu, {{0x0002u, (void *)&cyBle_attValuesLen[13]}} },
    { 0x001Bu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x001Bu, {{0x000Au, (void *)&cyBle_attValuesLen[14]}} },
    { 0x001Cu, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x001Cu, {{0x0002u, (void *)&cyBle_attValuesLen[15]}} },
    { 0x001Du, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x001Fu, {{0xD515u, NULL}}                           },
    { 0x001Eu, 0xD515u /* SYS_CAN_CHAN                        */, 0x010A0101u /* rd,wr     */, 0x001Fu, {{0x0001u, (void *)&cyBle_attValuesLen[16]}} },
    { 0x001Fu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x001Fu, {{0x000Cu, (void *)&cyBle_attValuesLen[17]}} },
    { 0x0020u, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x0022u, {{0xF0E5u, NULL}}                           },
    { 0x0021u, 0xF0E5u /* SYS_CAN_ID                          */, 0x010A0101u /* rd,wr     */, 0x0022u, {{0x0001u, (void *)&cyBle_attValuesLen[18]}} },
    { 0x0022u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0022u, {{0x000Au, (void *)&cyBle_attValuesLen[19]}} },
    { 0x0023u, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x0025u, {{0x243Au, NULL}}                           },
    { 0x0024u, 0x243Au /* SYS_CAL_LOOP                        */, 0x010A0101u /* rd,wr     */, 0x0025u, {{0x0002u, (void *)&cyBle_attValuesLen[20]}} },
    { 0x0025u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0025u, {{0x000Cu, (void *)&cyBle_attValuesLen[21]}} },
    { 0x0026u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x0029u, {{0xD959u, NULL}}                           },
    { 0x0027u, 0xD959u /* SYS_ADC                             */, 0x01120001u /* rd,ntf    */, 0x0029u, {{0x0002u, (void *)&cyBle_attValuesLen[22]}} },
    { 0x0028u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0028u, {{0x0007u, (void *)&cyBle_attValuesLen[23]}} },
    { 0x0029u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0029u, {{0x0002u, (void *)&cyBle_attValuesLen[24]}} },
    { 0x002Au, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x002Cu, {{0x1C98u, NULL}}                           },
    { 0x002Bu, 0x1C98u /* SYS_ALERT_1                         */, 0x010A0101u /* rd,wr     */, 0x002Cu, {{0x0002u, (void *)&cyBle_attValuesLen[25]}} },
    { 0x002Cu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x002Cu, {{0x000Bu, (void *)&cyBle_attValuesLen[26]}} },
    { 0x002Du, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x002Fu, {{0x409Bu, NULL}}                           },
    { 0x002Eu, 0x409Bu /* SYS_ALERT_2                         */, 0x010A0101u /* rd,wr     */, 0x002Fu, {{0x0002u, (void *)&cyBle_attValuesLen[27]}} },
    { 0x002Fu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x002Fu, {{0x000Bu, (void *)&cyBle_attValuesLen[28]}} },
    { 0x0030u, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x0032u, {{0x7830u, NULL}}                           },
    { 0x0031u, 0x7830u /* SYS_ALERT_1_ASC                     */, 0x010A0101u /* rd,wr     */, 0x0032u, {{0x0002u, (void *)&cyBle_attValuesLen[29]}} },
    { 0x0032u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0032u, {{0x000Fu, (void *)&cyBle_attValuesLen[30]}} },
    { 0x0033u, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x0035u, {{0x85DDu, NULL}}                           },
    { 0x0034u, 0x85DDu /* SYS_ALERT_2_ASC                     */, 0x010A0101u /* rd,wr     */, 0x0035u, {{0x0002u, (void *)&cyBle_attValuesLen[31]}} },
    { 0x0035u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0035u, {{0x000Fu, (void *)&cyBle_attValuesLen[32]}} },
    { 0x0036u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0038u, {{0x805Fu, NULL}}                           },
    { 0x0037u, 0x805Fu /* SYS_FRACTIONAL                      */, 0x01020001u /* rd        */, 0x0038u, {{0x0002u, (void *)&cyBle_attValuesLen[33]}} },
    { 0x0038u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0038u, {{0x000Eu, (void *)&cyBle_attValuesLen[34]}} },
    { 0x0039u, 0x2800u /* Primary service                     */, 0x00000001u /*           */, 0x004Bu, {{0x180Au, NULL}}                           },
    { 0x003Au, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x003Bu, {{0x2A29u, NULL}}                           },
    { 0x003Bu, 0x2A29u /* Manufacturer Name String            */, 0x01020001u /* rd        */, 0x003Bu, {{0x0013u, (void *)&cyBle_attValuesLen[35]}} },
    { 0x003Cu, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x003Du, {{0x2A24u, NULL}}                           },
    { 0x003Du, 0x2A24u /* Model Number String                 */, 0x01020001u /* rd        */, 0x003Du, {{0x0006u, (void *)&cyBle_attValuesLen[36]}} },
    { 0x003Eu, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x003Fu, {{0x2A25u, NULL}}                           },
    { 0x003Fu, 0x2A25u /* Serial Number String                */, 0x01020001u /* rd        */, 0x003Fu, {{0x000Cu, (void *)&cyBle_attValuesLen[37]}} },
    { 0x0040u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0041u, {{0x2A27u, NULL}}                           },
    { 0x0041u, 0x2A27u /* Hardware Revision String            */, 0x01020001u /* rd        */, 0x0041u, {{0x0004u, (void *)&cyBle_attValuesLen[38]}} },
    { 0x0042u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0043u, {{0x2A26u, NULL}}                           },
    { 0x0043u, 0x2A26u /* Firmware Revision String            */, 0x01020001u /* rd        */, 0x0043u, {{0x0004u, (void *)&cyBle_attValuesLen[39]}} },
    { 0x0044u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0045u, {{0x2A28u, NULL}}                           },
    { 0x0045u, 0x2A28u /* Software Revision String            */, 0x01020001u /* rd        */, 0x0045u, {{0x0002u, (void *)&cyBle_attValuesLen[40]}} },
    { 0x0046u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0047u, {{0x2A23u, NULL}}                           },
    { 0x0047u, 0x2A23u /* System ID                           */, 0x01020001u /* rd        */, 0x0047u, {{0x0008u, (void *)&cyBle_attValuesLen[41]}} },
    { 0x0048u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0049u, {{0x2A2Au, NULL}}                           },
    { 0x0049u, 0x2A2Au /* IEEE 11073-20601 Regulatory Certifi */, 0x01020001u /* rd        */, 0x0049u, {{0x0001u, (void *)&cyBle_attValuesLen[42]}} },
    { 0x004Au, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x004Bu, {{0x2A50u, NULL}}                           },
    { 0x004Bu, 0x2A50u /* PnP ID                              */, 0x01020001u /* rd        */, 0x004Bu, {{0x0007u, (void *)&cyBle_attValuesLen[43]}} },
    { 0x004Cu, 0x2800u /* Primary service                     */, 0x00000001u /*           */, 0x0099u, {{0xE551u, NULL}}                           },
    { 0x004Du, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x004Fu, {{0x6051u, NULL}}                           },
    { 0x004Eu, 0x6051u /* PIN                                 */, 0x010A0101u /* rd,wr     */, 0x004Fu, {{0x0004u, (void *)&cyBle_attValuesLen[44]}} },
    { 0x004Fu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x004Fu, {{0x0003u, (void *)&cyBle_attValuesLen[45]}} },
    { 0x0050u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0052u, {{0x670Bu, NULL}}                           },
    { 0x0051u, 0x670Bu /* SENSOR_TYPE                         */, 0x01020001u /* rd        */, 0x0052u, {{0x0001u, (void *)&cyBle_attValuesLen[46]}} },
    { 0x0052u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0052u, {{0x000Bu, (void *)&cyBle_attValuesLen[47]}} },
    { 0x0053u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0055u, {{0xFDF7u, NULL}}                           },
    { 0x0054u, 0xFDF7u /* SENSOR_RANGE                        */, 0x01020001u /* rd        */, 0x0055u, {{0x0002u, (void *)&cyBle_attValuesLen[48]}} },
    { 0x0055u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0055u, {{0x000Cu, (void *)&cyBle_attValuesLen[49]}} },
    { 0x0056u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0058u, {{0x8547u, NULL}}                           },
    { 0x0057u, 0x8547u /* SENSOR_GAS_NOTE                     */, 0x01020001u /* rd        */, 0x0058u, {{0x000Au, (void *)&cyBle_attValuesLen[50]}} },
    { 0x0058u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0058u, {{0x000Fu, (void *)&cyBle_attValuesLen[51]}} },
    { 0x0059u, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x005Bu, {{0x32BDu, NULL}}                           },
    { 0x005Au, 0x32BDu /* SENSOR_TAG                          */, 0x010A0101u /* rd,wr     */, 0x005Bu, {{0x0013u, (void *)&cyBle_attValuesLen[52]}} },
    { 0x005Bu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x005Bu, {{0x000Au, (void *)&cyBle_attValuesLen[53]}} },
    { 0x005Cu, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x005Fu, {{0x4A4Cu, NULL}}                           },
    { 0x005Du, 0x4A4Cu /* SENSOR_TEMPERATURE                  */, 0x01120001u /* rd,ntf    */, 0x005Fu, {{0x0001u, (void *)&cyBle_attValuesLen[54]}} },
    { 0x005Eu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x005Eu, {{0x0012u, (void *)&cyBle_attValuesLen[55]}} },
    { 0x005Fu, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x005Fu, {{0x0002u, (void *)&cyBle_attValuesLen[56]}} },
    { 0x0060u, 0x2803u /* Characteristic                      */, 0x001A0001u /* rd,wr,ntf */, 0x0063u, {{0x645Du, NULL}}                           },
    { 0x0061u, 0x645Du /* SENSOR_CAL_LEVEL                    */, 0x011A0101u /* rd,wr,ntf */, 0x0063u, {{0x0002u, (void *)&cyBle_attValuesLen[57]}} },
    { 0x0062u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0062u, {{0x0010u, (void *)&cyBle_attValuesLen[58]}} },
    { 0x0063u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0063u, {{0x0002u, (void *)&cyBle_attValuesLen[59]}} },
    { 0x0064u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0066u, {{0xDFD6u, NULL}}                           },
    { 0x0065u, 0xDFD6u /* CAL_Z_COUNTS                        */, 0x01020001u /* rd        */, 0x0066u, {{0x0002u, (void *)&cyBle_attValuesLen[60]}} },
    { 0x0066u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0066u, {{0x000Cu, (void *)&cyBle_attValuesLen[61]}} },
    { 0x0067u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x006Au, {{0x7D4Fu, NULL}}                           },
    { 0x0068u, 0x7D4Fu /* ZERO_READING                        */, 0x01120001u /* rd,ntf    */, 0x006Au, {{0x0002u, (void *)&cyBle_attValuesLen[62]}} },
    { 0x0069u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0069u, {{0x000Cu, (void *)&cyBle_attValuesLen[63]}} },
    { 0x006Au, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x006Au, {{0x0002u, (void *)&cyBle_attValuesLen[64]}} },
    { 0x006Bu, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x006Eu, {{0x71ADu, NULL}}                           },
    { 0x006Cu, 0x71ADu /* CAL_ZERO_ERROR                      */, 0x01120001u /* rd,ntf    */, 0x006Eu, {{0x0001u, (void *)&cyBle_attValuesLen[65]}} },
    { 0x006Du, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x006Du, {{0x000Eu, (void *)&cyBle_attValuesLen[66]}} },
    { 0x006Eu, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x006Eu, {{0x0002u, (void *)&cyBle_attValuesLen[67]}} },
    { 0x006Fu, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x0072u, {{0xB354u, NULL}}                           },
    { 0x0070u, 0xB354u /* CAL_STEP                            */, 0x01120001u /* rd,ntf    */, 0x0072u, {{0x0001u, (void *)&cyBle_attValuesLen[68]}} },
    { 0x0071u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0071u, {{0x0008u, (void *)&cyBle_attValuesLen[69]}} },
    { 0x0072u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0072u, {{0x0002u, (void *)&cyBle_attValuesLen[70]}} },
    { 0x0073u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x0076u, {{0xEC95u, NULL}}                           },
    { 0x0074u, 0xEC95u /* CAL_SPEED                           */, 0x01120001u /* rd,ntf    */, 0x0076u, {{0x0002u, (void *)&cyBle_attValuesLen[71]}} },
    { 0x0075u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0075u, {{0x0009u, (void *)&cyBle_attValuesLen[72]}} },
    { 0x0076u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0076u, {{0x0002u, (void *)&cyBle_attValuesLen[73]}} },
    { 0x0077u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x007Au, {{0xB157u, NULL}}                           },
    { 0x0078u, 0xB157u /* CAL_AS_FOUND                        */, 0x01120001u /* rd,ntf    */, 0x007Au, {{0x0001u, (void *)&cyBle_attValuesLen[74]}} },
    { 0x0079u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0079u, {{0x000Cu, (void *)&cyBle_attValuesLen[75]}} },
    { 0x007Au, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x007Au, {{0x0002u, (void *)&cyBle_attValuesLen[76]}} },
    { 0x007Bu, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x007Eu, {{0x86F7u, NULL}}                           },
    { 0x007Cu, 0x86F7u /* CAL_ADJUSTED                        */, 0x01120001u /* rd,ntf    */, 0x007Eu, {{0x0001u, (void *)&cyBle_attValuesLen[77]}} },
    { 0x007Du, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x007Du, {{0x000Cu, (void *)&cyBle_attValuesLen[78]}} },
    { 0x007Eu, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x007Eu, {{0x0002u, (void *)&cyBle_attValuesLen[79]}} },
    { 0x007Fu, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0081u, {{0xE8EBu, NULL}}                           },
    { 0x0080u, 0xE8EBu /* CAL_COUNTS                          */, 0x01020001u /* rd        */, 0x0081u, {{0x0002u, (void *)&cyBle_attValuesLen[80]}} },
    { 0x0081u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0081u, {{0x000Au, (void *)&cyBle_attValuesLen[81]}} },
    { 0x0082u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x0085u, {{0x2EEFu, NULL}}                           },
    { 0x0083u, 0x2EEFu /* SENSOR_LIFE                         */, 0x01120001u /* rd,ntf    */, 0x0085u, {{0x0001u, (void *)&cyBle_attValuesLen[82]}} },
    { 0x0084u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0084u, {{0x000Bu, (void *)&cyBle_attValuesLen[83]}} },
    { 0x0085u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0085u, {{0x0002u, (void *)&cyBle_attValuesLen[84]}} },
    { 0x0086u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x0089u, {{0x1ECAu, NULL}}                           },
    { 0x0087u, 0x1ECAu /* CAL_CLEARING                        */, 0x01120001u /* rd,ntf    */, 0x0089u, {{0x0002u, (void *)&cyBle_attValuesLen[85]}} },
    { 0x0088u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0088u, {{0x000Cu, (void *)&cyBle_attValuesLen[86]}} },
    { 0x0089u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0089u, {{0x0002u, (void *)&cyBle_attValuesLen[87]}} },
    { 0x008Au, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x008Du, {{0x04B7u, NULL}}                           },
    { 0x008Bu, 0x04B7u /* CAL_SPAN_ERROR                      */, 0x01120001u /* rd,ntf    */, 0x008Du, {{0x0001u, (void *)&cyBle_attValuesLen[88]}} },
    { 0x008Cu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x008Cu, {{0x000Eu, (void *)&cyBle_attValuesLen[89]}} },
    { 0x008Du, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x008Du, {{0x0002u, (void *)&cyBle_attValuesLen[90]}} },
    { 0x008Eu, 0x2803u /* Characteristic                      */, 0x001A0001u /* rd,wr,ntf */, 0x0091u, {{0x276Du, NULL}}                           },
    { 0x008Fu, 0x276Du /* CALIBRATION_STATUS                  */, 0x011A0101u /* rd,wr,ntf */, 0x0091u, {{0x0001u, (void *)&cyBle_attValuesLen[91]}} },
    { 0x0090u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0090u, {{0x0012u, (void *)&cyBle_attValuesLen[92]}} },
    { 0x0091u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0091u, {{0x0002u, (void *)&cyBle_attValuesLen[93]}} },
    { 0x0092u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x0095u, {{0x1825u, NULL}}                           },
    { 0x0093u, 0x1825u /* READING_SCALED                      */, 0x01120001u /* rd,ntf    */, 0x0095u, {{0x0004u, (void *)&cyBle_attValuesLen[94]}} },
    { 0x0094u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0094u, {{0x000Eu, (void *)&cyBle_attValuesLen[95]}} },
    { 0x0095u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0095u, {{0x0002u, (void *)&cyBle_attValuesLen[96]}} },
    { 0x0096u, 0x2803u /* Characteristic                      */, 0x00120001u /* rd,ntf    */, 0x0099u, {{0x9150u, NULL}}                           },
    { 0x0097u, 0x9150u /* ALERT_STATUS                        */, 0x01120001u /* rd,ntf    */, 0x0099u, {{0x0001u, (void *)&cyBle_attValuesLen[97]}} },
    { 0x0098u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0098u, {{0x000Cu, (void *)&cyBle_attValuesLen[98]}} },
    { 0x0099u, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x0099u, {{0x0002u, (void *)&cyBle_attValuesLen[99]}} },
};


#endif /* (CYBLE_GATT_ROLE_SERVER) */

#if(CYBLE_GATT_ROLE_CLIENT)
    
CYBLE_CLIENT_STATE_T cyBle_clientState;
CYBLE_GATTC_T cyBle_gattc;
CYBLE_GATT_ATTR_HANDLE_RANGE_T cyBle_gattcDiscoveryRange;
    
#endif /* (CYBLE_GATT_ROLE_CLIENT) */


#if(CYBLE_GATT_ROLE_SERVER)

/****************************************************************************** 
* Function Name: CyBle_GattsReInitGattDb
***************************************************************************//**
* 
*  Reinitializes the GATT database.
* 
*  \return
*  CYBLE_API_RESULT_T: A function result states if it succeeded or failed with
*  error codes:

*  Errors codes                          | Description
*  ------------                          | -----------
*  CYBLE_ERROR_OK						 | GATT database was reinitialized successfully.
*  CYBLE_ERROR_INVALID_STATE             | If the function is called in any state except CYBLE_STATE_DISCONNECTED.
*  CYBLE_ERROR_INVALID_PARAMETER         | If the Database has zero entries or is a NULL pointer.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattsReInitGattDb(void)
{
    CYBLE_API_RESULT_T apiResult;
    
    if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
    {
        apiResult = CyBle_GattsDbRegister(cyBle_gattDB, CYBLE_GATT_DB_INDEX_COUNT, CYBLE_GATT_DB_MAX_VALUE_LEN);
    }
    else
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    
    return(apiResult);
}


/****************************************************************************** 
* Function Name: CyBle_GattsWriteEventHandler
***************************************************************************//**
* 
*  Handles the Write Request Event for GATT service.
* 
*  \param eventParam: The pointer to the data structure specified by the event.
* 
*  \return
*  CYBLE_GATT_ERR_CODE_T: A function returns one of the following status 
*  values.

*  Errors codes                          | Description
*  --------------------                  | -----------
*  CYBLE_GATT_ERR_NONE                   | Write is successful.
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_GattsWriteEventHandler(CYBLE_GATTS_WRITE_REQ_PARAM_T *eventParam)
{
    CYBLE_GATT_ERR_CODE_T gattErr = CYBLE_GATT_ERR_NONE;
    
    /* Client Characteristic Configuration descriptor write request */
    if(eventParam->handleValPair.attrHandle == cyBle_gatts.cccdHandle)
    {
        /* Store value to database */
        gattErr = CyBle_GattsWriteAttributeValue(&eventParam->handleValPair, 0u, 
                        &eventParam->connHandle, CYBLE_GATT_DB_PEER_INITIATED);
        
        if(gattErr == CYBLE_GATT_ERR_NONE)
        {
            if(CYBLE_IS_INDICATION_ENABLED_IN_PTR(eventParam->handleValPair.value.val))
            {
                CyBle_ApplCallback((uint32)CYBLE_EVT_GATTS_INDICATION_ENABLED, eventParam);
            }
            else
            {
                CyBle_ApplCallback((uint32)CYBLE_EVT_GATTS_INDICATION_DISABLED, eventParam);
            }
        }
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
    }
    return (gattErr);
}


#endif /* (CYBLE_GATT_ROLE_SERVER) */

#if(CYBLE_GATT_ROLE_CLIENT)

/****************************************************************************** 
* Function Name: CyBle_GattcStartDiscovery
***************************************************************************//**
* 
*  Starts the automatic server discovery process. 
*   
*   Discovery procedure is based on the user configuration. It discovers only services, characteristics, 
*   descriptors which were declared in the GATT database.
*   Discovery procedure has the following flow:
*   - discovering primary services by BLE Stack function CyBle_GattcDiscoverAllPrimaryServices();
*   - discovering included services by BLE Stack function CyBle_GattcFindIncludedServices();
*   - discovering characteristics for available services by BLE Stack function CyBle_GattcDiscoverAllCharacteristics();
*   - discovering characteristic descriptors by BLE Stack function CyBle_GattcDiscoverAllCharacteristicDescriptors();
*
*   During the discovery procedure the discovery-specific stack events are handled by the component 
*   and thus aren’t passed to the application callback: CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP,
*   CYBLE_EVT_GATTC_READ_BY_TYPE_RSP, CYBLE_EVT_GATTC_FIND_INFO_RSP, CYBLE_EVT_GATTC_ERROR_RSP.              
*   
*   After the discovery procedure all information about available services is stored in CYBLE_DISC_SRVC_INFO_T structures,
*   and discovered attributes handles are stored in service-specific client structures, such as CYBLE_BASC_T for 
*   Battery Service or CYBLE_HRSC_T for Heart Rate Service.
*
*  \param connHandle: The handle which consists of the device ID and ATT connection ID.
* 
*  \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*                        failed. Following are the possible error codes.
*
*   <table>	
*   <tr>
*	  <th>Errors codes</th>
*	  <th>Description</th>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_OK</td>
*	  <td>On successful operation</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*	  <td>'connHandle' value does not represent any existing entry.</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_OPERATION</td>
*	  <td>The operation is not permitted</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*	  <td>Memory allocation failed</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_INVALID_STATE</td>
*	  <td>If the function is called in any state except connected or discovered</td>
*	</tr>
*   </table>
*
*  \events
*   The following events may be generated after calling this function:
*   * CYBLE_EVT_GATTC_DISCOVERY_COMPLETE  - event is generated when the remote device was successfully discovered. 
*   * CYBLE_EVT_GATTC_ERROR_RSP  		- is generated if the device discovery has failed.
*   * CYBLE_EVT_GATTC_SRVC_DUPLICATION 	- is generated if duplicate service record was found during the server device
*        								  discovery.
*   * CYBLE_EVT_GATTC_CHAR_DUPLICATION 	- is generated if duplicate service's characteristic descriptor record was found
*        								  during the server device discovery.
*   * CYBLE_EVT_GATTC_DESCR_DUPLICATION - is generated if duplicate service's characteristic descriptor record was found
*        								  during the server device discovery.
*  
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcStartDiscovery(CYBLE_CONN_HANDLE_T connHandle)
{
    uint8 j;
    CYBLE_API_RESULT_T apiResult;
    
    if((CyBle_GetState() != CYBLE_STATE_CONNECTED) || 
       ((CyBle_GetClientState() != CYBLE_CLIENT_STATE_CONNECTED) && 
        (CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED))) 
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else
    {
        /* Clean old discovery information */
        for(j = 0u; j < (uint8) CYBLE_SRVI_COUNT; j++)
        {
            (void)memset(&cyBle_serverInfo[j].range, 0, sizeof(cyBle_serverInfo[0].range));
        }

        cyBle_connHandle = connHandle;
        cyBle_gattcDiscoveryRange.startHandle = CYBLE_GATT_ATTR_HANDLE_START_RANGE;
        cyBle_gattcDiscoveryRange.endHandle = CYBLE_GATT_ATTR_HANDLE_END_RANGE;
        
        CyBle_ServiceInit();
        
        apiResult = CyBle_GattcDiscoverAllPrimaryServices(connHandle);

        if(apiResult == CYBLE_ERROR_OK)
        {
            CyBle_SetClientState(CYBLE_CLIENT_STATE_SRVC_DISCOVERING);
            cyBle_eventHandlerFlag |= CYBLE_AUTO_DISCOVERY;
        }
    }
    
    return (apiResult);
}


/****************************************************************************** 
* Function Name: CyBle_GattcStartPartialDiscovery
***************************************************************************//**
* 
*  Starts the automatic server discovery process as per the range provided
*  on a GATT Server to which it is connected. This function could be used for 
*  partial server discovery after indication received to the Service Changed
*  Characteristic Value. 
* 
*  \param connHandle: The handle which consists of the device ID and ATT connection ID.
*  \param startHandle: Start of affected attribute handle range.
*  \param endHandle: End of affected attribute handle range.
* 
*  \return
*	CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*                        failed. Following are the possible error codes.
*
*   <table>	
*   <tr>
*	  <th>Errors codes</th>
*	  <th>Description</th>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_OK</td>
*	  <td>On successful operation</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*	  <td>'connHandle' value does not represent any existing entry.</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_OPERATION</td>
*	  <td>The operation is not permitted</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*	  <td>Memory allocation failed</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_INVALID_STATE</td>
*	  <td>If the function is called in any state except connected or discovered</td>
*	</tr>
*   </table>
* 
*  \events
*  Two events may be generated after calling this function:
*  CYBLE_EVT_GATTC_DISCOVERY_COMPLETE or CYBLE_EVT_GATTC_ERROR_RSP.
*  The CYBLE_EVT_GATTC_DISCOVERY_COMPLETE event is 
*  generated when the remote device was successfully discovered. The
*  CYBLE_EVT_GATTC_ERROR_RSP is generated if the device discovery is failed.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcStartPartialDiscovery(CYBLE_CONN_HANDLE_T connHandle,
                        CYBLE_GATT_DB_ATTR_HANDLE_T startHandle, CYBLE_GATT_DB_ATTR_HANDLE_T endHandle)
{
    uint8 j;
    CYBLE_API_RESULT_T apiResult;
    
    if((CyBle_GetState() != CYBLE_STATE_CONNECTED) || 
       ((CyBle_GetClientState() != CYBLE_CLIENT_STATE_CONNECTED) && 
        (CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED))) 
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else
    {
        /* Clean old discovery information of affected attribute range */
        for(j = 0u; j < (uint8) CYBLE_SRVI_COUNT; j++)
        {
            if((cyBle_serverInfo[j].range.startHandle >= startHandle) &&
               (cyBle_serverInfo[j].range.startHandle <= endHandle))
            {
                (void)memset(&cyBle_serverInfo[j].range, 0, sizeof(cyBle_serverInfo[0].range));
            }
        }

        cyBle_connHandle = connHandle;
        cyBle_gattcDiscoveryRange.startHandle = startHandle;
        cyBle_gattcDiscoveryRange.endHandle = endHandle;

        CyBle_ServiceInit();

        apiResult = CyBle_GattcDiscoverPrimaryServices(connHandle, &cyBle_gattcDiscoveryRange);

        if(apiResult == CYBLE_ERROR_OK)
        {
            CyBle_SetClientState(CYBLE_CLIENT_STATE_SRVC_DISCOVERING);
            cyBle_eventHandlerFlag |= CYBLE_AUTO_DISCOVERY;
        }
    }
    
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_GattcDiscoverCharacteristicsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a CYBLE_EVT_GATTC_READ_BY_TYPE_RSP
*  event. Based on the service UUID, an appropriate data structure is populated
*  using the data received as part of the callback.
* 
*  \param discCharInfo: The pointer to a characteristic information structure.
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_GattcDiscoverCharacteristicsEventHandler(CYBLE_DISC_CHAR_INFO_T *discCharInfo)
{
    if(discCharInfo->uuid.uuid16 == CYBLE_UUID_CHAR_SERVICE_CHANGED)
    {
        CyBle_CheckStoreCharHandle(cyBle_gattc.serviceChanged);
    }
}


/******************************************************************************
* Function Name: CyBle_GattcDiscoverCharDescriptorsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a "CYBLE_EVT_GATTC_FIND_INFO_RSP" event.
*  Based on the descriptor UUID, an appropriate data structure is populated 
*  using the data received as part of the callback.
* 
*  \param discDescrInfo: The pointer to a descriptor information structure.
*  \param discoveryService: The index of the service instance
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_GattcDiscoverCharDescriptorsEventHandler(CYBLE_DISC_DESCR_INFO_T *discDescrInfo)
{
    if(discDescrInfo->uuid.uuid16 == CYBLE_UUID_CHAR_CLIENT_CONFIG)
    {
        CyBle_CheckStoreCharDescrHandle(cyBle_gattc.cccdHandle);
    }
}


/******************************************************************************
* Function Name: CyBle_GattcIndicationEventHandler
***************************************************************************//**
* 
*  Handles the Indication Event.
* 
*  \param eventParam: The pointer to the data structure specified by the event.
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_GattcIndicationEventHandler(CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *eventParam)
{
    if(cyBle_gattc.serviceChanged.valueHandle == eventParam->handleValPair.attrHandle)
    {
        CyBle_ApplCallback((uint32)CYBLE_EVT_GATTC_INDICATION, eventParam);
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
    }
}


#endif /* (CYBLE_GATT_ROLE_CLIENT) */


/* [] END OF FILE */
