//*****************************************************************************
//
// Module: ADC
//
// File Name: atmega32_adc.h
//
// Description: Header file for the ADC driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef ATMEGA32_ADC_H_
#define ATMEGA32_ADC_H_

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
	uint8 refVolatge;
	uint8 clkSelect;
	uint8 IRQ_enable;
	void (*P_IRQ_callBack)(uint16);		// Interrupt callback function.
} ADC_Config;

//*****************************************************************************
// Definitions
//*****************************************************************************
#define ADC_REF_VOLT_VALUE 			5
#define ADC_MAXIMUM_VALUE 			1023

// ADC_refVolatge_define
#define ADC_REF_VOLT_AREF			0
#define ADC_REF_VOLT_AVCC			(1<<REFS0)
#define ADC_REF_VOLT_2_56			((1<<REFS0) | (1<<REFS1))

// ADC_clkSelect_define
#define ADC_CLK_SELECT_2			(1<<ADPS0)
#define ADC_CLK_SELECT_4			(1<<ADPS1)
#define ADC_CLK_SELECT_8			((1<<ADPS0) | (1<<ADPS1))
#define ADC_CLK_SELECT_16			(1<<ADPS2)
#define ADC_CLK_SELECT_32			((1<<ADPS0) | (1<<ADPS2))
#define ADC_CLK_SELECT_64			((1<<ADPS1) | (1<<ADPS2))
#define ADC_CLK_SELECT_128			((1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2))

// ADC_IRQ_enable_define
#define ADC_IRQ_NONE				0
#define ADC_IRQ_ENABLE				(1<<ADIE)

//*****************************************************************************
// ADC APIs Prototypes
//*****************************************************************************
void MCAL_ADC_init(ADC_Config *ADC_config);
void MCAL_ADC_deInit(void);
uint16 MCAL_ADC_readChannel(uint8 channelNum);
uint16 MCAL_ADC_getResult(void);

#endif // ATMEGA32_ADC_H_
