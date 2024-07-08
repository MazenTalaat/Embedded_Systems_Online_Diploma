 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Mazen Talaat
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTA_ID
#define LCD_RS_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTA_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTA_ID
#define LCD_DATA_START_PIN_ID          PIN3_ID

#define LCD_BITS 4

/* LCD Commands */
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

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void);

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command);

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data);

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

void LCD_shiftDisplayRight(void);
void LCD_shiftDisplayLeft(void);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data);

/*
 * Description :
 * Display the required float value on the screen
 */
void LCD_floatToString(float data);

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
