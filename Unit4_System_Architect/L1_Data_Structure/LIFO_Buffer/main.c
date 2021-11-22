/*
 * main.c
 *
 *  Created on: Nov 21, 2021
 *      Author: Mazen Talaat
 */

#include "lifo.h"

unsigned int Buffer1[5];

int main(){
	unsigned int i, temp=0;
	LIFO_Buffer_t UART_LIFO, I2C_LIFO;
	/* Static Allocation */
	LIFO_Init(&UART_LIFO, Buffer1, 5);
	/* Dynamic Allocation */
	unsigned int* Buffer2 = (unsigned int*) malloc(5*sizeof(unsigned int));
	LIFO_Init(&I2C_LIFO, Buffer2, 5);
	/* Adding 5 items */
	for(i=0; i<5; i++){
		LIFO_Add_Item(&UART_LIFO, i);
		printf("UART Added: %d\n", i);
	}
	/* Getting 5 items */
	for(i=0; i<5; i++){
		LIFO_Get_Item(&UART_LIFO, &temp);
		printf("UART Get: %d\n", temp);
	}
	return 0;
}
