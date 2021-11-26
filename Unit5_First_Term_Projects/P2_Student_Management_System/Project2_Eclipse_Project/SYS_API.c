/*
 * 		SYS_API.c
 *
 *  	Created on: Nov 25, 2021
 *      Author: Mazen Talaat
 */

#include "SYS_API.h"

/* Global variable */
int num_of_students = 0;

/* Functions body */
/* Add student details manually	*/
void add_student_manually(){
	/* Check if full */
	if(num_of_students < 50){
		int i, rn;
		Dprint(" ------------------------\n");
		Dprint(" Add the student details\n");
		Dprint(" ------------------------\n");
		Dprint(" Enter the roll number: ");
		Dscan("%d", &rn);
		for(i=0; i<num_of_students; i++){
			if(st[i].roll == rn){
				Dprint(" [ERROR] Roll number %d is already taken\n", rn);
				return;
			}
		}
		st[num_of_students].roll = rn;
		Dprint(" Enter first name of student: ");
		Dscan("%s", st[num_of_students].fname);
		Dprint(" Enter last name of student: ");
		Dscan("%s", st[num_of_students].lname);
		Dprint(" Enter the GPA you obtained: ");
		Dscan("%f", &st[num_of_students].gpa);
		Dprint(" Enter the courses ID\n");
		for(i = 0; i<5; i++){
			Dprint(" Course %d ID: ", i+1);
			Dscan("%d", &st[num_of_students].cid[i]);
		}
		num_of_students++;
		Dprint(" [INFO] Student details is added successfully\n");
		tot_s();
	}
	else{
		Dprint(" [ERROR] The list is full\n");
	}
}

/* Add student details from text file */
void add_student_file(){
	/* Check if full */
	if(num_of_students < 50){
		/*Buffer to store the data from file */
		char buff[100];
		int i, rn, F_found, F_EOF;
		fp = fopen("Students.txt", "r");
		while(1){
			/* Reset the flag */
			F_found = 0;
			/* Read Roll number */
			fscanf(fp, "%s", buff);
			rn = atoi(buff);
			st[num_of_students].roll = rn;
			/* Read First name */
			fscanf(fp, "%s", st[num_of_students].fname);
			/* Read Last name */
			fscanf(fp, "%s", st[num_of_students].lname);
			/* Read GPA */
			fscanf(fp, "%s", buff);
			st[num_of_students].gpa = atof(buff);
			for(i=0; i<num_of_courses; i++){
				/* Read Courses ID */
				F_EOF = fscanf(fp, "%s", buff);
				st[num_of_students].cid[i] = atoi(buff);
			}
			/* Search for roll ID */
			for(i=0; i<num_of_students; i++){
				if(st[i].roll == rn){
					Dprint(" [ERROR] Roll number %d is already taken\n", rn);
					/* Raise found flag */
					F_found = 1;
					break;
				}
			}
			if(F_found == 0){
				Dprint(" [INFO] Roll number %d saved successfully\n", rn);
				num_of_students++;
			}
			/* Check if reached EOF */
			if(F_EOF == -1){
				fclose(fp);
				break;
			}
		}
		Dprint(" [INFO] Students details is added successfully\n");
		tot_s();
	}
	else{
		Dprint(" [ERROR] The list is full\n");
	}
}

/* Find the student by the given roll number */
void find_rl(){
	/* Check if empty */
	if(num_of_students != 0){
		int i, j, rn;
		Dprint(" -------------------------------\n");
		Dprint(" Find a student by roll number\n");
		Dprint(" -------------------------------\n");
		Dprint(" Enter the roll number: ");
		Dscan("%d", &rn);
		/* Search for roll number */
		for(i = 0; i<num_of_students; i++){
			if (st[i].roll == rn){
				Dprint(" ----------------------------\n");
				Dprint("\n Student first name: %s\n", st[i].fname);
				Dprint(" Student last name: %s\n", st[i].lname);
				Dprint(" Student roll number: %d\n", st[i].roll);
				Dprint(" Student GPA number: %.1f\n", st[i].gpa);
				for(j=0; j<num_of_courses; j++){
					Dprint(" Course %d ID: %d\n", j+1, st[i].cid[j]);
				}
				Dprint(" ----------------------------\n");
				return;
			}
		}
		/* If the loop ended */
		Dprint(" [ERROR] Roll number %d not found\n", rn);
	}
	else{
		Dprint(" [ERROR] The list is empty!\n");
	}
}

/* Find the student by the given first name */
void find_fn(){
	/* Check if empty */
	if(num_of_students != 0){
		int i, j, F_found=0;
		char fn[name_length];
		Dprint(" -------------------------------\n");
		Dprint(" Find a student by first name\n");
		Dprint(" -------------------------------\n");
		Dprint(" Enter the first name: ");
		Dscan("%s", fn);
		/* Search for first name by comparing strings */
		for(i = 0; i<num_of_students; i++){
			if (!strcmp(fn, st[i].fname)){
				Dprint(" ----------------------------\n");
				Dprint(" Student first name: %s\n", st[i].fname);
				Dprint(" Student last name: %s\n", st[i].lname);
				Dprint(" Student roll number: %d\n", st[i].roll);
				Dprint(" Student GPA number: %.1f\n", st[i].gpa);
				for(j=0; j<num_of_courses; j++){
					Dprint(" Course %d ID: %d\n", j+1, st[i].cid[j]);
				}
				/* Raise found flag */
				F_found = 1;
			}
		}
		if (F_found == 0)
			Dprint(" [ERROR] First name %s not found\n", fn);
	}
	else{
		Dprint(" [ERROR] The list is empty!\n");
	}
}

/* Find the student registered in a course */
void find_c(){
	/* Check if empty */
	if(num_of_students != 0){
		int i, j, ID,F_found=0;
		int count = 0;
		Dprint(" -------------------------------\n");
		Dprint(" Find students by course ID\n");
		Dprint(" -------------------------------\n");
		Dprint(" Enter the course ID: ");
		Dscan("%d", &ID);
		/* Search for course ID */
		for(i = 0; i<num_of_students; i++){
			for(j=0; j<num_of_courses; j++){
				if (st[i].cid[j] == ID){
					Dprint(" ----------------------------\n");
					Dprint(" Student first name: %s\n", st[i].fname);
					Dprint(" Student last name: %s\n", st[i].lname);
					Dprint(" Student roll number: %d\n", st[i].roll);
					Dprint(" Student GPA number: %.1f\n", st[i].gpa);
					/* Increase the number of enrolled students by 1 */
					count++;
					/* Raise found flag */
					F_found = 1;
					/* Break to stop the courses loop */
					break;
				}
			}
		}
		if (F_found == 0){
			Dprint(" [ERROR] Course ID %d not found\n", ID);
		}
		else{
			Dprint(" [INFO] Total number of students enrolled: %d\n", count);
		}
	}
	else{
		Dprint(" [ERROR] The list is empty!\n");
	}
}

/* Count number of students */
void tot_s(){
	Dprint(" -----------------------------------------\n");
	Dprint(" [INFO] The total number of students is %d\n", num_of_students);
	Dprint(" [INFO] You can add up to %d students\n"	 , max_num_of_students);
	Dprint(" [INFO] You can add %d more students\n"		 , max_num_of_students - num_of_students);
}

/* Fills the gap */
void remove_gap(int index){
	int i;
	for(i=index; i<num_of_students; i++){
		/* Shift all students to the removed index */
		st[i] = st[i+1];
	}
}

/* Delete a student */
void del_s(){
	/* Check if empty */
	if(num_of_students != 0){
		int i, rn;
		Dprint(" -------------------------------\n");
		Dprint(" Delete a student by roll number\n");
		Dprint(" -------------------------------\n");
		Dprint(" Enter the roll number: ");
		Dscan("%d", &rn);
		/* Search for roll number */
		for(i = 0; i<num_of_students; i++){
			if (st[i].roll == rn){
				/* Decrease the num_of_students by 1 */
				num_of_students--;
				/* Fill the gap with the next student */
				remove_gap(i);
				Dprint(" [INFO] The roll number is removed successfully\n");
				return;
			}
		}
		/* If the loop ended */
		Dprint(" [ERROR] The roll number %d not found\n", rn);
	}
	else{
		Dprint(" [ERROR] The list is empty!\n");
	}

}

/* Update a student */
void up_s(){
	/* Check if empty */
	if(num_of_students != 0){
		int i, j, rn, x;
		Dprint(" -------------------------------\n");
		Dprint(" Update a student by roll number\n");
		Dprint(" -------------------------------\n");
		Dprint(" Enter the roll number: ");
		Dscan("%d", &rn);
		/* Search for roll number */
		for(i = 0; i<num_of_students; i++){
			if (st[i].roll == rn){
				Dprint(" 1. First name\n");
				Dprint(" 2. Last name\n");
				Dprint(" 3. Roll number\n");
				Dprint(" 4. GPA\n");
				Dprint(" 5. Courses\n");
				Dprint(" Enter your choice: ");
				Dscan("%d", &x);
				switch(x){
				case 1:
					Dprint(" Enter the new first name: ");
					Dscan("%s", st[i].fname);
					Dprint(" [INFO] Updated successfully\n");
					break;
				case 2:
					Dprint(" Enter the new last name: ");
					Dscan("%s", st[i].lname);
					Dprint(" [INFO] Updated successfully\n");
					break;
				case 3:
					Dprint(" Enter the new roll number: ");
					Dscan("%d", &st[i].roll);
					Dprint(" [INFO] Updated successfully\n");
					break;
				case 4:
					Dprint(" Enter the new GPA: ");
					Dscan("%f", &st[i].gpa);
					Dprint(" [INFO] Updated successfully\n");
					break;
				case 5:
					Dprint(" Enter the new course ID: \n");
					for(j = 0; j<5; j++){
						Dprint(" Course %d ID: ", j+1);
						Dscan("%d", &st[i].cid[j]);
					}
					Dprint(" [INFO] Updated successfully\n");
					break;
				default:
					Dprint(" Wrong input value\n");
					break;
				}
				return;
			}
		}
		/* If the loop ended */
		Dprint(" [ERROR] Roll number %d not found\n", rn);
	}
	else{
		Dprint(" [ERROR] The list is empty!\n");
	}
}

/* Print student details */
void show_s(){
	/* Check if empty */
	if(num_of_students != 0){
		int i, j;
		Dprint(" ----------------------------\n");
		for(i=0; i<num_of_students; i++){
			Dprint("\n Student first name: %s\n", st[i].fname);
			Dprint(" Student last name: %s\n"   , st[i].lname);
			Dprint(" Student roll number: %d\n" , st[i].roll);
			Dprint(" Student GPA number: %.1f\n", st[i].gpa);
			for(j=0; j<num_of_courses; j++){
				Dprint(" Course %d ID: %d\n", j+1, st[i].cid[j]);
			}
		}
		Dprint(" ----------------------------\n");
	}
	else{
		Dprint("[ERROR] The list is empty!\n");
	}
}
