/*
 * ex3.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int main()
{
	int x, y;
	printf("Enter two integers: ");
	fflush(stdout);
	scanf("%d \n%d", &x, &y);
	printf("Sum: %d", x+y);
	return 0;
}
