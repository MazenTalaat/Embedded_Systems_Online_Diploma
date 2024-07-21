//*****************************************************************************
//
// Module: GPIO
//
// File Name: atmega32_gpio.h
//
// Description: Header file for the GPIO driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef ATMEGA32_GPIO_H_
#define ATMEGA32_GPIO_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32.h"
#include "std_types.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct{
	uint8 GPIO_pinNumber;
	uint8  GPIO_pinMode;
}GPIO_PinConfig;

//*****************************************************************************
// Definitions
//*****************************************************************************
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define GPIO_PIN_0                 ((uint8)0x01)  // Pin 0 selected   
#define GPIO_PIN_1                 ((uint8)0x02)  // Pin 1 selected   
#define GPIO_PIN_2                 ((uint8)0x04)  // Pin 2 selected   
#define GPIO_PIN_3                 ((uint8)0x08)  // Pin 3 selected   
#define GPIO_PIN_4                 ((uint8)0x10)  // Pin 4 selected   
#define GPIO_PIN_5                 ((uint8)0x20)  // Pin 5 selected   
#define GPIO_PIN_6                 ((uint8)0x40)  // Pin 6 selected   
#define GPIO_PIN_7                 ((uint8)0x80)  // Pin 7 selected   
#define GPIO_PIN_All               ((uint8)0xFF)  // All pins selected

// GPIO_Mode_define
#define GPIO_MODE_IN_PULL_UP 			((uint8)0x01)
#define GPIO_MODE_IN_FLOATING 			((uint8)0x02)

#define GPIO_MODE_OUT			 		((uint8)0x03)

//*****************************************************************************
// GPIO APIs Prototypes
//*****************************************************************************
void MCAL_GPIO_init(GPIO_TypeDef* GPIOx, GPIO_PinConfig* pinConfig);
void MCAL_GPIO_deInit(GPIO_TypeDef* GPIOx);

uint8 MCAL_GPIO_readPin(GPIO_TypeDef* GPIOx, uint8 pinNumber);
uint8 MCAL_GPIO_readPort(GPIO_TypeDef* GPIOx);

void MCAL_GPIO_writePin(GPIO_TypeDef* GPIOx, uint8 pinNumber, uint8 value);
void MCAL_GPIO_writePort(GPIO_TypeDef* GPIOx, uint8 value);

void MCAL_GPIO_togglePin(GPIO_TypeDef* GPIOx, uint8 pinNumber);

#endif // ATMEGA32_GPIO_H_
