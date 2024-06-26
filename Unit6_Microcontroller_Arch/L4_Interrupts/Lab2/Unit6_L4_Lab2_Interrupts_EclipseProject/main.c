/*
 * main.c
 *
 *  Created on: Jun 26, 2024
 *      Author: Mazen Talaat
 */

#include "avr/io.h"
#include "avr/interrupt.h"
#include "util/delay.h"

typedef enum {
	NoLED, LED_RED, LED_GREEN, LED_BLUE
} LED_ToToggle;

LED_ToToggle currentLED = NoLED;

int main(void) {
	/* Pins D2, D3 B2 as Inputs */
	DDRD &= ~((1 << PD2) | (1 << PD3));
	DDRB &= ~(1 << PB2);

	/* Pins D7,D6,D5 as output */
	DDRD |= ((1 << PD7) | (1 << PD6) | (1 << PD5));

	/* INT0 any logical change */
	/* ISC01=0 ISC00=1 Any logical change on INT0 generates an interrupt request. */
	MCUCR |= (1 << ISC00);

	/* INT1 rising edge */
	/* ISC11=1 ISC10=1 The rising edge of INT1 generates an interrupt request. */
	MCUCR |= ((1 << ISC11) | (1 << ISC10));

	/* INT2 failing edge */
	/* If ISC2 is written to zero, a falling edge on INT2 activates the interrupt.  */
	MCUCSR &=~(1<<ISC2); //falling edge

	/* Enable External Interrupt Requests */
	GICR |= ((1 << INT0) | (1 << INT1) | (1 << INT2));

	/* Enable I bit */
	SREG |= (1<<7);

	for (;;) {
		switch (currentLED) {
		case LED_RED:
			PORTD |= (1 << PD7);
			_delay_ms(1000);
			PORTD &= ~(1 << PD7);
			currentLED = NoLED;
			break;
		case LED_GREEN:
			PORTD |= (1 << PD6);
			_delay_ms(1000);
			PORTD &= ~(1 << PD6);
			currentLED = NoLED;
			break;
		case LED_BLUE:
			PORTD |= (1 << PD5);
			_delay_ms(1000);
			PORTD &= ~(1 << PD5);
			currentLED = NoLED;
			break;
		default:
			break;
		}
	}
}

ISR(INT0_vect) {
	currentLED = LED_RED;
}

ISR(INT1_vect) {
	currentLED = LED_GREEN;
}

ISR(INT2_vect) {
	currentLED = LED_BLUE;
}
