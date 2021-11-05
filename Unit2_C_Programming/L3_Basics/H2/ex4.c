/*
 * ex4.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main()
{
	float x;
	printf("Enter a number: ");
	fflush(stdout); fflush(stdin);
	scanf("%f", &x);
	if(x>0)
		printf("%.2f is positive", x);
	else if(x<0)
		printf("%.2f is negative", x);
	else
		printf("You entered a zero");
	return 0;
}
