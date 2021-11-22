/*
 * features.c
 *
 *  Created on: Nov 22, 2021
 *      Author: Mazen Talaat
 */

#include "features.h"

extern struct SStudent* gpFirstStudent;

/* Fills the record with the student data */
void Fill_The_Record(struct SStudent* NewStudent){
	char temp[40];

	DPrint("\n Enter the ID: ")
	gets(temp);
	NewStudent->Student.ID = atoi(temp);

	DPrint("\n Enter the name: ")
	gets(NewStudent->Student.Name);

	DPrint("\n Enter the height: ")
	gets(temp);
	NewStudent->Student.Height = atof(temp);
}

void Add_Student(){
	struct SStudent* PLastStudent;
	struct SStudent* PNewStudent;

	/* First time */
	if(gpFirstStudent == NULL){
		PNewStudent = (struct SStudent* )malloc(sizeof(struct SStudent));
		/* Point to the new location */
		gpFirstStudent = PNewStudent;
	}
	/* Second time */
	else{
		/* Point to the first location and loop until getting NULL */
		PLastStudent = gpFirstStudent;
		while(PLastStudent->PNextStudent){
			PLastStudent = PLastStudent->PNextStudent;
		}
		PNewStudent = (struct SStudent* )malloc(sizeof(struct SStudent));
		/* Point to the new location */
		PLastStudent->PNextStudent = PNewStudent;
	}
	Fill_The_Record(PNewStudent);
	/* Point to NULL */
	PNewStudent->PNextStudent = NULL;
}

void Delete_Student(){
	char temp[40], FFree /* Flag to confirm that the location is freed */;
	DPrint("\n Enter the student ID to be deleted: ")
	gets(temp);

	struct SStudent* PCurrentStudent;
	struct SStudent* PPreviousStudent;
	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n Empty list")
	}
	else{
		/* Initial value */
		PPreviousStudent = NULL;
		PCurrentStudent = gpFirstStudent;

		while(PCurrentStudent){
			/* If the ID is found */
			if(PCurrentStudent->Student.ID == atoi(temp)){
				/* Raise the flag */
				FFree = 1;
				/* If it is not the first */
				if(PPreviousStudent){
					PPreviousStudent->PNextStudent = PCurrentStudent->PNextStudent;
				}
				/* If it is the first */
				else{
					gpFirstStudent = PCurrentStudent->PNextStudent;
				}
				free(PCurrentStudent);
				DPrint("\n Record deleted")
				break;
			}
			/* Looping */
			PPreviousStudent = PCurrentStudent;
			PCurrentStudent = PCurrentStudent->PNextStudent;
		}
		/* If the loop is finished without raising the flag */
		if(!FFree)
			DPrint("\n ID not found")
	}
}

void View_Students(){
	struct SStudent* PCurrentStudent;
	int count = 1;
	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n List is empty")
	}
	else{
		/* Initial value */
		PCurrentStudent = gpFirstStudent;
		/* Loop and print the data until getting NULL */
		while(PCurrentStudent){
			DPrint("\n Record number: %d", count)
			DPrint("\n ID: %d", PCurrentStudent->Student.ID)
			DPrint("\n Name: %s", PCurrentStudent->Student.Name)
			DPrint("\n Height: %.1f", PCurrentStudent->Student.Height)
			PCurrentStudent = PCurrentStudent->PNextStudent;
			count++;
		}
	}
}

void Delete_All(){
	struct SStudent* pCurrentStudent = gpFirstStudent;
	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n List is empty")
	}
	else{
		/* Loop and free the space until getting NULL */
		while(pCurrentStudent){
			/* Temp pointer to hold the current address */
			struct SStudent* pTemp = pCurrentStudent;
			pCurrentStudent = pCurrentStudent->PNextStudent;
			free(pTemp);
		}
		gpFirstStudent = NULL;
		DPrint("\n All deleted")
	}
}

void Get_Nth(){
	char temp[40], FFound=0; /* Flag found */
	int count = 0;

	DPrint("\n Enter the index: ")
	gets(temp);
	/* Initial value */
	struct SStudent* pCurrentStudent = gpFirstStudent;

	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n List is empty")
	}
	else{
		/* Loop till the index == the counter or getting NULL */
		while(pCurrentStudent){
			if(atoi(temp) == count){
				FFound = 1;
				DPrint("\n The ID is: %d", pCurrentStudent->Student.ID)
				break;
			}
			else{
				pCurrentStudent = pCurrentStudent->PNextStudent;
				count++;
			}
		}
		/* If got NULL */
		if (FFound==0)
			DPrint("\n The ID is not found")
	}
}

void Get_Count(){
	/* Initial value */
	int count = 0;
	struct SStudent* pCurrentStudent = gpFirstStudent;
	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n List is empty")
	}
	else{
		/* Loop till getting NULL */
		while(pCurrentStudent){
			pCurrentStudent = pCurrentStudent->PNextStudent;
			count++;
		}
		DPrint("\n Count is: %d", count)
	}
}

int Get_Count_Recursive(struct SStudent* PCurrentStudent){
	/* Loop till getting NULL then return 0 */
	if(PCurrentStudent){
		return (1 + Get_Count_Recursive(PCurrentStudent->PNextStudent));
	}
	else
		return 0;
}

void Get_Nth_End(){
	/* Initial value */
	struct SStudent* PMainStudent = gpFirstStudent;
	struct SStudent* PRefStudent  = gpFirstStudent;
	int count = 0;
	char temp[40];
	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n List is empty")
	}
	else{
		/* Getting index number */
		DPrint("\n Enter the reversed index: ")
		gets(temp);
		/* Move the main pointer to nth index */
		while(PRefStudent){
			PRefStudent = PRefStudent->PNextStudent;
			if(count == atoi(temp)){
				break;
			}
			count++;
		}
		if(count == atoi(temp)){
			/* Move the two pointer until the PRef becomes NULL */
			while(PRefStudent){
				PRefStudent = PRefStudent->PNextStudent;
				PMainStudent = PMainStudent->PNextStudent;
			}
			DPrint("\n The ID is: %d", PMainStudent->Student.ID)
		}
		/* If we got NULL without reaching the nth index */
		else
			DPrint("\n Number of students is low")
	}
}

void Get_Middle(){
	/* Initial value */
	struct SStudent* PFastStudent = gpFirstStudent;
	struct SStudent* PSlowStudent = gpFirstStudent;
	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n List is empty")
	}
	else{
		while(PFastStudent){
			/* Move the fast pointer two steps and the slower pointer one step */
			PFastStudent = PFastStudent->PNextStudent;
			/* Check if the fast point is NULL with one step */
			if(PFastStudent){
			PFastStudent = PFastStudent->PNextStudent;
			PSlowStudent = PSlowStudent->PNextStudent;
			}
			else
				break;
		}
		DPrint("\n The ID of the middle is: %d", PSlowStudent->Student.ID)
	}
}

void Reverse(){
	/* Assuming we have 4 nodes and *
	 * the pointers are F, C, P, N  *
	 *  1->2->3->4->NULL 		L272*
	 * FCP N					L274*
	 * NULL<-1<-2  3->4->NULL	L283*
	 *     	 F	P CN			L286*
	 * NULL<-1<-2<-3  4->NULL   L283*
	 *  	 F	   P  CN        L286*
	 * NULL<-1<-2<-3<-4  NULL 	L283*
	 *  	 F        P  CN     L286*
	 * NULL<-1<-2<-3<-4  NULL	L289*
	 *  	          PF CN  	    */

	/* Initial value */
	struct SStudent* pCurrentStudent  = gpFirstStudent;
	struct SStudent* pNextStudent     = gpFirstStudent->PNextStudent;
	struct SStudent* pPreviousStudent = gpFirstStudent;
	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n List is empty")
	}
	else{
		/* Details above */
		gpFirstStudent->PNextStudent = NULL;
		while(pCurrentStudent){
			pCurrentStudent = pNextStudent->PNextStudent;  /* Move the pointer */
			pNextStudent->PNextStudent = pPreviousStudent; /* Switch the arrow */
			pPreviousStudent = pNextStudent;			   /* Move the pointer */
			pNextStudent = pCurrentStudent;			       /* Move the pointer */
		}
		/* Set the first pointer to the previous pointer */
		gpFirstStudent = pPreviousStudent;
		DPrint("\n List is now reversed")
	}
}

void Loop_Detection(){
	/* Initial value */
	struct SStudent* PFastStudent = gpFirstStudent;
	struct SStudent* PSlowStudent = gpFirstStudent;
	int FLoop = 0; /* Flag if loop detected */
	/* Check if the list is empty */
	if(gpFirstStudent == NULL){
		DPrint("\n List is empty")
	}
	else{
		while(PFastStudent){
			/* Move the fast pointer two steps and the slower pointer one step */
			PFastStudent = PFastStudent->PNextStudent;
			/* Check if the fast pointer is NULL with one step */
			if(PFastStudent){
				break;
			}
			PFastStudent = PFastStudent->PNextStudent;
			PSlowStudent = PSlowStudent->PNextStudent;
			/* Check if the fast pointer is == slow pointer */
			if(PFastStudent==PSlowStudent){
				DPrint("\n Loop detected")
				FLoop = 1;
				break;
			}
		}
		if(!FLoop)
			DPrint("\n No loop detected")
	}
}
