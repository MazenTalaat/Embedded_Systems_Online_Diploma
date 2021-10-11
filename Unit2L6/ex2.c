/*
 * ex2.c
 *
 *  Created on: Oct 11, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

struct Sdistance
{
	int m_feet;
	float m_inch;
} gx, gy, gsum;

struct Sdistance read_data();

int main(){
	printf("\nEnter information for 1st distance:\n");
	gx = read_data();
	printf("\nEnter information for 2nd distance:\n");
	gy = read_data();
	if((gx.m_inch+gy.m_inch)>12){
		gsum.m_feet = gx.m_feet + gy.m_feet + 1;
		gsum.m_inch = gx.m_inch + gy.m_inch - 12;
	}
	else{
		gsum.m_feet = (gx.m_feet + gy.m_feet);
		gsum.m_inch = (gx.m_inch + gy.m_inch);
	}
	printf("\nSum of distances = %d\'%.1f\"", gsum.m_feet, gsum.m_inch);
	return 0;
}

struct Sdistance read_data(){
	struct Sdistance x;
	printf("Enter feet: ");
	scanf("%d", &x.m_feet);
	printf("Enter inch: ");
	scanf("%f", &x.m_inch);
	return x;
}
