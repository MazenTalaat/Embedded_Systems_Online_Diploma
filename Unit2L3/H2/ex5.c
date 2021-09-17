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
	fflush(stdout); fflush(stdin);
	scanf("%c", &x);
	int i = x;
	if((i>=65 && i<=90) || (i>=97 && i<=122))
		printf("%c is an alphabet", x);
	else
		printf("%c is not an alphabet", x);
	return 0;
}
