/*
 * Alarm_Controller.h
 *
 * Created on: Nov 26, 2021
 * Author: Mazen Talaat
 */

#ifndef ALARM_CONTROLLER_H_
#define ALARM_CONTROLLER_H_

#define STATE_Fn_Define(_StatFunction_) void ST_##_StatFunction_()
#define STATE(_StatFunction_) ST_##_StatFunction_

/* States */
enum{
	AC_Idle,
	AC_Busy
}AC_State_ID;

/* State functions */
STATE_Fn_Define(AC_Idle);
STATE_Fn_Define(AC_Busy);

/* Global pointer to fn */
extern void (*P_AC_state)();

void AC_Init();

#endif /* ALARM_CONTROLLER_H_ */
