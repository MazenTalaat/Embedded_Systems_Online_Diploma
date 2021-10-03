/*
 * ex4.c
 *
 *  Created on: Oct 03, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"
#include "string.h"

int power(int, int);

int main(){
	int x, pow;
	printf("Enter base number: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &x);
	printf("Enter power number (positive integer): ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &pow);
	printf("%d^%d = %d", x, pow, power(x, pow));
	return 0;
}
int power(int a, int b){
	if(b!=0){
		return a*power(a, b-1);
	}
	else
		return 1;
}
