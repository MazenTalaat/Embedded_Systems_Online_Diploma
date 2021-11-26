/*
 * Pressure_Sensor.c
 *
 * Created on: Nov 26, 2021
 * Author: Mazen Talaat
 */

#include "Pressure_Sensor.h"

int PS_pressure = 0;

void (*P_PS_state)() = 0;

void PS_Init(){
	/* Do some stuff */
}

STATE_Fn_Define(PS_Busy){
	PS_State_ID = PS_Busy;
	PS_pressure = getPressureVal();
	PS_Set_Pressure(PS_pressure);
	P_PS_state = STATE(PS_Busy);
	Delay(100000);
}
