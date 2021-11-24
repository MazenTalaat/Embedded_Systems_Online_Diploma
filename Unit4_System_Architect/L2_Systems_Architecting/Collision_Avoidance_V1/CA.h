/*
 * CA.h
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"

/* States */
enum{
	CA_Waiting,
	CA_Driving
}CA_State_ID;

/* State functions */
STATE_Fn_Define(CA_Waiting);
STATE_Fn_Define(CA_Driving);

/* Global pointer to fn */
extern void (*P_CA_state)();

int US_Get_Distance_Random(int l, int r);

#endif /* CA_H_ */
