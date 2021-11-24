/*
 * CA.c
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#include "CA.h"

/* Variables */
int CA_speed = 0;
int CA_distance = 0;
int CA_threshold = 50;

void (*P_CA_state)() = 0;

STATE_Fn_Define(CA_Waiting){
	CA_State_ID = CA_Waiting;
	CA_speed = 0;
	CA_distance = US_Get_Distance_Random(45, 55);

	(CA_distance <= CA_threshold) ? (P_CA_state = STATE(CA_Waiting)) : (P_CA_state = STATE(CA_Driving));
	printf("Waiting state: distance=%d speed=%d \n", CA_distance, CA_speed);
}

STATE_Fn_Define(CA_Driving){
	CA_State_ID = CA_Driving;
	CA_speed = 30;
	CA_distance = US_Get_Distance_Random(45, 55);

	(CA_distance <= CA_threshold) ? (P_CA_state = STATE(CA_Waiting)) : (P_CA_state = STATE(CA_Driving));
	printf("Driving state: distance=%d speed=%d \n", CA_distance, CA_speed);
}

int US_Get_Distance_Random(int l, int r){
	int rand_num = (rand() % (r-l+1))+l;
	return rand_num;
}
