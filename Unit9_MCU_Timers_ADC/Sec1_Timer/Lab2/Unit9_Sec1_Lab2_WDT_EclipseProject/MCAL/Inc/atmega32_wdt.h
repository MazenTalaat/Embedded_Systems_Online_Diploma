// Module: WDT
//
// File Name: atmega32_wdt.h
//
// Description: Header file for the WDT driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef ATMEGA32_WDT_H_
#define ATMEGA32_WDT_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32.h"
#include "std_types.h"

//*****************************************************************************
// Definitions
//*****************************************************************************
#define WDT_TIME_16_3ms     (0)
#define WDT_TIME_32_5ms     (1<<WDP0)

#define WDT_TIME_0_52s      ((1<<WDP0) | (1<<WDP2))
#define WDT_TIME_1s        	((1<<WDP1) | (1<<WDP2))
#define WDT_TIME_2_1s       ((1<<WDP0) | (1<<WDP1) | (1<<WDP2))

//*****************************************************************************
// GPIO APIs Prototypes
//*****************************************************************************
void MCAL_WDT_init(uint8 time);
void MCAL_WDT_deInit(void);

#endif // ATMEGA32_WDT_H_
