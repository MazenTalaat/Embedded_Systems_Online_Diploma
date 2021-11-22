/*
 * fifo.h
 *
 *  Created on: Nov 21, 2021
 *      Author: Mazen Talaat
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdint.h"

#define element_type uint8_t

/* Definitions */
typedef struct{
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_Buffer_t;

typedef enum{
	FIFO_No_Error,
	FIFO_Full,
	FIFO_Empty,
	FIFO_Null
}FIFO_Status;

/* APIs */
FIFO_Status FIFO_Init(FIFO_Buffer_t* FIFO_Buffer, element_type* Buffer, unsigned int length);
FIFO_Status FIFO_Enqueue(FIFO_Buffer_t* FIFO_Buffer, element_type item);
FIFO_Status FIFO_Dequeue(FIFO_Buffer_t* FIFO_Buffer, element_type* item);
FIFO_Status FIFO_Is_Full(FIFO_Buffer_t* FIFO_Buffer);
void FIFO_Print(FIFO_Buffer_t* FIFO_Buffer);

#endif /* FIFO_H_ */
