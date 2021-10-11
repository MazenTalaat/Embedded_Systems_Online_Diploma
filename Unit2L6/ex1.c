/*
 * ex1.c
 *
 *  Created on: Oct 11, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

void read_data();
void print_data();

struct Sstudent
{
	char m_name[50];
	int m_roll;
	float m_marks;
} gstudent;

int main(){
	read_data();
	print_data();
	return 0;
}

void read_data(){
	printf("\nEnter information of students:\n\n");
	printf("Enter name: ");
	scanf("%s", &gstudent.m_name);
	printf("Enter roll number: ");
	scanf("%d", &gstudent.m_roll);
	printf("Enter marks: ");
	scanf("%f", &gstudent.m_marks);
}

void print_data(){
	printf("\nDisplaying information\n");
	printf("name: %s\n", gstudent.m_name);
	printf("Roll: %d\n", gstudent.m_roll);
	printf("Marks: %.2f\n", gstudent.m_marks);
}
