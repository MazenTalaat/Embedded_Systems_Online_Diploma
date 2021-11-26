/*
 * Pressure_Controller.c
 *
 * Created on: Nov 26, 2021
 * Author: Mazen Talaat
 */

#include "Pressure_Controller.h"

/* Variables */
int PC_pressure = 0;
int PC_pressure_threshold = 20;

void (*P_PC_state)() = 0;

void PS_Set_Pressure(int p){
	PC_pressure = p;
	(PC_pressure <= PC_pressure_threshold) ? (P_PC_state = STATE(PC_Waiting)) : (P_PC_state = STATE(PC_Alarm));
}

STATE_Fn_Define(PC_Waiting){
	PC_State_ID = PC_Waiting;
	Set_Alarm_actuator(1);
}

STATE_Fn_Define(PC_Alarm){
	PC_State_ID = PC_Alarm;
	Set_Alarm_actuator(0);
	/* Wait 60s */
	Delay(6000000);
	Set_Alarm_actuator(1);
}
