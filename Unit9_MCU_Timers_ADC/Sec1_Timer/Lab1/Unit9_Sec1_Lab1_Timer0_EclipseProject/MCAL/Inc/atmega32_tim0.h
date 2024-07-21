//*****************************************************************************
//
// Module: TIM0
//
// File Name: atmega32_tim0.h
//
// Description: Header file for the TIM0 driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef ATMEGA32_TIM0_H_
#define ATMEGA32_TIM0_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32.h"
#include "avr/interrupt.h"
#include "std_types.h"
#include "common_macros.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct {
	uint8 mode;
	uint8 clkSelect;
	uint8 IRQ_enable;
	void (*P_IRQ_callBack)(void);		// Interrupt callback function.
} TIM0_Config;

//*****************************************************************************
// Definitions
//*****************************************************************************
// TIM0_mode_define
#define TIM0_MODE_NORMAL 				0
#define TIM0_MODE_CTC					(1<<WGM01)
#define TIM0_MODE_CTC_TOGGLE_OC0		(1<<COM00)
#define TIM0_MODE_CTC_CLEAR_OC0			(1<<COM01)
#define TIM0_MODE_CTC_SET_OC0			((1<<COM00) | (1<<COM01))

// TIM0_clkSelect_define
#define TIM0_CLK_SELECT_NONE			(0)
#define TIM0_CLK_SELECT_1				(1<<CS00)
#define TIM0_CLK_SELECT_8				(1<<CS01)
#define TIM0_CLK_SELECT_64				((1<<CS00) | (1<<CS01))
#define TIM0_CLK_SELECT_256				(1<<CS02)
#define TIM0_CLK_SELECT_1024			((1<<CS00) | (1<<CS02))
#define TIM0_CLK_SELECT_EXT_FALLING		((1<<CS01) | (1<<CS02))
#define TIM0_CLK_SELECT_EXT_RISING		((1<<CS00) | (1<<CS01) | (1<<CS02))

// TIM0_IRQ_enable_define
#define TIM0_IRQ_NONE					0
#define TIM0_IRQ_OUTPUT_COMPARE			(1<<TOIE0)
#define TIM0_IRQ_OVERFLOW				(1<<OCIE0)

//*****************************************************************************
// TIM0 APIs Prototypes
//*****************************************************************************
void MCAL_TIM0_init(TIM0_Config *TIM0_config);
void MCAL_TIM0_deInit(void);
void MCAL_TIM0_stop();

uint8 MCAL_TIM0_getFlagStatus(void);

uint8 MCAL_TIM0_getCompareValue(void);
void MCAL_TIM0_setCompareValue(uint8_t ticks);

uint8 MCAL_TIM0_getCounterValue(void);
void MCAL_TIM0_setCounterValue(uint8 ticks);

uint8 MCAL_TIM0_getOverflowCounter(void);
void MCAL_TIM0_setOverflowCounter(uint8 ticks);

#endif // ATMEGA32_TIM0_H_
