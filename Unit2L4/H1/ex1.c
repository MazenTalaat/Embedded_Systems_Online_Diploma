/*
 * ex1.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main(){
	int i,j;
	float n;
	float m1[2][2], m2[2][2];
	printf("Enter the elements of 1st matrix\n");
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			printf("Enter a%d%d: ", i+1,j+1);
			fflush(stdout); fflush(stdin);
			scanf("%f", &n);
			m1[i][j]=n;
		}
	}
	printf("Enter the elements of 2nd matrix\n");
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			printf("Enter b%d%d: ", i+1,j+1);
			fflush(stdout); fflush(stdin);
			scanf("%f", &n);
			m2[i][j]=n;
		}
	}
	printf("Sum Of Matrix: \n");
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			printf("%.1f\t", m1[i][j]+m2[i][j]);
		}
		printf("\n");
	}
	return 0;
}
