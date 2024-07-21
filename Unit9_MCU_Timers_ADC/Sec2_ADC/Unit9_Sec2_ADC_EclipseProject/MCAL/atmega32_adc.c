//*****************************************************************************
//
// Module: ADC
//
// File Name: atmega32_adc.c
//
// Description: Source file for the ADC driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32_adc.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
ADC_Config ADC_g_config;
static uint16 ADC_g_result = 0;

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the ADC device.
// @param[in]  ADC_config 	The needed configuration.
void MCAL_ADC_init(ADC_Config *ADC_config) {
	ADC_g_config = *ADC_config;

	// Bit 7:6 – REFS1:0: Reference Selection Bits
	ADMUX = ADC_config->refVolatge;

	// Bit 7 – ADEN: ADC Enable
	// Bit 3 – ADIE: ADC Interrupt Enable
	// Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
	ADCSRA = (1 << ADEN) | ADC_config->clkSelect | ADC_g_config.IRQ_enable;
}

// @brief Reset the ADC.
void MCAL_ADC_deInit(void) {
	IRQ17_ADC_DISABLE;
	ADCSRA = 0;
	ADMUX = 0;
}

// @brief Reads the channel
// @param[in]  channelNum 	The input channel to read from.
// @return	   The digital value or TRUE(1) in case of using interrupt.
uint16 MCAL_ADC_readChannel(uint8 channelNum) {
	// Input channel number must be from 0 --> 7
	channelNum &= 0x07;

	// Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel
	ADMUX &= 0xE0;
	//  Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits
	ADMUX |= channelNum;

	// Start conversion write 1 to ADSC
	SET_BIT(ADCSRA, ADSC);

	if (ADC_g_config.IRQ_enable == ADC_IRQ_NONE) {
		// Wait for conversion to complete, ADIF becomes 1
		while (BIT_IS_CLEAR(ADCSRA, ADIF))
			;
		// Clear ADIF
		SET_BIT(ADCSRA, ADIF);

		// Read the digital value
		ADC_g_result = ADC;
		return ADC_g_result;
	} else {
		return TRUE;
	}

}

// @brief Reads the last digital value
// @return	   The last digital value.
uint16 MCAL_ADC_getResult(void) {
	return ADC_g_result;
}

//*****************************************************************************
// ISR Functions Definitions
//*****************************************************************************
ISR(ADC_vect) {
	ADC_g_result = ADC;
	if (ADC_g_config.P_IRQ_callBack) {
		ADC_g_config.P_IRQ_callBack(ADC_g_result);
	}
}
