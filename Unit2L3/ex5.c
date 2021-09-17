/*
 * ex5.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int main()
{
	char x;
	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c", &x);
	printf("ASCII value of %c = %d", x, x);
	return 0;
}
