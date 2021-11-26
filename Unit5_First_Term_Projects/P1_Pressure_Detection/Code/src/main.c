/*
 * main.c
 *
 * Created on: Nov 26, 2021
 * Author: Mazen Talaat
 */

#include "driver.h"
#include "Pressure_Controller.h"
#include "Alarm_Controller.h"
#include "Pressure_Sensor.h"

/* Pressure_Controller states: waiting, alarm *
 * Pressure_Sensor     states: busy           *
 * Alarm_Controller    states: idle, busy     */
 
void setup(){
	AC_Init();
	PS_Init();
	P_PC_state = STATE(PC_Waiting);
	P_AC_state = STATE(AC_Idle);
	P_PS_state = STATE(PS_Busy);
}

int main (){
	GPIO_INITIALIZATION();
	setup();
	while (1)
	{
		P_PS_state();
		P_PC_state();
		P_AC_state();
	}
	return 0;
}
