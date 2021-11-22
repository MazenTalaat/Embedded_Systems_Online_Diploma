/*
 * main.c
 *
 *  Created on: Nov 22, 2021
 *      Author: Mazen Talaat
 */

#include "features.h"

struct SStudent* gpFirstStudent = NULL;

int main(){
	char temp[40];
	while(1){
		DPrint("\n ===================================")
		DPrint("\n Choose one of the following options")
		DPrint("\n ===================================")
		DPrint("\n 1:  Add a student")
		DPrint("\n 2:  Delete a student")
		DPrint("\n 3:  View students")
		DPrint("\n 4:  Delete all students")
		DPrint("\n 5:  Get_Nth")
		DPrint("\n 6:  Get_Count")
		DPrint("\n 7:  Get_Count_Recursive")
		DPrint("\n 8:  Get_Nth_End")
		DPrint("\n 9:  Get_Middle")
		DPrint("\n 10: Reverse")
		DPrint("\n 11: Loop detection")
		DPrint("\n 12: Exit")
		DPrint("\n ===================================")
		DPrint("\n Enter option number: ")
		gets(temp);
		DPrint("\n ===================================")
		switch(atoi(temp)){
		case 1:
			Add_Student();
			break;
		case 2:
			Delete_Student();
			break;
		case 3:
			View_Students();
			break;
		case 4:
			Delete_All();
			break;
		case 5:
			Get_Nth();
			break;
		case 6:
			Get_Count();
			break;
		case 7:
			DPrint("\n Count is: %d", Get_Count_Recursive(gpFirstStudent));
			break;
		case 8:
			Get_Nth_End();
			break;
		case 9:
			Get_Middle();
			break;
		case 10:
			Reverse();
			break;
		case 11:
			Loop_Detection();
			break;
		case 12:
			return 1;
		default:
			DPrint("\n Wrong option")
			break;
		}
	}
	return 0;
}
