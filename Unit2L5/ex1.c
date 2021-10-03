/*
 * ex1.c
 *
 *  Created on: Oct 03, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"
void prime_numbers(int, int);


int main(){
	int x, y;
	printf("Enter two numbers (intervals): ");
	fflush(stdout); fflush(stdin);
	scanf("%d %d", &x, &y);
	prime_numbers(x, y);
	return 0;
}
void prime_numbers(int a, int b){
	int i = a++;
	printf("Prime numbers between %d and %d are: ", a, b);
	for(; i<b; i++){
		if((i%2)!=0 && (i%3)!=0 && (i%5)!=0){
			printf("%d ", i);
		}
	}
}
