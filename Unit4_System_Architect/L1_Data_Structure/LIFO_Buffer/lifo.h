/*
 * lifo.h
 *
 *  Created on: Nov 21, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"
#include "stdlib.h"

#ifndef LIFO_H_
#define LIFO_H_

/* Definitions */
typedef struct{
	unsigned int length;
	unsigned int count;
	unsigned int* base;
	unsigned int* head;
}LIFO_Buffer_t;

typedef enum{
	LIFO_No_Error,
	LIFO_Full,
	LIFO_Empty,
	LIFO_Null
}LIFO_Status;

/* APIs */
LIFO_Status LIFO_Add_Item(LIFO_Buffer_t* LIFO_Buffer, unsigned int item);
LIFO_Status LIFO_Get_Item(LIFO_Buffer_t* LIFO_Buffer, unsigned int* item);
LIFO_Status LIFO_Init(LIFO_Buffer_t* LIFO_Buffer, unsigned int* Buffer, unsigned int length);

#endif /* LIFO_H_ */
