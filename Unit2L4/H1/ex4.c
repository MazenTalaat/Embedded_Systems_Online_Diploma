/*
 * ex4.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main(){
	int n, i, j, l, arr[50];

	printf("Enter no of elements : ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &n);

	for(i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}
	printf("Enter the element to be inserted : ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &j);

	printf("Entered the location : ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &l);

	for(i=n; i>=l; i--){
		arr[i]=arr[i-1];
	}
	arr[l-1]=j;
	for(i=0;i<n+1;i++){
		printf("%d ", arr[i]);
	}
	return 0;
}
