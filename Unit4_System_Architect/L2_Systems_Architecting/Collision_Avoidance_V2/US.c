/*
 * US.c
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#include "US.h"

int US_distance = 0;

void (*P_US_state)() = 0;

void US_Init(){
	printf("US_init \n");
}

int US_Get_Distance_Random(int l, int r){
	int rand_num = (rand() % (r-l+1))+l;
	return rand_num;
}

STATE_Fn_Define(US_Busy){
	US_State_ID = US_Busy;
	US_distance = US_Get_Distance_Random(45, 55);
	printf("US_Waiting state distance=%d\n", US_distance);
	US_Set_Distance(US_distance);
	P_US_state = STATE(US_Busy);
}
