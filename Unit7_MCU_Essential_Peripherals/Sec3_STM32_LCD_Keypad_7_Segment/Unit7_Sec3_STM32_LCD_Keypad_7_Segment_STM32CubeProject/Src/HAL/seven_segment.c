/*
 * seven_segment.c
 *
 *  Created on: Jul 9, 2024
 *      Author: Mazen Talaat
 */

#include "seven_segment.h"

void SEVEN_SEGMENT_init(SEVEN_SEGMENT_Config *SEVEN_SEGMENT_config) {
	uint8 i = 0;
	GPIO_PinConfig pinConfig = { SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin,
	SEVEN_SEGMENT_OUTPUT_PINS_MODE };
	for (i = 0; i < 7; i++) {
		MCAL_GPIO_init(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port, &pinConfig);
		pinConfig.GPIO_pinNumber <<= 1;
	}
}

void SEVEN_SEGMENT_turnOff(SEVEN_SEGMENT_Config *SEVEN_SEGMENT_config) {
	uint8 i = 0;
	if (SEVEN_SEGMENT_config->SEVEN_SEGMENT_type == SEVEN_SEGMENT_TYPE_COM_AN) {
		for (i = 0; i < 7; i++) {
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << i,
					LOGIC_HIGH);
		}
	} else {
		for (i = 0; i < 7; i++) {
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << i,
					LOGIC_LOW);
		}
	}
}

void SEVEN_SEGMENT_display(SEVEN_SEGMENT_Config *SEVEN_SEGMENT_config,
		unsigned char value) {
	if (SEVEN_SEGMENT_config->SEVEN_SEGMENT_type == SEVEN_SEGMENT_TYPE_COM_AN) {
		switch (value) {
		case 0:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 1:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 2:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 3:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 4:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 5:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 6:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 7:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 8:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 9:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		}
	} else {
		switch (value) {
		case 0:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 1:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 2:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 3:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 4:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 5:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 6:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 7:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_LOW);
			break;
		case 8:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		case 9:
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 0,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 1,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 2,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 3,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 4,
					LOGIC_LOW);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 5,
					LOGIC_HIGH);
			MCAL_GPIO_writePin(SEVEN_SEGMENT_config->SEVEN_SEGMENT_port,
					SEVEN_SEGMENT_config->SEVEN_SEGMENT_startPin << 6,
					LOGIC_HIGH);
			break;
		}
	}
}
