/*
 * ex2.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"
#include "string.h"

int main(){
	int i;
	char s[100];
	printf("Enter a string: ");
	fflush(stdout); fflush(stdin);
	gets(s);
	for(i=0;i<sizeof(s);i++){
		if(s[i]==0)
			break;
	}
	printf("Length of string: %d", i);
	return 0;
}
