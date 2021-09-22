/*
 * ex3.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"
#include "string.h"

int main(){
	int i;
	char s[100];
	printf("Enter a string : ");
	fflush(stdout); fflush(stdin);
	gets(s);
	printf("Reverse string is :");
	for(i=strlen(s);i>=0;i--){
		printf("%c", s[i]);
	}
	return 0;
}
