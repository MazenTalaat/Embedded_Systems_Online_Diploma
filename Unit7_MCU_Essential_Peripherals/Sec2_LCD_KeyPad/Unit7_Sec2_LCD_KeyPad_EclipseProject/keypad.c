 /******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Mazen Talaat
 *
 *******************************************************************************/

#include "keypad.h"

void KEYPAD_init(void) {
	uint8 i;
	for (i = 0; i < KEYPAD_ROWS; i++) {
		GPIO_setupPinDirection(KEYPAD_ROW_PORT, KEYPAD_ROW_START_PIN + i,
				PIN_INPUT);
	}
	for (i = 0; i < KEYPAD_COLS; i++) {
		GPIO_setupPinDirection(KEYPAD_COL_PORT, KEYPAD_COL_START_PIN + i,
				PIN_INPUT);
	}
}

uint8 KEYPAD_decoder(uint8 row, uint8 col) {
#if KEYPAD_TYPE == 0
	if (row == KEYPAD_ROWS - 1) {
		switch (col) {
			case 0:
				return '*';
			case 1:
				return 0;
			case 2:
				return '#';
			default:
				return 0;
		}

	}
	return ((col) + 1 + (row) * KEYPAD_COLS);
#elif KEYPAD_TYPE == 1
	if (row == KEYPAD_ROWS - 1) {
		switch (col) {
		case 0:
			return '~';
		case 1:
			return 0;
		case 2:
			return '=';
		case 3:
			return '+';
		default:
			return 0;
		}
	} else if (col == KEYPAD_COLS - 1) {
		switch (row) {
		case 0:
			return '/';
		case 1:
			return '*';
		case 2:
			return '-';
		case 3:
			return '+';
		default:
			return 0;
		}
	}
	return ((col) + 7 + (row) * -3);
#else
	return 0;
#endif
}

uint8 KEYPAD_getPressedKey(void) {
	uint8 row, col;
	KEYPAD_init();
	while (1) {
		for (row = 0; row < KEYPAD_ROWS; row++) {
			GPIO_setupPinDirection(KEYPAD_ROW_PORT, KEYPAD_ROW_START_PIN + row,
					PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT, KEYPAD_ROW_START_PIN + row,
			KEYPAD_KEY_PRESSED);

			for (col = 0; col < KEYPAD_COLS; col++) {
				if (GPIO_readPin(KEYPAD_COL_PORT,
				KEYPAD_COL_START_PIN + col) == KEYPAD_KEY_PRESSED) {
					return KEYPAD_decoder(row, col);
				}
				_delay_ms(5);
			}

			GPIO_setupPinDirection(KEYPAD_ROW_PORT, KEYPAD_ROW_START_PIN + row,
					PIN_INPUT);
			_delay_ms(5);
		}
	}
}
