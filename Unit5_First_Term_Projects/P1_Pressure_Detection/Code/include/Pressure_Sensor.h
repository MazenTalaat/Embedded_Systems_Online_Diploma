/*
 * Pressure_Sensor.h
 *
 * Created on: Nov 26, 2021
 * Author: Mazen Talaat
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#define STATE_Fn_Define(_StatFunction_) void ST_##_StatFunction_()
#define STATE(_StatFunction_) ST_##_StatFunction_

/* States */
enum{
	PS_Busy
}PS_State_ID;

/* State functions */
STATE_Fn_Define(PS_Busy);

/* Global pointer to fn */
extern void (*P_PS_state)();

void PS_Init();

#endif /* PRESSURE_SENSOR_H_ */
