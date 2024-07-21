//*****************************************************************************
//
// Module: WDT
//
// File Name: atmega32_wdt.c
//
// Description: Source file for the WDT driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32_wdt.h"

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the WDT.
// @param[in]  time  Determine the Watch-dog Timer.
void MCAL_WDT_init(uint8 time) {
	WDTCR = time | (1 << WDE);
}

// @brief Reset the WDT.
void MCAL_WDT_deInit(void) {
	WDTCR = (1 << WDTOE) | (1 << WDE);
	WDTCR = 0x00;
}
