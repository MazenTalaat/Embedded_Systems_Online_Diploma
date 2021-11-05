/*
 * ex5.c
 *
 *  Created on: Nov 02, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

struct employee
{
	char *Mname;
	int Mid;
};

int main(){
	struct employee employee1 = {"Mazen",1001}, employee2 = {"Alex",1002};
	struct employee array[] = {&employee1, &employee2};
	struct employee *(*ptr)[2] = &array;

	printf("Employee Name: %s\n", (*(*ptr+1))->Mname);
	printf("Employee ID: %d", (*(*ptr+1))->Mid);
	return 0;
}
