/*
 * US.h
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#ifndef US_H_
#define US_H_

#include "state.h"

/* States */
enum{
	US_Busy
}US_State_ID;

int US_Get_Distance_Random(int l, int r);

/* State functions */
STATE_Fn_Define(US_Busy);

/* Global pointer to fn */
extern void (*P_US_state)();

void US_Init();

#endif /* US_H_ */
