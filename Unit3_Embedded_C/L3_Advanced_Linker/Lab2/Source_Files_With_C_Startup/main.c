/*
 *	 	Created on: Nov 5, 2021
 *	 	Author: Mazen Talaat
 *		main.c
 */
#include "LED_Init.h"

void Delay(int);

int main(void)
{
	LED_Init();
    /* Loop forever */
	while(1){
		LED_On(13);
		Delay(5000);
		LED_Off(13);
		Delay(5000);
	}
	return 0;
}

void Delay(int ms){
	int i;
	for(i=0; i<ms; i++);
}
