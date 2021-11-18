/*
 *	 	Created on: Nov 17, 2021
 *	 	Author: Mazen Talaat
 *		main.c
 */
#include "LED_Init.h"

void Delay(unsigned long);

int main(void)
{
	LED_Init(3);
    /* Loop forever */
	while(1){
		LED_On(3);
		Delay(200000);
		LED_Off(3);
		Delay(200000);
	}
	return 0;
}

void Delay(unsigned long ms){
	unsigned long i;
	for(i=0; i<ms; i++);
}
