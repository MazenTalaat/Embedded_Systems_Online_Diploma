/*
 * ex2.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main(){
	int i, n;
	float num, sum=0;
	printf("Enter the number of data: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &n);
	float ns[n];
	for(i=0;i<n;i++){
		printf("%d. Enter number: ", i+1);
		fflush(stdout); fflush(stdin);
		scanf("%f", &num);
		ns[i] = num;
		sum+=num;
	}
	printf("Average = %.2f", sum/n);
	return 0;
}
