/*
 * delay.c
 *
 *  Created on: Jul 9, 2024
 *      Author: Mazen Talaat
 */

#include "delay.h"

void _delay_ms(uint32 ms) {
	volatile int i = 0, j = 0;
	for (i = 0; i < ms; ++i) {
		for (j = 0; j < 65; ++j) {

		}
	}
}
