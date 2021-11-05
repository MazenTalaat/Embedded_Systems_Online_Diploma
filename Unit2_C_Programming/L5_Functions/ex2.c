/*
 * ex2.c
 *
 *  Created on: Oct 03, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int fact(int);

int main(){
	int x;
	printf("Enter a positive integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &x);
	printf("Factorial of %d = %d", x, fact(x));
	return 0;
}
int fact(int a){
	if(a==0){
		return 1;
	}
	else{
		return a*fact(a-1);
	}
}
