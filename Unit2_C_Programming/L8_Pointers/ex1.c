/*
 * ex1.c
 *
 *  Created on: Nov 02, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int main(){
	int m = 29;
	int *ab;
	printf("Address of m: 0x%llx \n", &m);
	printf("Value of m: %d\n\n", m);
	printf("Now ab is assigned with the address of m.\n");
	ab = &m;
	printf("Address of pointer ab: 0x%llx \n", ab);
	printf("Value of of pointer ab: %d \n\n", *ab);
	printf("The value of m assigned to 34 now.\n");
	m = 34;
	printf("Address of pointer ab: 0x%llx \n", ab);
	printf("Value of of pointer ab: %d \n\n", *ab);
	printf("The pointer variable ab is assigned with the value 7 now.\n");
	*ab = 7;
	printf("Address of m: 0x%llx \n", &m);
	printf("Value of m: %d \n\n", m);
	return 0;
}
