/*
 * DC.c
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#include "DC.h"

int DC_speed = 0;

void (*P_DC_state)() = 0;

void DC_Init(){
	printf("DC_init \n");
}

void DC_Motor_Set(int s){
	DC_speed = s;
	P_DC_state = STATE(DC_Busy);
	printf("CA -----> speed=%d -----> DC\n", DC_speed);
}

STATE_Fn_Define(DC_Idle){
	DC_State_ID = DC_Idle;
	P_DC_state = STATE(DC_Idle);
	printf("DC_Idle state speed=%d\n", DC_speed);
}

STATE_Fn_Define(DC_Busy){
	DC_State_ID = DC_Busy;
	P_DC_state = STATE(DC_Idle);
	printf("DC_Busy state speed=%d\n", DC_speed);
}
