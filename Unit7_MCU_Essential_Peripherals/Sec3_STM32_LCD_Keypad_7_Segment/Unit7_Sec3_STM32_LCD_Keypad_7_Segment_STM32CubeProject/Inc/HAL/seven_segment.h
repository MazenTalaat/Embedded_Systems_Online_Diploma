/*
 * seven_segment.h
 *
 *  Created on: Jul 9, 2024
 *      Author: Mazen Talaat
 */

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "stm32f103c6_gpio.h"
#include "std_types.h"

// SEVEN_SEGMENT_TYPE: 1 -> common anode, 0 -> common cathode
#define SEVEN_SEGMENT_TYPE_COM_CA 0
#define SEVEN_SEGMENT_TYPE_COM_AN 1

#define SEVEN_SEGMENT_OUTPUT_PINS_MODE GPIO_MODE_OUT_OPEN_DRAIN, GPIO_OUTPUT_SPEED_2MHZ

typedef struct {
	GPIO_TypeDef *SEVEN_SEGMENT_port;
	uint16 SEVEN_SEGMENT_startPin;
	uint8 SEVEN_SEGMENT_type;
} SEVEN_SEGMENT_Config;

void SEVEN_SEGMENT_init(SEVEN_SEGMENT_Config *SEVEN_SEGMENT_config);
void SEVEN_SEGMENT_turnOff(SEVEN_SEGMENT_Config *SEVEN_SEGMENT_config);
void SEVEN_SEGMENT_display(SEVEN_SEGMENT_Config *SEVEN_SEGMENT_config,
		unsigned char value);

#endif /* SEVEN_SEGMENT_H_ */
