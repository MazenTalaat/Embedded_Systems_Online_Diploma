/*
 * ex3.c
 *
 *  Created on: Nov 02, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"
#include "string.h"

int main(){
	char str[50];
	char *p;
	int i;
	printf("Pointer : Print a string in reverse order :\n");
	printf("------------------------------------------------\n");
	printf("Input a string : ");
	fflush(stdout); fflush(stdin);
	scanf("%s", str);
	fflush(stdout); fflush(stdin);
	p= str + strlen(str) - 1;
	printf("Reverse of the string is : ");
	for(i=strlen(str)-1; i>=0; i--){
		printf("%c", *p);
		p--;
	}
	return 0;
}
