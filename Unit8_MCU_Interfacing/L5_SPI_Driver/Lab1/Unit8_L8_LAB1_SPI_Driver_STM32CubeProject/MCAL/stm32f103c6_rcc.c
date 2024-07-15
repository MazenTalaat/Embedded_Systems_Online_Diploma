//*****************************************************************************
//
// Module: RCC
//
// File Name: stm32f103c6_rcc.c
//
// Description: Source file for the RCC driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c6_rcc.h"

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Read the system clock frequency.
// @return The system clock frequency value.
uint32 MCAL_RCC_getSysCLKFreq(void) {
//	Bits 3:2 SWS: System clock switch status
//	Set and cleared by hardware to indicate which clock source is used as system clock.
//	00: HSI oscillator used as system clock
//	01: HSE oscillator used as system clock
//	10: PLL used as system clock
//	11: not applicable
	switch ((RCC->CFGR >> 2 & 0b11)) {
	case 0b00:
		return HSI_CLOCK;
		break;
	case 0b01:
		return HSE_CLOCK;
		break;
	case 0b10:
		//TODO need to calculate  it PLLCLK and PLLMUL & PLL Source MUX
		return 16000000UL;
		break;
	default:
		return FALSE;
		break;
	}

}

// @brief Read the AHB clock frequency.
// @return The AHB clock frequency value.
uint32 MCAL_RCC_getHCLKFreq(void) {
	// Bits 7:4 HPRE: AHB prescaler
	return (MCAL_RCC_getSysCLKFreq()
			* (RCC_AHB_PRESCALER_MAPPING((RCC->CFGR>>4) & 0b1111)));
}

// @brief Read the APB1 clock frequency.
// @return The APB1 clock frequency value.
uint32 MCAL_RCC_getPCLK1Freq(void) {
	// Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	return (MCAL_RCC_getHCLKFreq()
			* (RCC_APB_PRESCALER_MAPPING((RCC->CFGR>>8) & 0b111)));
}

// @brief Read the APB2 clock frequency.
// @return The APB2 clock frequency value.
uint32 MCAL_RCC_getPCLK2Freq(void) {
	// Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	return (MCAL_RCC_getHCLKFreq()
			* (RCC_APB_PRESCALER_MAPPING((RCC->CFGR>>11) & 0b111)));
}
