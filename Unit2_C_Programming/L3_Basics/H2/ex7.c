/*
 * ex7.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main()
{
	int x, i, fact=1;
	printf("Enter an integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &x);
	if(x<0)
		printf("Error!!! Factorial of a negative number doesn't exist");
	else if (x==0)
		printf("Factorial = 1");
	else
	{
		for(i=1; i<=x; i++)
		{
			fact*=i;
		}
		printf("Factorial = %d", fact);
	}
	return 0;
}
