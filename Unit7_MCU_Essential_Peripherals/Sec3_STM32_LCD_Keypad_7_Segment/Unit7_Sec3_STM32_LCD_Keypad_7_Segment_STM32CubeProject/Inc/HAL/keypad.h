 /******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mazen Talaat
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "common_macros.h"
#include "delay.h"
#include "stm32f103c6_gpio.h"


#define KEYPAD_OUTPUT_PINS_MODE GPIO_MODE_OUT_OPEN_DRAIN, GPIO_OUTPUT_SPEED_2MHZ
#define KEYPAD_INPUT_PINS_MODE 	GPIO_MODE_IN_FLOATING

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define KEYPAD_FULL_PORT 0

#if KEYPAD_FULL_PORT == 1
#define KEYPAD_ROW_PORT GPIOB
#define KEYPAD_ROW_START_PIN GPIO_PIN_0
#define KEYPAD_COL_PORT GPIOB
#define KEYPAD_COL_START_PIN GPIO_PIN_5

#else
#define KEYPAD_ROW1_PORT GPIOB
#define KEYPAD_ROW1_PIN GPIO_PIN_0

#define KEYPAD_ROW2_PORT GPIOB
#define KEYPAD_ROW2_PIN GPIO_PIN_1

#define KEYPAD_ROW3_PORT GPIOB
#define KEYPAD_ROW3_PIN GPIO_PIN_3

#if KEYPAD_ROWS == 3

#define KEYPAD_ROW_PORT_ARRAY 	{ KEYPAD_ROW1_PORT, KEYPAD_ROW2_PORT, KEYPAD_ROW3_PORT }
#define KEYPAD_ROW_PIN_ARRAY 	{ KEYPAD_ROW1_PIN, KEYPAD_ROW2_PIN, KEYPAD_ROW3_PIN }

#elif KEYPAD_ROWS == 4
#define KEYPAD_ROW4_PORT GPIOB
#define KEYPAD_ROW4_PIN GPIO_PIN_4

#define KEYPAD_ROW_PORT_ARRAY 	{ KEYPAD_ROW1_PORT, KEYPAD_ROW2_PORT, KEYPAD_ROW3_PORT, KEYPAD_ROW4_PORT }
#define KEYPAD_ROW_PIN_ARRAY 	{ KEYPAD_ROW1_PIN, KEYPAD_ROW2_PIN, KEYPAD_ROW3_PIN, KEYPAD_ROW4_PIN }
#endif

#define KEYPAD_COL1_PORT GPIOB
#define KEYPAD_COL1_PIN GPIO_PIN_5

#define KEYPAD_COL2_PORT GPIOB
#define KEYPAD_COL2_PIN GPIO_PIN_6

#define KEYPAD_COL3_PORT GPIOB
#define KEYPAD_COL3_PIN GPIO_PIN_7

#if KEYPAD_ROWS == 3

#define KEYPAD_COL_PORT_ARRAY 	{ KEYPAD_COL1_PORT, KEYPAD_COL2_PORT, KEYPAD_COL3_PORT }
#define KEYPAD_COL_PIN_ARRAY 	{ KEYPAD_COL1_PIN, KEYPAD_COL2_PIN, KEYPAD_COL3_PIN }

#elif KEYPAD_ROWS == 4
#define KEYPAD_COL4_PORT GPIOB
#define KEYPAD_COL4_PIN GPIO_PIN_8

#define KEYPAD_COL_PORT_ARRAY 	{ KEYPAD_COL1_PORT, KEYPAD_COL2_PORT, KEYPAD_COL3_PORT, KEYPAD_COL4_PORT }
#define KEYPAD_COL_PIN_ARRAY 	{ KEYPAD_COL1_PIN, KEYPAD_COL2_PIN, KEYPAD_COL3_PIN, KEYPAD_COL4_PIN }
#endif

#endif

/* 0 default keypad (Starts at 1)
 * 1 Eta32mini keypad/standard keypad (Starts at 7)
 */
#define KEYPAD_TYPE 1

#define KEYPAD_KEY_PRESSED LOGIC_LOW
#define KEYPAD_KEY_NOT_PRESSED LOGIC_HIGH

void KEYPAD_init(void);
uint8 KEYPAD_getPressedKey(void);
uint8 KEYPAD_decoder(uint8 row, uint8 col);

#endif
