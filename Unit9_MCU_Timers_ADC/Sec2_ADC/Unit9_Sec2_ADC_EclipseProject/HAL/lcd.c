//*****************************************************************************
//
// Module: LCD
//
// File Name: lcd.c
//
// Description: Source file for the LCD driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
//*****************************************************************************
// Includes
//*****************************************************************************
#include "lcd.h"

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the LCD:
// 1. Setup the LCD pins directions by use the GPIO driver.
// 2. Setup the LCD Data Mode 4-bits or 8-bits.
void LCD_init(void) {
	uint8 pinShift = 0;
	GPIO_PinConfig LCD_outputPinsConfig = { LCD_RS_PIN, LCD_OUTPUT_PINS_MODE };
	MCAL_GPIO_init(LCD_RS_PORT, &LCD_outputPinsConfig);

	LCD_outputPinsConfig.GPIO_pinNumber = LCD_E_PIN;
	MCAL_GPIO_init(LCD_E_PORT, &LCD_outputPinsConfig);

	for (pinShift = 0; pinShift < LCD_BITS; pinShift++) {
		LCD_outputPinsConfig.GPIO_pinNumber = (LCD_DATA_START_PIN << pinShift);
		MCAL_GPIO_init(LCD_DATA_PORT, &LCD_outputPinsConfig);
	}
	_delay_ms(20); // LCD Power ON delay always > 15ms 

#if LCD_BITS == 8
	// use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode 
	LCD_sendCommand(LCD_EIGHT_BIT_TWO_LINES_5x7);

#elif LCD_BITS == 4
	LCD_sendCommand(LCD_FOUR_BIT_TWO_LINES_INIT1);
	LCD_sendCommand(LCD_FOUR_BIT_TWO_LINES_INIT2);
	LCD_sendCommand(LCD_FOUR_BIT_TWO_LINES_5x7);
#endif
	LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_OFF); // cursor off 
	LCD_sendCommand(LCD_CLEAR_DISPLAY); // clear LCD at the beginning 
}

// @brief Send the required command to the screen
// @param[in]  command  The command to be sent.
void LCD_sendCommand(uint8 command) {
	MCAL_GPIO_writePin(LCD_RS_PORT, LCD_RS_PIN, LOGIC_LOW);
	_delay_ms(1);

	MCAL_GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);
	_delay_ms(1);
#if LCD_BITS == 8
	MCAL_GPIO_writePort(LCD_DATA_PORT, (MCAL_GPIO_readPort(LCD_DATA_PORT) & 0xFF00)| command);
#elif LCD_BITS == 4
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN, GET_BIT(command, 4));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 1,
			GET_BIT(command, 5));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 2,
			GET_BIT(command, 6));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 3,
			GET_BIT(command, 7));
	_delay_ms(1);
	MCAL_GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);
	_delay_ms(1);
	MCAL_GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);
	_delay_ms(1);
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN, GET_BIT(command, 0));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 1,
			GET_BIT(command, 1));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 2,
			GET_BIT(command, 2));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 3,
			GET_BIT(command, 3));
#endif
	_delay_ms(1);
	MCAL_GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);
	_delay_ms(1);
}

// @brief Display the required character on the screen
// @param[in]  data  The data to be sent. 
void LCD_displayCharacter(uint8 data) {
	MCAL_GPIO_writePin(LCD_RS_PORT, LCD_RS_PIN, LOGIC_HIGH);
	_delay_ms(1);

	MCAL_GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);
	_delay_ms(1);
#if LCD_BITS == 8
	MCAL_GPIO_writePort(LCD_DATA_PORT, (MCAL_GPIO_readPort(LCD_DATA_PORT) & 0xFF00)| data);
#elif LCD_BITS == 4
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN, GET_BIT(data, 4));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 1,
			GET_BIT(data, 5));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 2,
			GET_BIT(data, 6));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 3,
			GET_BIT(data, 7));
	_delay_ms(1);
	MCAL_GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);
	_delay_ms(1);
	MCAL_GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_HIGH);
	_delay_ms(1);
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN, GET_BIT(data, 0));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 1,
			GET_BIT(data, 1));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 2,
			GET_BIT(data, 2));
	MCAL_GPIO_writePin(LCD_DATA_PORT, LCD_DATA_START_PIN << 3,
			GET_BIT(data, 3));
#endif
	_delay_ms(1);
	MCAL_GPIO_writePin(LCD_E_PORT, LCD_E_PIN, LOGIC_LOW);
	_delay_ms(1);
}

// @brief Display the required string on the screen
// @param[in]  Str  The string to get displayed. 
void LCD_displayString(const uint8 *Str) {
	uint8 i = 0;
	while (Str[i] != '\0') {
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

// @brief Move the cursor to a specified row and column index on the screen
// @param[in]  row  The row index. 
// @param[in]  col  The column index. 
void LCD_moveCursor(uint8 row, uint8 col) {
	uint8 lcd_memory_address;

	// Calculate the required address in the LCD DDRAM 
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
	// Move the LCD cursor to this specific address 
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

// @brief Display the required string in a specified row and column index on the screen
// @param[in]  row  The row index. 
// @param[in]  col  The column index. 
// @param[in]  Str  The string to get displayed. 
void LCD_displayStringRowColumn(uint8 row, uint8 col, const uint8 *Str) {
	LCD_moveCursor(row, col); // go to to the required LCD position 
	LCD_displayString(Str); // display the string 
}

// @brief Shift display content to the right.
void LCD_shiftDisplayRight(void) {
	LCD_sendCommand(LCD_SHIFT_ENTIRE_DISPLAY_RIGHT);
}

// @brief Shift display content to the left.
void LCD_shiftDisplayLeft(void) {
	LCD_sendCommand(LCD_SHIFT_ENTIRE_DISPLAY_LEFT);
}

// @brief Display the required decimal value on the screen
// @param[in]  data  The int data to be displayed. 
void LCD_intgerToString(sint32 data) {
	uint8 buff[16]; // String to hold the ascii result 
	itoa(data, buff, 10); // Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal 
	LCD_displayString(buff); // Display the string 
}

// @brief Display the required float value on the screen
// @param[in]  data  The float data to be displayed. 
void LCD_floatToString(float data) {
	sint32 decimalValue = (sint32) data;
	sint32 floatValue = (data - decimalValue) * 100;
	LCD_intgerToString(decimalValue);
	LCD_displayCharacter('.');
	LCD_intgerToString(floatValue);
}

// @brief Send the clear screen command
void LCD_clearScreen(void) {
	LCD_sendCommand(LCD_CLEAR_DISPLAY); // Send clear display command 
}
