/*
 * features.h
 *
 *  Created on: Nov 22, 2021
 *      Author: Mazen Talaat
 */

#ifndef FEATURES_H_
#define FEATURES_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DPrint(...) printf(__VA_ARGS__); fflush(stdin); fflush(stdout);

struct SData{
	int ID;
	char Name[40];
	float Height;
};

struct SStudent{
	struct SData Student;
	struct SStudent* PNextStudent;
};

void Fill_The_Record(struct SStudent*);
void Add_Student();
void Delete_Student();
void View_Students();
void Delete_All();
void Get_Nth();
void Get_Count();
int Get_Count_Recursive();
void Get_Nth_End();
void Get_Middle();
void Reverse();
void Loop_Detection();

#endif /* FEATURES_H_ */
