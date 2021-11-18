/*
 *	 	Created on: Nov 17, 2021
 *	 	Author: Mazen Talaat
 *		LED_Init.h
 */
#include "Platform_Types.h"

#ifndef _LED_INIT_H_
#define _LED_INIT_H_

/* Registers Bases     */
#define SYSCTL_BASE        0x400FE000     /* System CLK       */
#define GPIO_PORTF_BASE    0x40025000     /* GPIO for port F  */

/* Registers Offsets   */
#define SYSCTL_RCGC2_R_OFFSET    0x108    /* Peripheral CLK   */
#define GPIO_PORTF_DATA_R_OFFSET 0x3FC    /* Port F Data      */
#define GPIO_PORTF_DIR_R_OFFSET  0x400 	  /* Port F Direction */
#define GPIO_PORTF_DEN_R_OFFSET  0x51C    /* Port F Enable    */

/* Registers Locations */
#define SYSCTL_RCGC2_R 	   *(vuint32_t *)(SYSCTL_BASE     + SYSCTL_RCGC2_R_OFFSET   )
#define GPIO_PORTF_DIR_R   *(vuint32_t *)(GPIO_PORTF_BASE + GPIO_PORTF_DIR_R_OFFSET )
#define GPIO_PORTF_DATA_R  *(vuint32_t *)(GPIO_PORTF_BASE + GPIO_PORTF_DATA_R_OFFSET)
#define GPIO_PORTF_DEN_R   *(vuint32_t *)(GPIO_PORTF_BASE + GPIO_PORTF_DEN_R_OFFSET )

/* Functions           */
void LED_Init(int);
void LED_On(int);
void LED_Off(int);

#endif
