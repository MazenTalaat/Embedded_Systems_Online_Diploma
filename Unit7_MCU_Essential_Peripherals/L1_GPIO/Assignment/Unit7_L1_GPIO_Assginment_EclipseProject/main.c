/*
 * main.c
 *
 *  Created on: Jun 27, 2024
 *      Author: Mazen Talaat
 */

//#include "avr/io.h"

typedef unsigned char uint8_t;

#define DDRD *(volatile uint8_t*)0x31
#define PORTD *(volatile uint8_t*)0x32

typedef enum {
	LED_RED, LED_GREEN, LED_BLUE, Buzzer
} deviceToOperate;

void delay(unsigned long n) {
	unsigned long i;
	for (i = 0; i < n; ++i)
		;
}

int main(void) {
	deviceToOperate currentDevice = LED_RED;
	/* Configure PD4->PD7 as output */
	DDRD |= (0xF << 4);

	/* Turn them off */
	PORTD |= (0xE << 4);

	for (;;) {
		switch (currentDevice) {
		case LED_RED:
			PORTD ^= (1 << 5);
			delay(10000);
			PORTD ^= (1 << 5);
			break;
		case LED_GREEN:
			PORTD ^= (1 << 6);
			delay(10000);
			PORTD ^= (1 << 6);
			break;
		case LED_BLUE:
			PORTD ^= (1 << 7);
			delay(10000);
			PORTD ^= (1 << 7);
			break;
		case Buzzer:
			PORTD ^= (1 << 4);
			delay(10000);
			PORTD ^= (1 << 4);
			break;
		}
		currentDevice++;
		if (currentDevice > Buzzer) {
			currentDevice = LED_RED;
		}
	}
}
