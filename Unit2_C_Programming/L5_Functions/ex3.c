/*
 * ex3.c
 *
 *  Created on: Oct 03, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"
#include "string.h"

void rev(char arr[], int);

int main(){
	char str[50];
	printf("Enter a sentence: ");
	fflush(stdout); fflush(stdin);
	gets(str);
	rev(str, strlen(str));
	return 0;
}
void rev(char arr[], int n){
	if(n!=0){
		printf("%c", arr[n-1]);
		rev(arr,n-1);
	}
}
