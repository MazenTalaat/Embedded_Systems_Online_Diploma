//******************************************************************************
//
// Module: LM35
//
// File Name: lm35_sensor.c
//
// Description: Source file for the LM35 driver
//
// Author: Mazen Talaat
//
//******************************************************************************
//*****************************************************************************
// Includes
//*****************************************************************************
#include "lm35_sensor.h"

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief calculate the temperature from the ADC digital value.
// @return	   The temperature value.
uint8 LM35_getTemperature(void) {
	uint8 tempValue = 0;

	// Read ADC channel where the temperature sensor is connected
	MCAL_ADC_readChannel(LM35_SENSOR_CHANNEL_ID);

	// Make delay for some time until ADC value is updated in case of using the ADC interrupt
	_delay_ms(5);

	// Calculate the temperature from the ADC value
	tempValue = (uint8) (((uint32) MCAL_ADC_getResult()
			* LM35_SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE)
			/ (ADC_MAXIMUM_VALUE * LM35_SENSOR_MAX_VOLT_VALUE));

	return tempValue;
}

