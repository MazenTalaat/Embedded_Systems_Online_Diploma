/*
 * ex4.c
 *
 *  Created on: Oct 11, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

struct Sstudent
{
	char m_name[50];
	int m_roll;
	int m_marks;
} gstudent[10];

struct Sstudent read_data();
void print_data(struct Sstudent);

int main(){
	int i;
	printf("\nEnter information of students:\n\n");
	for(i=0; i<10; i++){
		gstudent[i] = read_data(i);
	}
	printf("\nDisplaying informationof students:\n\n");
	for(i=0; i<10; i++){
		print_data(gstudent[i]);
	}
	return 0;
}

struct Sstudent read_data(int i){
	struct Sstudent x;
	printf("For roll number %d\n", i+1);
	printf("Enter name: ");
	scanf("%s", &x.m_name);
	x.m_roll = i+1;
	printf("Enter marks: ");
	scanf("%d", &x.m_marks);
	printf("\n");
	return x;
}

void print_data(struct Sstudent x){
	printf("Information for roll number %d:\n", x.m_roll);
	printf("name: %s\n", x.m_name);
	printf("Marks: %d\n", x.m_marks);
}
