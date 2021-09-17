/*
 * ex2.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int main()
{
	int x;
	printf("Enter an integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &x);
	printf("You entered: %d", x);
	return 0;
}
