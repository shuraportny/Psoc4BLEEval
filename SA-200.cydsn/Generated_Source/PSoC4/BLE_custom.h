/***************************************************************************//**
* \file CYBLE_custom.h
* \version 3.40
* 
* \brief
*  Contains the function prototypes and constants for the Custom Service.
* 
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BLE_CYBLE_CUSTOM_H)
#define CY_BLE_CYBLE_CUSTOM_H

#include "BLE_gatt.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Maximum supported Custom Services */
#define CYBLE_CUSTOMS_SERVICE_COUNT                  (0x02u)
#define CYBLE_CUSTOMC_SERVICE_COUNT                  (0x00u)
#define CYBLE_CUSTOM_SERVICE_CHAR_COUNT              (0x15u)
#define CYBLE_CUSTOM_SERVICE_CHAR_DESCRIPTORS_COUNT  (0x02u)

/* Below are the indexes and handles of the defined Custom Services and their characteristics */
#define CYBLE_SGA1_SERVICE_INDEX   (0x00u) /* Index of SGA1 service in the cyBle_customs array */
#define CYBLE_SGA1_SYS_REMOTE_CHAR_INDEX   (0x00u) /* Index of SYS_REMOTE characteristic */
#define CYBLE_SGA1_SYS_REMOTE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_REMOTE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA1_SYS_READING_CHAR_INDEX   (0x01u) /* Index of SYS_READING characteristic */
#define CYBLE_SGA1_SYS_READING_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_READING_SYS_READING_CCCD_DESC_INDEX   (0x01u) /* Index of SYS_READING_CCCD descriptor */
#define CYBLE_SGA1_SYS_STATUS_CHAR_INDEX   (0x02u) /* Index of SYS_STATUS characteristic */
#define CYBLE_SGA1_SYS_STATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA1_SYS_CAN_CHAN_CHAR_INDEX   (0x03u) /* Index of SYS_CAN_CHAN characteristic */
#define CYBLE_SGA1_SYS_CAN_CHAN_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_CAN_ID_CHAR_INDEX   (0x04u) /* Index of SYS_CAN_ID characteristic */
#define CYBLE_SGA1_SYS_CAN_ID_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_CAL_LOOP_CHAR_INDEX   (0x05u) /* Index of SYS_CAL_LOOP characteristic */
#define CYBLE_SGA1_SYS_CAL_LOOP_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ADC_CHAR_INDEX   (0x06u) /* Index of SYS_ADC characteristic */
#define CYBLE_SGA1_SYS_ADC_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ADC_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA1_SYS_ALERT_1_CHAR_INDEX   (0x07u) /* Index of SYS_ALERT_1 characteristic */
#define CYBLE_SGA1_SYS_ALERT_1_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ALERT_2_CHAR_INDEX   (0x08u) /* Index of SYS_ALERT_2 characteristic */
#define CYBLE_SGA1_SYS_ALERT_2_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ALERT_1_ASC_CHAR_INDEX   (0x09u) /* Index of SYS_ALERT_1_ASC characteristic */
#define CYBLE_SGA1_SYS_ALERT_1_ASC_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ALERT_2_ASC_CHAR_INDEX   (0x0Au) /* Index of SYS_ALERT_2_ASC characteristic */
#define CYBLE_SGA1_SYS_ALERT_2_ASC_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_FRACTIONAL_CHAR_INDEX   (0x0Bu) /* Index of SYS_FRACTIONAL characteristic */
#define CYBLE_SGA1_SYS_FRACTIONAL_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */

#define CYBLE_SGA2_SERVICE_INDEX   (0x01u) /* Index of SGA2 service in the cyBle_customs array */
#define CYBLE_SGA2_PIN_CHAR_INDEX   (0x00u) /* Index of PIN characteristic */
#define CYBLE_SGA2_PIN_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_TYPE_CHAR_INDEX   (0x01u) /* Index of SENSOR_TYPE characteristic */
#define CYBLE_SGA2_SENSOR_TYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_RANGE_CHAR_INDEX   (0x02u) /* Index of SENSOR_RANGE characteristic */
#define CYBLE_SGA2_SENSOR_RANGE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_GAS_NOTE_CHAR_INDEX   (0x03u) /* Index of SENSOR_GAS_NOTE characteristic */
#define CYBLE_SGA2_SENSOR_GAS_NOTE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_TAG_CHAR_INDEX   (0x04u) /* Index of SENSOR_TAG characteristic */
#define CYBLE_SGA2_SENSOR_TAG_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_TEMPERATURE_CHAR_INDEX   (0x05u) /* Index of SENSOR_TEMPERATURE characteristic */
#define CYBLE_SGA2_SENSOR_TEMPERATURE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_TEMPERATURE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_SENSOR_CAL_LEVEL_CHAR_INDEX   (0x06u) /* Index of SENSOR_CAL_LEVEL characteristic */
#define CYBLE_SGA2_SENSOR_CAL_LEVEL_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_CAL_LEVEL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_Z_COUNTS_CHAR_INDEX   (0x07u) /* Index of CAL_Z_COUNTS characteristic */
#define CYBLE_SGA2_CAL_Z_COUNTS_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_ZERO_READING_CHAR_INDEX   (0x08u) /* Index of ZERO_READING characteristic */
#define CYBLE_SGA2_ZERO_READING_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_ZERO_READING_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_ZERO_ERROR_CHAR_INDEX   (0x09u) /* Index of CAL_ZERO_ERROR characteristic */
#define CYBLE_SGA2_CAL_ZERO_ERROR_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_ZERO_ERROR_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_STEP_CHAR_INDEX   (0x0Au) /* Index of CAL_STEP characteristic */
#define CYBLE_SGA2_CAL_STEP_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_STEP_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_SPEED_CHAR_INDEX   (0x0Bu) /* Index of CAL_SPEED characteristic */
#define CYBLE_SGA2_CAL_SPEED_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_SPEED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_AS_FOUND_CHAR_INDEX   (0x0Cu) /* Index of CAL_AS_FOUND characteristic */
#define CYBLE_SGA2_CAL_AS_FOUND_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_AS_FOUND_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_ADJUSTED_CHAR_INDEX   (0x0Du) /* Index of CAL_ADJUSTED characteristic */
#define CYBLE_SGA2_CAL_ADJUSTED_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_ADJUSTED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_COUNTS_CHAR_INDEX   (0x0Eu) /* Index of CAL_COUNTS characteristic */
#define CYBLE_SGA2_CAL_COUNTS_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_LIFE_CHAR_INDEX   (0x0Fu) /* Index of SENSOR_LIFE characteristic */
#define CYBLE_SGA2_SENSOR_LIFE_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_LIFE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_CLEARING_CHAR_INDEX   (0x10u) /* Index of CAL_CLEARING characteristic */
#define CYBLE_SGA2_CAL_CLEARING_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_CLEARING_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_SPAN_ERROR_CHAR_INDEX   (0x11u) /* Index of CAL_SPAN_ERROR characteristic */
#define CYBLE_SGA2_CAL_SPAN_ERROR_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_SPAN_ERROR_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CALIBRATION_STATUS_CHAR_INDEX   (0x12u) /* Index of CALIBRATION_STATUS characteristic */
#define CYBLE_SGA2_CALIBRATION_STATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_CALIBRATION_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_READING_SCALED_CHAR_INDEX   (0x13u) /* Index of READING_SCALED characteristic */
#define CYBLE_SGA2_READING_SCALED_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_READING_SCALED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_ALERT_STATUS_CHAR_INDEX   (0x14u) /* Index of ALERT_STATUS characteristic */
#define CYBLE_SGA2_ALERT_STATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_INDEX   (0x00u) /* Index of Characteristic User Description descriptor */
#define CYBLE_SGA2_ALERT_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_INDEX   (0x01u) /* Index of Client Characteristic Configuration descriptor */


#define CYBLE_SGA1_SERVICE_HANDLE   (0x0010u) /* Handle of SGA1 service */
#define CYBLE_SGA1_SYS_REMOTE_DECL_HANDLE   (0x0011u) /* Handle of SYS_REMOTE characteristic declaration */
#define CYBLE_SGA1_SYS_REMOTE_CHAR_HANDLE   (0x0012u) /* Handle of SYS_REMOTE characteristic */
#define CYBLE_SGA1_SYS_REMOTE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0013u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_REMOTE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0014u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA1_SYS_READING_DECL_HANDLE   (0x0015u) /* Handle of SYS_READING characteristic declaration */
#define CYBLE_SGA1_SYS_READING_CHAR_HANDLE   (0x0016u) /* Handle of SYS_READING characteristic */
#define CYBLE_SGA1_SYS_READING_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0017u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_READING_SYS_READING_CCCD_DESC_HANDLE   (0x0018u) /* Handle of SYS_READING_CCCD descriptor */
#define CYBLE_SGA1_SYS_STATUS_DECL_HANDLE   (0x0019u) /* Handle of SYS_STATUS characteristic declaration */
#define CYBLE_SGA1_SYS_STATUS_CHAR_HANDLE   (0x001Au) /* Handle of SYS_STATUS characteristic */
#define CYBLE_SGA1_SYS_STATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x001Bu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x001Cu) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA1_SYS_CAN_CHAN_DECL_HANDLE   (0x001Du) /* Handle of SYS_CAN_CHAN characteristic declaration */
#define CYBLE_SGA1_SYS_CAN_CHAN_CHAR_HANDLE   (0x001Eu) /* Handle of SYS_CAN_CHAN characteristic */
#define CYBLE_SGA1_SYS_CAN_CHAN_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x001Fu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_CAN_ID_DECL_HANDLE   (0x0020u) /* Handle of SYS_CAN_ID characteristic declaration */
#define CYBLE_SGA1_SYS_CAN_ID_CHAR_HANDLE   (0x0021u) /* Handle of SYS_CAN_ID characteristic */
#define CYBLE_SGA1_SYS_CAN_ID_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0022u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_CAL_LOOP_DECL_HANDLE   (0x0023u) /* Handle of SYS_CAL_LOOP characteristic declaration */
#define CYBLE_SGA1_SYS_CAL_LOOP_CHAR_HANDLE   (0x0024u) /* Handle of SYS_CAL_LOOP characteristic */
#define CYBLE_SGA1_SYS_CAL_LOOP_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0025u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ADC_DECL_HANDLE   (0x0026u) /* Handle of SYS_ADC characteristic declaration */
#define CYBLE_SGA1_SYS_ADC_CHAR_HANDLE   (0x0027u) /* Handle of SYS_ADC characteristic */
#define CYBLE_SGA1_SYS_ADC_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0028u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ADC_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0029u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA1_SYS_ALERT_1_DECL_HANDLE   (0x002Au) /* Handle of SYS_ALERT_1 characteristic declaration */
#define CYBLE_SGA1_SYS_ALERT_1_CHAR_HANDLE   (0x002Bu) /* Handle of SYS_ALERT_1 characteristic */
#define CYBLE_SGA1_SYS_ALERT_1_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x002Cu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ALERT_2_DECL_HANDLE   (0x002Du) /* Handle of SYS_ALERT_2 characteristic declaration */
#define CYBLE_SGA1_SYS_ALERT_2_CHAR_HANDLE   (0x002Eu) /* Handle of SYS_ALERT_2 characteristic */
#define CYBLE_SGA1_SYS_ALERT_2_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x002Fu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ALERT_1_ASC_DECL_HANDLE   (0x0030u) /* Handle of SYS_ALERT_1_ASC characteristic declaration */
#define CYBLE_SGA1_SYS_ALERT_1_ASC_CHAR_HANDLE   (0x0031u) /* Handle of SYS_ALERT_1_ASC characteristic */
#define CYBLE_SGA1_SYS_ALERT_1_ASC_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0032u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_ALERT_2_ASC_DECL_HANDLE   (0x0033u) /* Handle of SYS_ALERT_2_ASC characteristic declaration */
#define CYBLE_SGA1_SYS_ALERT_2_ASC_CHAR_HANDLE   (0x0034u) /* Handle of SYS_ALERT_2_ASC characteristic */
#define CYBLE_SGA1_SYS_ALERT_2_ASC_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0035u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA1_SYS_FRACTIONAL_DECL_HANDLE   (0x0036u) /* Handle of SYS_FRACTIONAL characteristic declaration */
#define CYBLE_SGA1_SYS_FRACTIONAL_CHAR_HANDLE   (0x0037u) /* Handle of SYS_FRACTIONAL characteristic */
#define CYBLE_SGA1_SYS_FRACTIONAL_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0038u) /* Handle of Characteristic User Description descriptor */

#define CYBLE_SGA2_SERVICE_HANDLE   (0x004Cu) /* Handle of SGA2 service */
#define CYBLE_SGA2_PIN_DECL_HANDLE   (0x004Du) /* Handle of PIN characteristic declaration */
#define CYBLE_SGA2_PIN_CHAR_HANDLE   (0x004Eu) /* Handle of PIN characteristic */
#define CYBLE_SGA2_PIN_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x004Fu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_TYPE_DECL_HANDLE   (0x0050u) /* Handle of SENSOR_TYPE characteristic declaration */
#define CYBLE_SGA2_SENSOR_TYPE_CHAR_HANDLE   (0x0051u) /* Handle of SENSOR_TYPE characteristic */
#define CYBLE_SGA2_SENSOR_TYPE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0052u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_RANGE_DECL_HANDLE   (0x0053u) /* Handle of SENSOR_RANGE characteristic declaration */
#define CYBLE_SGA2_SENSOR_RANGE_CHAR_HANDLE   (0x0054u) /* Handle of SENSOR_RANGE characteristic */
#define CYBLE_SGA2_SENSOR_RANGE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0055u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_GAS_NOTE_DECL_HANDLE   (0x0056u) /* Handle of SENSOR_GAS_NOTE characteristic declaration */
#define CYBLE_SGA2_SENSOR_GAS_NOTE_CHAR_HANDLE   (0x0057u) /* Handle of SENSOR_GAS_NOTE characteristic */
#define CYBLE_SGA2_SENSOR_GAS_NOTE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0058u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_TAG_DECL_HANDLE   (0x0059u) /* Handle of SENSOR_TAG characteristic declaration */
#define CYBLE_SGA2_SENSOR_TAG_CHAR_HANDLE   (0x005Au) /* Handle of SENSOR_TAG characteristic */
#define CYBLE_SGA2_SENSOR_TAG_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x005Bu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_TEMPERATURE_DECL_HANDLE   (0x005Cu) /* Handle of SENSOR_TEMPERATURE characteristic declaration */
#define CYBLE_SGA2_SENSOR_TEMPERATURE_CHAR_HANDLE   (0x005Du) /* Handle of SENSOR_TEMPERATURE characteristic */
#define CYBLE_SGA2_SENSOR_TEMPERATURE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x005Eu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_TEMPERATURE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x005Fu) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_SENSOR_CAL_LEVEL_DECL_HANDLE   (0x0060u) /* Handle of SENSOR_CAL_LEVEL characteristic declaration */
#define CYBLE_SGA2_SENSOR_CAL_LEVEL_CHAR_HANDLE   (0x0061u) /* Handle of SENSOR_CAL_LEVEL characteristic */
#define CYBLE_SGA2_SENSOR_CAL_LEVEL_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0062u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_CAL_LEVEL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0063u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_Z_COUNTS_DECL_HANDLE   (0x0064u) /* Handle of CAL_Z_COUNTS characteristic declaration */
#define CYBLE_SGA2_CAL_Z_COUNTS_CHAR_HANDLE   (0x0065u) /* Handle of CAL_Z_COUNTS characteristic */
#define CYBLE_SGA2_CAL_Z_COUNTS_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0066u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_ZERO_READING_DECL_HANDLE   (0x0067u) /* Handle of ZERO_READING characteristic declaration */
#define CYBLE_SGA2_ZERO_READING_CHAR_HANDLE   (0x0068u) /* Handle of ZERO_READING characteristic */
#define CYBLE_SGA2_ZERO_READING_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0069u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_ZERO_READING_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x006Au) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_ZERO_ERROR_DECL_HANDLE   (0x006Bu) /* Handle of CAL_ZERO_ERROR characteristic declaration */
#define CYBLE_SGA2_CAL_ZERO_ERROR_CHAR_HANDLE   (0x006Cu) /* Handle of CAL_ZERO_ERROR characteristic */
#define CYBLE_SGA2_CAL_ZERO_ERROR_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x006Du) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_ZERO_ERROR_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x006Eu) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_STEP_DECL_HANDLE   (0x006Fu) /* Handle of CAL_STEP characteristic declaration */
#define CYBLE_SGA2_CAL_STEP_CHAR_HANDLE   (0x0070u) /* Handle of CAL_STEP characteristic */
#define CYBLE_SGA2_CAL_STEP_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0071u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_STEP_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0072u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_SPEED_DECL_HANDLE   (0x0073u) /* Handle of CAL_SPEED characteristic declaration */
#define CYBLE_SGA2_CAL_SPEED_CHAR_HANDLE   (0x0074u) /* Handle of CAL_SPEED characteristic */
#define CYBLE_SGA2_CAL_SPEED_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0075u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_SPEED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0076u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_AS_FOUND_DECL_HANDLE   (0x0077u) /* Handle of CAL_AS_FOUND characteristic declaration */
#define CYBLE_SGA2_CAL_AS_FOUND_CHAR_HANDLE   (0x0078u) /* Handle of CAL_AS_FOUND characteristic */
#define CYBLE_SGA2_CAL_AS_FOUND_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0079u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_AS_FOUND_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x007Au) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_ADJUSTED_DECL_HANDLE   (0x007Bu) /* Handle of CAL_ADJUSTED characteristic declaration */
#define CYBLE_SGA2_CAL_ADJUSTED_CHAR_HANDLE   (0x007Cu) /* Handle of CAL_ADJUSTED characteristic */
#define CYBLE_SGA2_CAL_ADJUSTED_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x007Du) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_ADJUSTED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x007Eu) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_COUNTS_DECL_HANDLE   (0x007Fu) /* Handle of CAL_COUNTS characteristic declaration */
#define CYBLE_SGA2_CAL_COUNTS_CHAR_HANDLE   (0x0080u) /* Handle of CAL_COUNTS characteristic */
#define CYBLE_SGA2_CAL_COUNTS_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0081u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_LIFE_DECL_HANDLE   (0x0082u) /* Handle of SENSOR_LIFE characteristic declaration */
#define CYBLE_SGA2_SENSOR_LIFE_CHAR_HANDLE   (0x0083u) /* Handle of SENSOR_LIFE characteristic */
#define CYBLE_SGA2_SENSOR_LIFE_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0084u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_SENSOR_LIFE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0085u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_CLEARING_DECL_HANDLE   (0x0086u) /* Handle of CAL_CLEARING characteristic declaration */
#define CYBLE_SGA2_CAL_CLEARING_CHAR_HANDLE   (0x0087u) /* Handle of CAL_CLEARING characteristic */
#define CYBLE_SGA2_CAL_CLEARING_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0088u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_CLEARING_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0089u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CAL_SPAN_ERROR_DECL_HANDLE   (0x008Au) /* Handle of CAL_SPAN_ERROR characteristic declaration */
#define CYBLE_SGA2_CAL_SPAN_ERROR_CHAR_HANDLE   (0x008Bu) /* Handle of CAL_SPAN_ERROR characteristic */
#define CYBLE_SGA2_CAL_SPAN_ERROR_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x008Cu) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_CAL_SPAN_ERROR_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x008Du) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_CALIBRATION_STATUS_DECL_HANDLE   (0x008Eu) /* Handle of CALIBRATION_STATUS characteristic declaration */
#define CYBLE_SGA2_CALIBRATION_STATUS_CHAR_HANDLE   (0x008Fu) /* Handle of CALIBRATION_STATUS characteristic */
#define CYBLE_SGA2_CALIBRATION_STATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0090u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_CALIBRATION_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0091u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_READING_SCALED_DECL_HANDLE   (0x0092u) /* Handle of READING_SCALED characteristic declaration */
#define CYBLE_SGA2_READING_SCALED_CHAR_HANDLE   (0x0093u) /* Handle of READING_SCALED characteristic */
#define CYBLE_SGA2_READING_SCALED_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0094u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_READING_SCALED_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0095u) /* Handle of Client Characteristic Configuration descriptor */
#define CYBLE_SGA2_ALERT_STATUS_DECL_HANDLE   (0x0096u) /* Handle of ALERT_STATUS characteristic declaration */
#define CYBLE_SGA2_ALERT_STATUS_CHAR_HANDLE   (0x0097u) /* Handle of ALERT_STATUS characteristic */
#define CYBLE_SGA2_ALERT_STATUS_CHARACTERISTIC_USER_DESCRIPTION_DESC_HANDLE   (0x0098u) /* Handle of Characteristic User Description descriptor */
#define CYBLE_SGA2_ALERT_STATUS_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE   (0x0099u) /* Handle of Client Characteristic Configuration descriptor */



#if(CYBLE_CUSTOMS_SERVICE_COUNT != 0u)
    #define CYBLE_CUSTOM_SERVER
#endif /* (CYBLE_CUSTOMS_SERVICE_COUNT != 0u) */
    
#if(CYBLE_CUSTOMC_SERVICE_COUNT != 0u)
    #define CYBLE_CUSTOM_CLIENT
#endif /* (CYBLE_CUSTOMC_SERVICE_COUNT != 0u) */

/***************************************
* Data Struct Definition
***************************************/

/**
 \addtogroup group_service_api_custom
 @{
*/

#ifdef CYBLE_CUSTOM_SERVER

/** Contains information about Custom Characteristic structure */
typedef struct
{
    /** Custom Characteristic handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServCharHandle;
    /** Custom Characteristic Descriptors handles */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServCharDesc[     /* MDK doesn't allow array with zero length */
        CYBLE_CUSTOM_SERVICE_CHAR_DESCRIPTORS_COUNT == 0u ? 1u : CYBLE_CUSTOM_SERVICE_CHAR_DESCRIPTORS_COUNT];
} CYBLE_CUSTOMS_INFO_T;

/** Structure with Custom Service attribute handles. */
typedef struct
{
    /** Handle of a Custom Service */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServHandle;
    
    /** Information about Custom Characteristics */
    CYBLE_CUSTOMS_INFO_T customServInfo[                /* MDK doesn't allow array with zero length */
        CYBLE_CUSTOM_SERVICE_CHAR_COUNT == 0u ? 1u : CYBLE_CUSTOM_SERVICE_CHAR_COUNT];
} CYBLE_CUSTOMS_T;


#endif /* (CYBLE_CUSTOM_SERVER) */

#ifdef CYBLE_CUSTOM_CLIENT

/** Structure with discovered attributes information of Custom Service Descriptors */
typedef struct
{
    /** Custom Descriptor handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T descHandle;
	/** Custom Descriptor 128 bit UUID */
	const void *uuid;           
    /** UUID Format - 16-bit (0x01) or 128-bit (0x02) */
	uint8 uuidFormat;
   
} CYBLE_CUSTOMC_DESC_T;

/** Structure with discovered attributes information of Custom Service Characteristics */
typedef struct
{
    /** Characteristic handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServCharHandle;
	/** Characteristic end handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServCharEndHandle;
	/** Custom Characteristic UUID */
	const void *uuid;           
    /** UUID Format - 16-bit (0x01) or 128-bit (0x02) */
	uint8 uuidFormat;
    /** Properties for value field */
    uint8  properties;
	/** Number of descriptors */
    uint8 descCount;
    /** Characteristic Descriptors */
    CYBLE_CUSTOMC_DESC_T * customServCharDesc;
} CYBLE_CUSTOMC_CHAR_T;

/** Structure with discovered attributes information of Custom Service */
typedef struct
{
    /** Custom Service handle */
    CYBLE_GATT_DB_ATTR_HANDLE_T customServHandle;
	/** Custom Service UUID */
	const void *uuid;           
    /** UUID Format - 16-bit (0x01) or 128-bit (0x02) */
	uint8 uuidFormat;
	/** Number of characteristics */
    uint8 charCount;
    /** Custom Service Characteristics */
    CYBLE_CUSTOMC_CHAR_T * customServChar;
} CYBLE_CUSTOMC_T;

#endif /* (CYBLE_CUSTOM_CLIENT) */


/***************************************
* External data references 
***************************************/

#ifdef CYBLE_CUSTOM_SERVER

/** Custom Services GATT DB handles structures */
extern const CYBLE_CUSTOMS_T cyBle_customs[CYBLE_CUSTOMS_SERVICE_COUNT];

#endif /* (CYBLE_CUSTOM_SERVER) */

#ifdef CYBLE_CUSTOM_CLIENT

/** Custom Services discovered attributes information */
extern CYBLE_CUSTOMC_T cyBle_customCServ[CYBLE_CUSTOMC_SERVICE_COUNT];

#endif /* (CYBLE_CUSTOM_CLIENT) */

/***************************************
* Private Function Prototypes
***************************************/

/** \cond IGNORE */
void CyBle_CustomInit(void);

#ifdef CYBLE_CUSTOM_CLIENT

void CyBle_CustomcDiscoverServiceEventHandler(const CYBLE_DISC_SRVC128_INFO_T *discServInfo);
void CyBle_CustomcDiscoverCharacteristicsEventHandler(uint16 discoveryService, const CYBLE_DISC_CHAR_INFO_T *discCharInfo);
CYBLE_GATT_ATTR_HANDLE_RANGE_T CyBle_CustomcGetCharRange(uint8 incrementIndex);
void CyBle_CustomcDiscoverCharDescriptorsEventHandler(const CYBLE_DISC_DESCR_INFO_T *discDescrInfo);

#endif /* (CYBLE_CUSTOM_CLIENT) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/
#define customServiceCharHandle         customServCharHandle
#define customServiceCharDescriptors    customServCharDesc
#define customServiceHandle             customServHandle
#define customServiceInfo               customServInfo
/** \endcond */

/** @} */

#endif /* CY_BLE_CYBLE_CUSTOM_H  */

/* [] END OF FILE */
