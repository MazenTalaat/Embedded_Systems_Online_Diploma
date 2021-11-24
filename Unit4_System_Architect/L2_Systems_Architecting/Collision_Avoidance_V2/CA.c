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

void US_Set_Distance(int d){
	CA_distance = d;
	(CA_distance <= CA_threshold) ? (P_CA_state = STATE(CA_Waiting)) : (P_CA_state = STATE(CA_Driving));
	printf("US -----> distance=%d -----> CA\n", CA_distance);
}

STATE_Fn_Define(CA_Waiting){
	CA_State_ID = CA_Waiting;
	CA_speed = 0;
	DC_Motor_Set(CA_speed);
	printf("Waiting state: distance=%d speed=%d \n", CA_distance, CA_speed);
}

STATE_Fn_Define(CA_Driving){
	CA_State_ID = CA_Driving;
	CA_speed = 30;
	DC_Motor_Set(CA_speed);
	printf("Driving state: distance=%d speed=%d \n", CA_distance, CA_speed);
}
