/*
 * main.c
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#include "CA.h"
#include "DC.h"
#include "US.h"

void setup(){
	DC_Init();
	US_Init();
	P_CA_state = STATE(CA_Waiting);
	P_DC_state = STATE(DC_Idle);
	P_US_state = STATE(US_Busy);
}

int main(){
	volatile int i;
	setup();
	while(1){
		P_US_state();
		P_CA_state();
		P_DC_state();
		for(i=0; i<1000000; i++);
	}
	return 0;
}
