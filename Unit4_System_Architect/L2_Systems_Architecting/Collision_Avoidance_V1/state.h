/*
 * state.h
 *
 *  Created on: Nov 24, 2021
 *      Author: Mazen Talaat
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"

#define STATE_Fn_Define(_StatFunction_) void ST_##_StatFunction_()
#define STATE(_StatFunction_) ST_##_StatFunction_

#endif /* STATE_H_ */
