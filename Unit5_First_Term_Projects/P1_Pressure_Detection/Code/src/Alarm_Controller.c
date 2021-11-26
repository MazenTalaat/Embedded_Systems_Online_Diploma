/*
 * Alarm_Controller.c
 *
 * Created on: Nov 26, 2021
 * Author: Mazen Talaat
 */

#include "Alarm_Controller.h"

void (*P_AC_state)() = 0;

void AC_Init(){
	Set_Alarm_actuator(1);
}

STATE_Fn_Define(AC_Idle){
	AC_State_ID = AC_Idle;
	P_AC_state = STATE(AC_Idle);
}

STATE_Fn_Define(AC_Busy){
	AC_State_ID = AC_Busy;
	P_AC_state = STATE(AC_Idle);
}
