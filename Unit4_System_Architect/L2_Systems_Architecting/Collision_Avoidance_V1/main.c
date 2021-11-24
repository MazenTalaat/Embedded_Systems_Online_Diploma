/*
 * main.c
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#include "CA.h"

void setup(){
	P_CA_state = STATE(CA_Waiting);
}

int main(){
	volatile int i;
	setup();
	while(1){
		P_CA_state();
		for(i=0; i<1000000; i++);
	}
	return 0;
}
