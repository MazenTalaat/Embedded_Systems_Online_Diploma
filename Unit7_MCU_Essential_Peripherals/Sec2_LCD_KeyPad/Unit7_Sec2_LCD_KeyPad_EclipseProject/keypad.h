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
#include "gpio.h"
#include "common_macros.h"
#include "util/delay.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define KEYPAD_ROW_PORT PORTB_ID
#define KEYPAD_ROW_START_PIN PIN4_ID
#define KEYPAD_COL_PORT PORTD_ID
#define KEYPAD_COL_START_PIN PIN2_ID


/* 0 default keypad (Starts at 1)
 * 1 Eta32mini keypad/standard keypad (Starts at 7)
 */
#define KEYPAD_TYPE 1

#define KEYPAD_KEY_PRESSED LOGIC_LOW
#define KEYPAD_KEY_NOT_PRESSED LOGIC_HIGH

void KEYPAD_init(void);
uint8 KEYPAD_decoder(uint8 row, uint8 col);
uint8 KEYPAD_getPressedKey(void);

#endif
