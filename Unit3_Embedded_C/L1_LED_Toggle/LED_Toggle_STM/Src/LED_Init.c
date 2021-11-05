/*
 * 		Created on: Nov 5, 2021
 *      Author: Mazen Talaat
 *      LED_Init.c
 */

#include "LED_Init.h"

void LED_Init(){
	RCC_APB2ENR |=   RCC_IOPAEN;
	GPIOA_CRH   &=~  CRH_Mode2;
	GPIOA_CRH   |=   CRH_Mode2;
}

void LED_On(int pin){
    GPIOA_ODR |= (1<<pin);
}

void LED_Off(int pin){
	GPIOA_ODR &= ~(1<<pin);
}
