//*****************************************************************************
//
// Module: GPIO
//
// File Name: stm32f103c8_gpio.h
//
// Description: Header file for the GPIO driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

#ifndef stm32f103c8_GPIO_H_
#define stm32f103c8_GPIO_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c8.h"
#include "std_types.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct{
	uint16 GPIO_pinNumber;
	uint8  GPIO_pinMode;
	uint8  GPIO_pinOutputSpeed;
}GPIO_PinConfig;

//*****************************************************************************
// Definitions
//*****************************************************************************
#define GPIO_NUM_OF_PORTS           4
#define GPIO_NUM_OF_PINS_PER_PORT   16

#define GPIO_CRLH_CNF_SHIFT			2

#define GPIO_PIN_0                 ((uint16)0x0001)  // Pin 0 selected    
#define GPIO_PIN_1                 ((uint16)0x0002)  // Pin 1 selected    
#define GPIO_PIN_2                 ((uint16)0x0004)  // Pin 2 selected    
#define GPIO_PIN_3                 ((uint16)0x0008)  // Pin 3 selected    
#define GPIO_PIN_4                 ((uint16)0x0010)  // Pin 4 selected    
#define GPIO_PIN_5                 ((uint16)0x0020)  // Pin 5 selected    
#define GPIO_PIN_6                 ((uint16)0x0040)  // Pin 6 selected    
#define GPIO_PIN_7                 ((uint16)0x0080)  // Pin 7 selected    
#define GPIO_PIN_8                 ((uint16)0x0100)  // Pin 8 selected    
#define GPIO_PIN_9                 ((uint16)0x0200)  // Pin 9 selected    
#define GPIO_PIN_10                ((uint16)0x0400)  // Pin 10 selected   
#define GPIO_PIN_11                ((uint16)0x0800)  // Pin 11 selected   
#define GPIO_PIN_12                ((uint16)0x1000)  // Pin 12 selected   
#define GPIO_PIN_13                ((uint16)0x2000)  // Pin 13 selected   
#define GPIO_PIN_14                ((uint16)0x4000)  // Pin 14 selected   
#define GPIO_PIN_15                ((uint16)0x8000)  // Pin 15 selected   
#define GPIO_PIN_All               ((uint16)0xFFFF)  // All pins selected 

//In input mode (MODE[1:0]=00):
//00: Analog mode
//01: Floating input (reset state)
//10: Input with pull-up / pull-down
//11: Reserved
//In output mode (MODE[1:0] > 00):
//00: General purpose output push-pull
//01: General purpose output Open-drain
//10: Alternate function output Push-pull
//11: Alternate function output Open-drain

// GPIO_Mode_define 
#define GPIO_MODE_IN_ANALOG 			((uint8)0x00)
#define GPIO_MODE_IN_FLOATING			((uint8)0x01)
#define GPIO_MODE_IN_PULL_UP 			((uint8)0x02)
#define GPIO_MODE_IN_PULL_DOWN 			((uint8)0x03)

#define GPIO_MODE_OFFSET				((uint8)0x04)

#define GPIO_MODE_OUT_PUSH_PULL 		((uint8)0x04)
#define GPIO_MODE_OUT_OPEN_DRAIN 		((uint8)0x05)
#define GPIO_MODE_OUT_AF_PUSH_PULL 		((uint8)0x06)
#define GPIO_MODE_OUT_AF_OPEN_DRAIN 	((uint8)0x07)

//#define GPIO_MODE_IN_AF 				((uint8)0x08) // To be considered as GPIO_MODE_IN_FLOATING

// GPIO_OutputSpeed_define 
#define GPIO_OUTPUT_SPEED_10MHZ 		((uint8)0x01)
#define GPIO_OUTPUT_SPEED_2MHZ			((uint8)0x02)
#define GPIO_OUTPUT_SPEED_50MHZ 		((uint8)0x03)

//*****************************************************************************
// GPIO APIs Prototypes
//*****************************************************************************
void MCAL_GPIO_init(GPIO_TypeDef* GPIOx, GPIO_PinConfig* pinConfig);
void MCAL_GPIO_deInit(GPIO_TypeDef* GPIOx);

uint8 MCAL_GPIO_readPin(GPIO_TypeDef* GPIOx, uint16 pinNumber);
uint16 MCAL_GPIO_readPort(GPIO_TypeDef* GPIOx);

void MCAL_GPIO_writePin(GPIO_TypeDef* GPIOx, uint16 pinNumber, uint8 value);
void MCAL_GPIO_writePort(GPIO_TypeDef* GPIOx, uint16 value);

void MCAL_GPIO_togglePin(GPIO_TypeDef* GPIOx, uint16 pinNumber);

uint8 MCAL_GPIO_lockPin	(GPIO_TypeDef* GPIOx , uint16 pinNumber);

#endif // stm32f103c8_GPIO_H_ 
