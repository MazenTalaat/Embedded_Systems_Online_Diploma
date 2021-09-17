/*
 * ex6.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main()
{
	int x, i, sum=0;
	printf("Enter an integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &x);
	for(i=1; i<=x; i++)
	{
		sum+=i;
	}
	printf("Sum = %d", sum);
	return 0;
}
