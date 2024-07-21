//*****************************************************************************
//
// Module: TIM0
//
// File Name: atmega32_tim0.c
//
// Description: Source file for the TIM0 driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32_tim0.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
TIM0_Config TIM0_g_config;
static uint32 TIM0_g_overFlowCounter = 0;

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the TIM0 device.
// @param[in]  TIM0_config 	The needed configuration.
void MCAL_TIM0_init(TIM0_Config *TIM0_config) {
	TIM0_g_config = *TIM0_config;

	// Bit 7 – FOC0: Force Output Compare
	// Bit 6, 3 – WGM01:0: Waveform Generation Mode
	// Bit 5:4 – COM01:0: Compare Match Output Mode
	// Bit 2:0 – CS02:0: Clock Select
	TCCR0 = TIM0_config->mode | TIM0_config->clkSelect | (1 << FOC0);

	if (TIM0_config->IRQ_enable == TIM0_IRQ_OVERFLOW) {
		IRQ12_TIM0_OVF_ENABLE;
	} else {
		IRQ11_TIM0_COMP_ENABLE;
	}
}

// @brief Reset TIM0.
void MCAL_TIM0_deInit(void) {
	IRQ12_TIM0_OVF_DISABLE;
	IRQ11_TIM0_COMP_DISABLE;

	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
	TIFR &= ~((1 << OCF0) | (1 << TOV0));
}

// @brief Stops TIM0.
void MCAL_TIM0_stop() {
	// No clock source to stop the timer
	// the value below has 0b111 in Bit 2:0 – CS02:0: Clock Select
	TCCR0 &= ~(TIM0_CLK_SELECT_EXT_RISING);
}

// @brief Return the status of a flag.
// @return	   The value of flag status depending on mode.
uint8 MCAL_TIM0_getFlagStatus(void) {
	if (TIM0_g_config.mode == TIM0_MODE_NORMAL) {
		return GET_BIT(TIFR, TOV0);
	} else {
		return GET_BIT(TIFR, OCF0);
	}
}

// @brief Return the compare value.
// @return	   The value of OCR0 register.
uint8 MCAL_TIM0_getCompareValue(void) {
	return OCR0;
}

// @brief Sets the compare value.
// @param[in]  ticks 	The value of OCR0 register.
void MCAL_TIM0_setCompareValue(uint8_t ticks) {
	OCR0 = ticks;
}

// @brief Return the counter value.
// @return	   The value of TCNT0 register.
uint8 MCAL_TIM0_getCounterValue(void) {
	return TCNT0;
}

// @brief Sets the counter value.
// @param[in]  ticks 	The value of TCNT0 register.
void MCAL_TIM0_setCounterValue(uint8 ticks) {
	TCNT0 = ticks;
}

// @brief Return the overflow counter value.
// @return	   The value of OverflowCounter.
uint8 MCAL_TIM0_getOverflowCounter(void) {
	return TIM0_g_overFlowCounter;
}

// @brief Sets the overflow counter value.
// @param[in]  ticks 	The value of OverflowCounter.
void MCAL_TIM0_setOverflowCounter(uint8 ticks) {
	TIM0_g_overFlowCounter = ticks;
}

//*****************************************************************************
// ISR Functions Definitions
//*****************************************************************************
ISR(TIMER0_COMP_vect) {
	TIM0_g_config.P_IRQ_callBack();
}

ISR(TIMER0_OVF_vect) {
	TIM0_g_overFlowCounter++;
	TIM0_g_config.P_IRQ_callBack();
}
