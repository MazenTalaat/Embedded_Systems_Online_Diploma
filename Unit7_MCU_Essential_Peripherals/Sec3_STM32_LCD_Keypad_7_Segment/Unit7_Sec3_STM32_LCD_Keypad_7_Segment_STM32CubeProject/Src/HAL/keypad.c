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
#if KEYPAD_FULL_PORT == 1
	GPIO_PinConfig keysConfig = { KEYPAD_ROW_START_PIN, KEYPAD_INPUT_PINS_MODE };

	for (i = 0; i < KEYPAD_ROWS; i++) {
		keysConfig.GPIO_pinNumber <<= i;
		MCAL_GPIO_init(KEYPAD_ROW_PORT, &keysConfig);
	}
	keysConfig.GPIO_pinNumber = KEYPAD_COL_START_PIN;
	for (i = 0; i < KEYPAD_COLS; i++) {
		keysConfig.GPIO_pinNumber <<= i;
		MCAL_GPIO_init(KEYPAD_COL_PORT, &keysConfig);
	}
#else
	GPIO_TypeDef *keyRowPort[] = KEYPAD_ROW_PORT_ARRAY;
	uint16 keyRowPin[] = KEYPAD_ROW_PIN_ARRAY;

	GPIO_TypeDef *keyColPort[] = KEYPAD_COL_PORT_ARRAY;
	uint16 keyColPin[] = KEYPAD_COL_PIN_ARRAY;

	GPIO_PinConfig keysConfig = { keyRowPin[0], KEYPAD_INPUT_PINS_MODE };

	for (i = 0; i < KEYPAD_ROWS; i++) {
		keysConfig.GPIO_pinNumber = keyRowPin[i];
		MCAL_GPIO_init(keyRowPort[i], &keysConfig);
	}
	for (i = 0; i < KEYPAD_COLS; i++) {
		keysConfig.GPIO_pinNumber = keyColPin[i];
		MCAL_GPIO_init(keyColPort[i], &keysConfig);
	}
#endif
}

uint8 KEYPAD_getPressedKey(void) {
	uint8 row, col;
#if KEYPAD_FULL_PORT == 1
	GPIO_PinConfig keysConfigOutputReset = { KEYPAD_ROW_START_PIN,
	KEYPAD_OUTPUT_PINS_MODE };
	GPIO_PinConfig keysConfigInputReset = { KEYPAD_ROW_START_PIN,
	KEYPAD_INPUT_PINS_MODE };
	GPIO_PinConfig keysConfig;
	KEYPAD_init();
	while (1) {
		for (row = 0; row < KEYPAD_ROWS; row++) {
			keysConfig = keysConfigOutputReset;
			keysConfig.GPIO_pinNumber = KEYPAD_ROW_START_PIN << row;
			MCAL_GPIO_init(KEYPAD_ROW_PORT, &keysConfig);

			MCAL_GPIO_writePin(KEYPAD_ROW_PORT, keysConfig.GPIO_pinNumber,
			KEYPAD_KEY_PRESSED);
			for (col = 0; col < KEYPAD_COLS; col++) {
				if (MCAL_GPIO_readPin(KEYPAD_COL_PORT,
						KEYPAD_COL_START_PIN << col) == KEYPAD_KEY_PRESSED) {
					return KEYPAD_decoder(row, col);
				}
				_delay_ms(5);
			}
			keysConfig = keysConfigInputReset;
			keysConfig.GPIO_pinNumber = KEYPAD_ROW_START_PIN << row;
			MCAL_GPIO_init(KEYPAD_ROW_PORT, &keysConfig);
			_delay_ms(5);
		}
	}
#else
	GPIO_TypeDef *keyRowPort[] = KEYPAD_ROW_PORT_ARRAY;
	uint16 keyRowPin[] = KEYPAD_ROW_PIN_ARRAY;

	GPIO_TypeDef *keyColPort[] = KEYPAD_COL_PORT_ARRAY;
	uint16 keyColPin[] = KEYPAD_COL_PIN_ARRAY;

	GPIO_PinConfig keysConfigOutputReset = { keyRowPin[0],
	KEYPAD_OUTPUT_PINS_MODE };
	GPIO_PinConfig keysConfigInputReset = { keyRowPin[0],
	KEYPAD_INPUT_PINS_MODE };
	GPIO_PinConfig keysConfig;
	KEYPAD_init();

	while (1) {
			for (row = 0; row < KEYPAD_ROWS; row++) {
				keysConfig = keysConfigOutputReset;
				keysConfig.GPIO_pinNumber = keyRowPin[row];
				MCAL_GPIO_init(keyRowPort[row], &keysConfig);

				MCAL_GPIO_writePin(keyRowPort[row], keysConfig.GPIO_pinNumber,
				KEYPAD_KEY_PRESSED);
				for (col = 0; col < KEYPAD_COLS; col++) {
					if (MCAL_GPIO_readPin(keyColPort[col],
							keyColPin[col]) == KEYPAD_KEY_PRESSED) {
						return KEYPAD_decoder(row, col);
					}
					_delay_ms(5);
				}
				keysConfig = keysConfigInputReset;
				keysConfig.GPIO_pinNumber = keyRowPin[row];
				MCAL_GPIO_init(keyRowPort[row], &keysConfig);
				_delay_ms(5);
			}
		}
#endif
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
