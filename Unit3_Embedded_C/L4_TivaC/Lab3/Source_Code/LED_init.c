/*
 * 		Created on: Nov 17, 2021
 *      Author: Mazen Talaat
 *      LED_Init.c
 */

#include "LED_Init.h"

void LED_Init(int pin){
	volatile unsigned long delay_count;
	SYSCTL_RCGC2_R =   0x20;
	for(delay_count = 0; delay_count<200; delay_count++);
	GPIO_PORTF_DIR_R   |=   (1<<pin);
	GPIO_PORTF_DEN_R   |=   (1<<pin);
}

void LED_On(int pin){
    GPIO_PORTF_DATA_R |= (1<<pin);
}

void LED_Off(int pin){
	GPIO_PORTF_DATA_R &= ~(1<<pin);
}
