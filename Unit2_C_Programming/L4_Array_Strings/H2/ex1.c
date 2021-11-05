/*
 * ex1.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"
#include "string.h"

int main(){
	int i, counter=0;
	char s[100], c;
	printf("Enter a string: ");
	fflush(stdout); fflush(stdin);
	gets(s);
	printf("Enter a character to find frequency: ");
	fflush(stdout); fflush(stdin);
	scanf("%c", &c);
	for(i=0;i<strlen(s);i++){
		if(c==s[i])
			counter++;
	}
	printf("Frequency of %c = %d", c, counter);
	return 0;
}
