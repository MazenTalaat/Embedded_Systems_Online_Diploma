/*
 * ex5.c
 *
 *  Created on: Oct 11, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

#define pi 3.14
#define Area(R) pi*R*R
int main(){
	float R, Area;
	printf("Enter the radius: ");
	scanf("%f", &R);
	printf("Area=%.2f\n", Area(R));
	return 0;
}
