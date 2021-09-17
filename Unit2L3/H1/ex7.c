/*
 * ex7.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int main()
{
	float a, b;
	printf("Enter value of a: ");
	fflush(stdout); fflush(stdin);
	scanf("%f", &a);
	printf("Enter value of b: ");
	fflush(stdout); fflush(stdin);
	scanf("%f", &b);
	a = a + b;
	b = a - b;
	a = a - b;
	printf("After swapping, value of a = %.2f", a);
	printf("\nAfter swapping, value of b = %.1f", b);
	return 0;
}
