/*
 * ex3.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main(){
	int r, c, i, j, m[50][50], t[50][50];
	printf("Enter rows and column of matrix: ");
	fflush(stdout); fflush(stdin);
	scanf("%d \n%d", &r, &c);
	printf("Enter elements of matrix: \n");
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			printf("Enter element a%d%d: ",i+1, j+1);
			fflush(stdout); fflush(stdin);
			scanf("%d", &m[i][j]);
		}
	}
	printf("Entered Matrix: \n");
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			printf("%d\t",m[i][j]);
			t[j][i]=m[i][j];
		}
		printf("\n");
	}
	printf("Transpose of Matrix: \n");
	for(i=0;i<c;i++){
		for(j=0;j<r;j++){
			printf("%d\t",t[i][j]);
		}
		printf("\n");
	}
	return 0;
}
