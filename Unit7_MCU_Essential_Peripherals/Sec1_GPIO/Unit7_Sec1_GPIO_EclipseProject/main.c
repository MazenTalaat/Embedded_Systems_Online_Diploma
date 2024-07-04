/*
 * main.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Mazen Talaat
 */

#include "util/delay.h"
#include "ATMEGA32.h"

#define F_CPU 8000000UL

#define SET_BIT(REG,BIT) (REG|=(0x1<<BIT))
#define CLEAR_BIT(REG,BIT) (REG&=~(0x1<<BIT))
#define READ_BIT(REG,BIT) ((REG>>BIT)&0x1)

int main(void) {
	/* Pushbutton 0,1,2 at D0, D1, D2 as input */
	DDRD &= ~(0x7);

	/* LEDs 1,2,3 negative logic at D5, D6, D7 as output */
	DDRD |= (0x7 << 5);
	/* Turn them off */
	PORTD &= ~(0x7 << 5);

	/* Buzzer at D4 */
	SET_BIT(DDRD, 4);
	CLEAR_BIT(PORTD, 4);

	/* 7 Segment Decoder at C4->C7 as output */
	DDRC |= (0xF << 4);
	/* Make them 0 */
	PORTD &= ~(0xF << 4);

	/* 7 Segments 1,2 common cathode at C2, C3 as output */
	DDRC |= (0x3 << 2);
	/* Turn them off */
	PORTC &= ~(0x3 << 2);

	/* Flags */
	uint8 LED_buttonPressed = 0;
	uint8 SEG_buttonPressed = 0;

	/* 7 Segment number */
	uint8 counter = 0;
	uint8 leftNumber = 0;
	uint8 rightNumber = 0;

	for (;;) {
		/* Pushbutton 0 pulled down at D0 pressed */
		if (READ_BIT(PIND, 0)) {
			/* Turn on buzzer */
			SET_BIT(PORTD, 4);
		} else if (!READ_BIT(PIND, 0)) {
			/* Turn off buzzer */
			CLEAR_BIT(PORTD, 4);
		}

		/* Pushbutton 1 pulled down at D1 pressed */
		if (READ_BIT(PIND, 1) && !LED_buttonPressed) {
			/* Toggle on LEDs */
			PORTD ^= (0x7 << 5);
			LED_buttonPressed = 1;
		} else if (!READ_BIT(PIND, 1)) {
			LED_buttonPressed = 0;
		}

		/* Pushbutton 2 pulled down at D2 pressed */
		if (READ_BIT(PIND, 2) && !SEG_buttonPressed) {
			/* Increment the counter to 99 then repeat */
			SEG_buttonPressed = 1;
			counter++;
			if (counter > 99) {
				counter = 0;
			}
			leftNumber = counter / 10;
			rightNumber = counter % 10;
		} else if (!READ_BIT(PIND, 2)) {
			SEG_buttonPressed = 0;
		}

		/* Switch between the 2 7 Segments to show the number */
		CLEAR_BIT(PORTC, 3);
		PORTC = ((PORTC & (~(0xF << 4))) | (rightNumber << 4));
		SET_BIT(PORTC, 2);
		_delay_ms(20);
		CLEAR_BIT(PORTC, 2);
		PORTC = ((PORTC & (~(0xF << 4))) | (leftNumber << 4));
		SET_BIT(PORTC, 3);
		_delay_ms(20);
	}
}

