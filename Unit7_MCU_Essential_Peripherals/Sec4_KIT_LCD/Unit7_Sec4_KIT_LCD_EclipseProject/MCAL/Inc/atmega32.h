/*
 * ATMEGA32.h
 *
 *  Created on: Jul 9, 2024
 *      Author: Mazen Talaat
 */

#ifndef ATMEGA32_H_
#define ATMEGA32_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                      Base addresses for BUS Peripherals                     *
 *******************************************************************************/
#define GPIOA_BASE (uint8)0x39
#define GPIOB_BASE (uint8)0x36
#define GPIOC_BASE (uint8)0x33
#define GPIOD_BASE (uint8)0x30

/*******************************************************************************
 *                           Peripheral register                               *
 *******************************************************************************/
/* Peripheral register: GPIO */
typedef struct {
	volatile uint8 PIN;
	volatile uint8 DDR;
	volatile uint8 PORT;
} GPIO_TypeDef;

/*******************************************************************************
 *                           Peripheral Instants                               *
 *******************************************************************************/
#define SREG *(volatile uint8 *)(0x5F)

#define GICR *(volatile uint8 *)(0x5B)
#define GIFR *(volatile uint8 *)(0x5A)

#define MCUCR *(volatile uint8 *)(0x55)
#define MCUCSR *(volatile uint8 *)(0x54)

#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef*) GPIOD_BASE)

/*******************************************************************************
 *                           Definitions                                       *
 *******************************************************************************/
//EXTI IRQ Number
#define 	EXTI0_IRQ			2
#define 	EXTI1_IRQ			3
#define 	EXTI2_IRQ			4

/*******************************************************************************
 *                           Generic Macros                                    *
 *******************************************************************************/
#define IRQ2_EXTI0_ENABLE  	    	(GICR |= (1<<6))
#define IRQ3_EXTI1_ENABLE   		(GICR |= (1<<7))
#define IRQ4_EXTI2_ENABLE   		(GICR |= (1<<5))

#define IRQ2_EXTI0_DISABLE  	    (GICR &= ~(1<<6))
#define IRQ3_EXTI1_DISABLE   		(GICR &= ~(1<<7))
#define IRQ4_EXTI2_DISABLE   		(GICR &= ~(1<<5))

#endif /* ATMEGA32_H_ */
