/*
 * main.c
 *
 *  Created on: Nov 21, 2021
 *      Author: Mazen Talaat
 */

#include "fifo.h"

/* Definitions */
/* UART Buffer Width */
#define UART_Width 5
element_type UART_Buffer[UART_Width];

int main(){
	FIFO_Buffer_t FIFO_UART;
	element_type i, temp=0;

	/* FIFO UART Initializing */
	if(FIFO_Init(&FIFO_UART, UART_Buffer, UART_Width) == FIFO_No_Error)
		printf("FIFO UART Init is done\n");

	/* Adding 7 elements */
	for(i=0; i<7; i++){
		printf("FIFO Enqueue: %x ", i);
		if(FIFO_Enqueue(&FIFO_UART, i) == FIFO_No_Error)
			printf("Done enqueue\n");
		else
			printf("Failed enqueue\n");
	}
	FIFO_Print(&FIFO_UART);

	/* Removing two elements */
	if(FIFO_Dequeue(&FIFO_UART, &temp) == FIFO_No_Error)
		printf("FIFO Dequeue: %x\n", temp);
	if(FIFO_Dequeue(&FIFO_UART, &temp) == FIFO_No_Error)
		printf("FIFO Dequeue: %x\n", temp);
	FIFO_Print(&FIFO_UART);

	/* Adding three elements */
	if(FIFO_Enqueue(&FIFO_UART, 9) == FIFO_No_Error){
		printf("FIFO Enqueue: %x ", 8);
		printf("Done enqueue\n");
	}
	if(FIFO_Enqueue(&FIFO_UART, 8) == FIFO_No_Error){
		printf("FIFO Enqueue: %x ", 8);
		printf("Done enqueue\n");
	}
	if(FIFO_Enqueue(&FIFO_UART, 7) == FIFO_No_Error){
		printf("FIFO Enqueue: %x ", 7);
		printf("Done enqueue\n");
	}
	else
		printf("Failed enqueue\n");

	FIFO_Print(&FIFO_UART);

	return 0;
}
