/*
 * ex4.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int main()
{
	float x, y;
	printf("Enter two numbers: ");
	fflush(stdout);
	scanf("%f \n%f", &x, &y);
	printf("Product: %f", x*y);
	return 0;
}
