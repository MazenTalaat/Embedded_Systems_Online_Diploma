/*
 * DC.h
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"

/* States */
enum{
	DC_Idle,
	DC_Busy
}DC_State_ID;

/* State functions */
STATE_Fn_Define(DC_Idle);
STATE_Fn_Define(DC_Busy);

/* Global pointer to fn */
extern void (*P_DC_state)();

void DC_Motor_Set(int);

void DC_Init();

#endif /* DC_H_ */
