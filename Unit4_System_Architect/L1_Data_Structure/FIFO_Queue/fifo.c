/*
 * fifo.c
 *
 *  Created on: Nov 21, 2021
 *      Author: Mazen Talaat
 */

#include "fifo.h"

FIFO_Status FIFO_Init(FIFO_Buffer_t* FIFO_Buffer, element_type* Buffer, unsigned int length){
	/* Check location is valid */
	if (Buffer == NULL)
		return FIFO_Null;

	/* Initializing */
	FIFO_Buffer->base= Buffer;
	FIFO_Buffer->head= Buffer;
	FIFO_Buffer->tail= Buffer;
	FIFO_Buffer->count=0;
	FIFO_Buffer->length=length;

	return FIFO_No_Error;
}

FIFO_Status FIFO_Enqueue(FIFO_Buffer_t* FIFO_Buffer, element_type item){
	/* Check FIFO is valid */
	if (!FIFO_Buffer->base || !FIFO_Buffer->head || !FIFO_Buffer->tail)
		return FIFO_Null;
	if (FIFO_Is_Full(FIFO_Buffer) == FIFO_Full)
		return FIFO_Full;

	/* Adding item */
	*(FIFO_Buffer->head) = item;
	FIFO_Buffer->count++;

	/* Making head circular */
	if(FIFO_Buffer->head == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type))))
		FIFO_Buffer->head = FIFO_Buffer->base;
	else
		FIFO_Buffer->head++;

	return FIFO_No_Error;
}

FIFO_Status FIFO_Dequeue(FIFO_Buffer_t* FIFO_Buffer, element_type* item){
	/* Check FIFO is valid */
	if (!FIFO_Buffer->base || !FIFO_Buffer->head || !FIFO_Buffer->tail)
		return FIFO_Null;

	/* Check FIFO is empty */
	if (FIFO_Buffer->count == 0)
		return FIFO_Empty;

	/* Getting item */
	*item = *(FIFO_Buffer->tail);
	FIFO_Buffer->count--;

	/* Making tail circular */
	if(FIFO_Buffer->tail == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type))))
		FIFO_Buffer->tail = FIFO_Buffer->base;
	else
		FIFO_Buffer->tail++;

	return FIFO_No_Error;
}

FIFO_Status FIFO_Is_Full(FIFO_Buffer_t* FIFO_Buffer){
	/* Check FIFO is valid */
	if (!FIFO_Buffer->base || !FIFO_Buffer->head || !FIFO_Buffer->tail)
		return FIFO_Null;

	/* Check FIFO is Full */
	if (FIFO_Buffer->count >= FIFO_Buffer->length){
		printf("FIFO Is Full ");
		return FIFO_Full;
	}

	return FIFO_No_Error;
}

void FIFO_Print(FIFO_Buffer_t* FIFO_Buffer){
	element_type* temp;
	int i;
	/* Check FIFO is Full */
	if(FIFO_Buffer->count == 0)
		printf("FIFO is empty\n");
	else{
		temp = FIFO_Buffer->tail;
		printf("\nFIFO Printing\n");
		for(i=0; i<FIFO_Buffer->count; i++){
			printf("%x\n", *temp);

			/* Making temp circular */
			if(temp == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type))))
				temp = FIFO_Buffer->base;
			else
				temp++;
		}
	}
	printf("\n");
}
