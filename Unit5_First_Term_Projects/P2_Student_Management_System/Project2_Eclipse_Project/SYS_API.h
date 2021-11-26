/*
 * 		SYS_API.h
 *
 *  	Created on: Nov 25, 2021
 *      Author: Mazen Talaat
 */

#ifndef SYS_API_H_
#define SYS_API_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macros */
#define Dprint(...) printf(__VA_ARGS__); fflush(stdin); fflush(stdout)
#define Dscan(...)  scanf (__VA_ARGS__); fflush(stdin); fflush(stdout)

#define name_length 50
#define num_of_courses 5
#define max_num_of_students 50

/* Definitions */
struct sinfo{
	char  fname[name_length];
	char  lname[name_length];
	int   roll;
	float gpa;
	int   cid[num_of_courses];
}st[max_num_of_students];

FILE *fp;

/* APIs */
void add_student_manually(   ); /* Add student details manually				 */
void add_student_file    (   ); /* Add student details from text file 		 */
void find_rl             (   ); /* Find the student by the given roll number */
void find_fn			 (   );	/* Find the student by the given first name  */
void find_c				 (   ); /* Find the student registered in a course 	 */
void tot_s				 (   ); /* Count number of students 				 */
void remove_gap			 (int); /* Fills the gap 							 */
void del_s				 (   );	/* Delete a student 						 */
void up_s				 (   );	/* Update a student 						 */
void show_s				 (   );	/* Print student details 					 */

#endif /* SYS_API_H_ */
