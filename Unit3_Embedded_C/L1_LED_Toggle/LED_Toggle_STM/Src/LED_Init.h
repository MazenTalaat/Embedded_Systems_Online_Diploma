/*
 *	 	Created on: Nov 5, 2021
 *	 	Author: Mazen Talaat
 *		LED_Init.h
 */
#include "Platform_Types.h"

#ifndef _LED_INIT_H_
#define _LED_INIT_H_

/* Registers Bases     */
#define RCC_BASE      0x40021000   /* Reset and control */
#define GPIOA_BASE    0x40010800   /* GPIO for port A   */

/* Registers Offsets   */
#define RCC_APB2ENR_OFFSET   0x18  /* Peripheral CLK */
#define GPIOA_CRH_OFFSET     0x04  /* Speed of pins 8-15 of the port  */
#define GPIOA_ODR_OFFSET     0x0C  /* Output Data register for port A */

/* Registers Locations */
#define RCC_APB2ENR *(vuint32_t *)(RCC_BASE   + RCC_APB2ENR_OFFSET )
#define GPIOA_CRH   *(vuint32_t *)(GPIOA_BASE + GPIOA_CRH_OFFSET   )
#define GPIOA_ODR   *(vuint32_t *)(GPIOA_BASE + GPIOA_ODR_OFFSET   )

/* Registers Bits      */
#define RCC_IOPAEN (1<<2)
#define CRH_Mode2  (2<<20)

/* Functions           */
void LED_Init();
void LED_On(int);
void LED_Off(int);

#endif
