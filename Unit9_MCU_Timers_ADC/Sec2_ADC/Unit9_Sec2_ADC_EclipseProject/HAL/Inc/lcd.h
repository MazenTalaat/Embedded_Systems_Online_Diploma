//******************************************************************************
//
// Module: LCD
//
// File Name: lcd.h
//
// Description: Header file for the LCD driver
//
// Author: Mazen Talaat
//
//******************************************************************************
#ifndef LCD_H_
#define LCD_H_

//******************************************************************************
// Includes
//******************************************************************************
#include "std_types.h"
#include "atmega32_gpio.h"
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "stdlib.h"

//******************************************************************************
// Definitions 
//******************************************************************************
// User Configurable definitions
#define LCD_OUTPUT_PINS_MODE 		GPIO_MODE_OUT

#define LCD_BITS 4

// LCD HW Ports and Pins definitions
#define LCD_RS_PORT                 GPIOA
#define LCD_RS_PIN                  GPIO_PIN_1

#define LCD_E_PORT                  GPIOA
#define LCD_E_PIN                   GPIO_PIN_2

#define LCD_DATA_PORT               GPIOA
#define LCD_DATA_START_PIN          GPIO_PIN_3

// LCD Commands definitions
#define LCD_EIGHT_BIT_ONE_LINE_5x7             0x30
#define LCD_EIGHT_BIT_TWO_LINES_5x7            0x38
#define LCD_FOUR_BIT_ONE_LINE_5x7              0x20
#define LCD_FOUR_BIT_TWO_LINES_5x7             0x28
#define LCD_FOUR_BIT_TWO_LINES_INIT1    	   0x33
#define LCD_FOUR_BIT_TWO_LINES_INIT2    	   0x32
#define LCD_ENTRY_MODE                         0x06
#define LCD_DISPLAY_OFF_CURSOR_OFF             0x08
#define LCD_DISPLAY_ON_CURSOR_ON               0x0E
#define LCD_DISPLAY_ON_CURSOR_OFF              0x0C
#define LCD_DISPLAY_ON_CURSOR_BLINKING         0x0D
#define LCD_SHIFT_ENTIRE_DISPLAY_RIGHT         0x1C
#define LCD_SHIFT_ENTIRE_DISPLAY_LEFT          0x18
#define LCD_MOVE_CURSOR_LEFT_BY_ONE_CHARACTER  0x10
#define LCD_MOVE_CURSOR_RIGHT_BY_ONE_CHARACTER 0x14
#define LCD_CLEAR_DISPLAY                      0x01
#define LCD_SET_CURSOR_LOCATION                0x80

//******************************************************************************
// LCD APIs Prototypes
//******************************************************************************
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const uint8 *Str);
void LCD_moveCursor(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row, uint8 col, const uint8 *Str);
void LCD_shiftDisplayRight(void);
void LCD_shiftDisplayLeft(void);
void LCD_intgerToString(sint32 data);
void LCD_floatToString(float data);
void LCD_clearScreen(void);

#endif /* LCD_H_ */
