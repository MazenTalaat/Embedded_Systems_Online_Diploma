/*
 * ex2.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main()
{
	char x;
	printf("Enter an alphabet: ");
	fflush(stdout); fflush(stdin);
	scanf("%c", &x);
	switch (x)
	{
	case 'a':
	case 'A':
	case 'e':
	case 'E':
	case 'I':
	case 'i':
	case 'o':
	case 'O':
	case 'u':
	case 'U':
	{
		printf("%c is a vowel",x);
	}
	break;
	default:
		printf("%c is a consonant",x);
	}
	return 0;
}
