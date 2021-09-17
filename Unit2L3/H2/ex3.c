/*
 * ex3.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main()
{
	float x1, x2, x3;
	printf("Enter three numbers: ");
	fflush(stdout); fflush(stdin);
	scanf("%f\n%f\n%f", &x1, &x2, &x3);
	if(x1>x2)
	{
		if(x1>x3)
			printf("Largest number = %.2f", x1);
	}
	else if(x2>x1)
	{
		if(x2>x3)
			printf("Largest number = %.2f", x2);
	}
	else
		printf("Largest number = %.2f", x3);
	return 0;
}
