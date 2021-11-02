/*
 * ex4.c
 *
 *  Created on: Nov 02, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int main(){
	int num[15], size, *p, i, d;
	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &size);
	fflush(stdout); fflush(stdin);
	printf("Input %d number of elements in the array : \n", size);
	for(i=0; i<size; i++){
		printf("element-%d:",i+1);
		fflush(stdout); fflush(stdin);
		scanf("%d", &d);
		num[i]=d;
		fflush(stdout); fflush(stdin);
	}
	p=num+size-1;
	printf("The elements of array in reverse order are : \n");
	for(i=size-1; i>=0; i--){
		printf("element - %d : ",i+1);
		printf("%d\n",*p);
		p--;
	}
	return 0;
}
