/*
 * Pressure_Controller.h
 *
 * Created on: Nov 26, 2021
 * Author: Mazen Talaat
 */

#ifndef PRESSURE_CONTROLLER_H_
#define PRESSURE_CONTROLLER_H_

#define STATE_Fn_Define(_StatFunction_) void ST_##_StatFunction_()
#define STATE(_StatFunction_) ST_##_StatFunction_

/* States */
enum{
	PC_Waiting,
	PC_Alarm
}PC_State_ID;

/* State functions */
STATE_Fn_Define(PC_Waiting);
STATE_Fn_Define(PC_Alarm);

/* Global pointer to fn */
extern void (*P_PC_state)();

#endif /* PRESSURE_CONTROLLER_H_ */
