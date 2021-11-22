/*
 * lifo.c
 *
 *  Created on: Nov 21, 2021
 *      Author: Mazen Talaat
 */

#include "lifo.h"

LIFO_Status LIFO_Init(LIFO_Buffer_t* LIFO_Buffer, unsigned int* Buffer, unsigned int length){
	/* Check location is valid */
	if(Buffer == NULL)
		return LIFO_Null;
	LIFO_Buffer->base = Buffer;
	LIFO_Buffer->count = 0;
	LIFO_Buffer->head = Buffer;
	LIFO_Buffer->length = length;
	return LIFO_No_Error;
}

LIFO_Status LIFO_Add_Item(LIFO_Buffer_t* LIFO_Buffer, unsigned int item){
	/* Check LIFO is valid */
	if(!LIFO_Buffer->base || !LIFO_Buffer->head)
		return LIFO_Null;
	/* Check LIFO is full */
	if(LIFO_Buffer->count == LIFO_Buffer->length)
		return LIFO_Full;
	/* Add item */
	*(LIFO_Buffer->head) = item;
	LIFO_Buffer->head++;
	LIFO_Buffer->count++;
	return LIFO_No_Error;
}

LIFO_Status LIFO_Get_Item(LIFO_Buffer_t* LIFO_Buffer, unsigned int* item){
	/* Check LIFO is valid */
	if(!LIFO_Buffer->base || !LIFO_Buffer->head)
			return LIFO_Null;
	/* Check LIFO is empty */
	if(LIFO_Buffer->count == 0)
			return LIFO_Empty;
	/* Get item */
	LIFO_Buffer->head--;
	*item = *(LIFO_Buffer->head);
	LIFO_Buffer->count--;
	return LIFO_No_Error;
}
