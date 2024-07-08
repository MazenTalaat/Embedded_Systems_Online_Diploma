 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Mazen Talaat
 *
 *******************************************************************************/

#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "lcd.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 8-bits.
 */
void LCD_init(void) {
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
#if LCD_BITS == 8
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
#elif LCD_BITS == 4
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+1, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+2, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+3, PIN_OUTPUT);
#endif
	_delay_ms(20); /* LCD Power ON delay always > 15ms */

#if LCD_BITS == 8
	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_EIGHT_BIT_TWO_LINES_5x7);

#elif LCD_BITS == 4
	LCD_sendCommand(LCD_FOUR_BIT_TWO_LINES_INIT1);
	LCD_sendCommand(LCD_FOUR_BIT_TWO_LINES_INIT2);
	LCD_sendCommand(LCD_FOUR_BIT_TWO_LINES_5x7);
#endif
	LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_DISPLAY); /* clear LCD at the beginning */
}

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command) {
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
#if LCD_BITS == 8
	GPIO_writePort(LCD_DATA_PORT_ID, command);
#elif LCD_BITS == 4
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID, GET_BIT(command, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+1, GET_BIT(command, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+2, GET_BIT(command, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+3, GET_BIT(command, 7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID, GET_BIT(command, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+1, GET_BIT(command, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+2, GET_BIT(command, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+3, GET_BIT(command, 3));
#endif
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data) {
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
#if LCD_BITS == 8
	GPIO_writePort(LCD_DATA_PORT_ID, data);
#elif LCD_BITS == 4
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID, GET_BIT(data, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+1, GET_BIT(data, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+2, GET_BIT(data, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+3, GET_BIT(data, 7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID, GET_BIT(data, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+1, GET_BIT(data, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+2, GET_BIT(data, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_START_PIN_ID+3, GET_BIT(data, 3));
#endif
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str) {
	uint8 i = 0;
	while (Str[i] != '\0') {
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row, uint8 col) {
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch (row) {
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = col + 0x40;
		break;
	case 2:
		lcd_memory_address = col + 0x10;
		break;
	case 3:
		lcd_memory_address = col + 0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str) {
	LCD_moveCursor(row, col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_shiftDisplayRight(void){
	LCD_sendCommand(LCD_SHIFT_ENTIRE_DISPLAY_RIGHT);
}

void LCD_shiftDisplayLeft(void){
	LCD_sendCommand(LCD_SHIFT_ENTIRE_DISPLAY_LEFT);
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data) {
	char buff[16]; /* String to hold the ascii result */
	itoa(data, buff, 10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 * Display the required float value on the screen
 */
void LCD_floatToString(float data) {
	int decimalValue = (int) data;
	int floatValue = (data - decimalValue) * 100;
	LCD_intgerToString(decimalValue);
	LCD_displayCharacter('.');
	LCD_intgerToString(floatValue);
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void) {
	LCD_sendCommand(LCD_CLEAR_DISPLAY); /* Send clear display command */
}
