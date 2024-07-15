//*****************************************************************************
//
// Module: STM32F103C6
//
// File Name: stm32f103c6.h
//
// Description: Header file for the STM32F103C6
//
// Author: Mazen Talaat
//
//*****************************************************************************

#ifndef STM32F103C6_H_
#define STM32F103C6_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "std_types.h"

//*******************************************************************************
// Base addresses for memory
//*******************************************************************************
#define FLASH_MEMORY_BASE 	0x08000000UL
#define SRAM_BASE 			0x20000000UL
#define SYS_MEMORY_BASE		0x1FFFF000UL

//*******************************************************************************
// NVIC register map
//*******************************************************************************
#define NVIC_Base			(0xE000E100UL)
#define NVIC_ISER0			*(volatile uint32 *)(NVIC_Base + 0x0)
#define NVIC_ISER1			*(volatile uint32 *)(NVIC_Base + 0x4)
#define NVIC_ISER2			*(volatile uint32 *)(NVIC_Base + 0x8)
#define NVIC_ICER0			*(volatile uint32 *)(NVIC_Base + 0x80)
#define NVIC_ICER1			*(volatile uint32 *)(NVIC_Base + 0x84)
#define NVIC_ICER2			*(volatile uint32 *)(NVIC_Base + 0x88)

//*******************************************************************************
// Base addresses for BUS Peripherals
//*******************************************************************************
#define PERIPHERALS_BASE 			0x40000000UL
#define INTERNAL_PERIPHERALS_BASE 	0xE0000000UL

//*******************************************************************************
// Base addresses for AHB BUS Peripherals
//*******************************************************************************
#define RCC_BASE 	0x40021000UL

//*******************************************************************************
// Base addresses for APB2 BUS Peripherals
//*******************************************************************************
// FULL INCLUDED
#define GPIOA_BASE 	0x40010800UL
#define GPIOB_BASE 	0x40010C00UL
// PARTIAL INCLUDED
#define GPIOC_BASE 	0x40011000UL
#define GPIOD_BASE 	0x40011400UL
// NOT INCLUDED IN THE PACKAGE
//#define GPIOG_BASE 0x40012000UL
//#define GPIOF_BASE 0x40011C00UL
//#define GPIOE_BASE 0x40011800UL

#define AFIO_BASE 	0x40010000UL
#define EXTI_BASE 	0x40010400UL

#define USART1_BASE 0x40013800UL

#define SPI1_BASE 	0x40013000UL

//*******************************************************************************
// Base addresses for APB1 BUS Peripherals
//*******************************************************************************
#define USART2_BASE 0x40004400UL
#define USART3_BASE 0x40004800UL

#define SPI2_BASE 	0x40003800UL
// NOT INCLUDED IN THE PACKAGE
// #define SPI3_BASE 	0x40003C00UL

//*******************************************************************************
// Peripheral register
//*******************************************************************************
// Peripheral register: RCC
typedef struct {
	volatile uint32 CR;
	volatile uint32 CFGR;
	volatile uint32 CIR;
	volatile uint32 APB2RSTR;
	volatile uint32 APB1RSTR;
	volatile uint32 AHBENR;
	volatile uint32 APB2ENR;
	volatile uint32 APB1ENR;
	volatile uint32 BDCR;
	volatile uint32 CSR;
	volatile uint32 AHBSTR;
	volatile uint32 CFGR2;
} RCC_TypeDef;

// Peripheral register: GPIO
typedef struct {
	volatile uint32 CRL;
	volatile uint32 CRH;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 BRR;
	volatile uint32 LCKR;
} GPIO_TypeDef;

// Peripheral register: AFIO
typedef struct {
	volatile uint32 EVCR;
	volatile uint32 MAPR;
	volatile uint32 EXTICR[4];
	uint32 RESERVED0;
	volatile uint32 MAPR2;
} AFIO_TypeDef;

// Peripheral register: EXTI
typedef struct {
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RTSR;
	volatile uint32 FTSR;
	volatile uint32 SWIER;
	volatile uint32 PR;
} EXTI_TypeDef;

// Peripheral register: USART
typedef struct {
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 BRR;
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 CR3;
	volatile uint32 GTPR;
} USART_TypeDef;

// Peripheral register: SPI
typedef struct {
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 CRCPR;
	volatile uint32 RXCRCR;
	volatile uint32 TXCRCR;
	volatile uint32 I2SCFGR;
	volatile uint32 I2SPR;
} SPI_TypeDef;

//*******************************************************************************
// Peripheral Instants
//*******************************************************************************
#define RCC   	((RCC_TypeDef*) RCC_BASE)

#define GPIOA 	((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB 	((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC 	((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD 	((GPIO_TypeDef*) GPIOD_BASE)

#define AFIO  	((AFIO_TypeDef*) AFIO_BASE)
#define EXTI  	((EXTI_TypeDef*) EXTI_BASE)

#define USART1 	((USART_TypeDef*) USART1_BASE)
#define USART2 	((USART_TypeDef*) USART2_BASE)
#define USART3 	((USART_TypeDef*) USART3_BASE)

#define SPI1 	((SPI_TypeDef*) SPI1_BASE)
#define SPI2 	((SPI_TypeDef*) SPI2_BASE)

//*******************************************************************************
// Definitions
//*******************************************************************************
// EXTI IRQ Number
#define 	EXTI0_IRQ			6
#define 	EXTI1_IRQ			7
#define 	EXTI2_IRQ			8
#define 	EXTI3_IRQ			9
#define 	EXTI4_IRQ			10
#define 	EXTI5_IRQ			23
#define 	EXTI6_IRQ			23
#define 	EXTI7_IRQ			23
#define 	EXTI8_IRQ			23
#define 	EXTI9_IRQ			23
#define 	EXTI10_IRQ			40
#define 	EXTI11_IRQ			40
#define 	EXTI12_IRQ			40
#define 	EXTI13_IRQ			40
#define 	EXTI14_IRQ			40
#define 	EXTI15_IRQ			40

// USART IRQ Number
#define 	USART1_IRQ			37
#define 	USART2_IRQ			38
#define 	USART3_IRQ			39

// SPI IRQ Number
#define 	SPI1_IRQ			35
#define 	SPI2_IRQ			36

//*******************************************************************************
// Generic Macros
//*******************************************************************************
// NVIC IRQ enable/disable macros:
// EXTI
#define NVIC_IRQ6_EXTI0_ENABLE  	    (NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_ENABLE   		(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_ENABLE   		(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_ENABLE   		(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_ENABLE   		(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_ENABLE   	(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_ENABLE   	(NVIC_ISER1 |= 1<<8) //40-32 = 8

#define NVIC_IRQ6_EXTI0_DISABLE  	    (NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_DISABLE   		(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_DISABLE   		(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_DISABLE   		(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_DISABLE   		(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_DISABLE   	(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_DISABLE   	(NVIC_ICER1 |= 1<<8) //40-32 = 8

// USART
#define NVIC_IRQ37_USART1_ENABLE   		(NVIC_ISER1 |= 1<<( USART1_IRQ - 32 ))
#define NVIC_IRQ38_USART2_ENABLE   		(NVIC_ISER1 |= 1<<( USART2_IRQ - 32 ))
#define NVIC_IRQ39_USART3_ENABLE   		(NVIC_ISER1 |= 1<<( USART3_IRQ - 32 ))

#define NVIC_IRQ37_USART1_DISABLE   	(NVIC_ICER1 |= 1<<( USART1_IRQ - 32 ))
#define NVIC_IRQ38_USART2_DISABLE   	(NVIC_ICER1 |= 1<<( USART2_IRQ - 32 ))
#define NVIC_IRQ39_USART3_DISABLE   	(NVIC_ICER1 |= 1<<( USART3_IRQ - 32 ))

// SPI
#define NVIC_IRQ35_SPI1_ENABLE   		(NVIC_ISER1 |= 1<<( SPI1_IRQ - 32 ))
#define NVIC_IRQ36_SPI2_ENABLE   		(NVIC_ISER1 |= 1<<( SPI2_IRQ - 32 ))

#define NVIC_IRQ35_SPI1_DISABLE   		(NVIC_ICER1 |= 1<<( SPI1_IRQ - 32 ))
#define NVIC_IRQ36_SPI2_DISABLE   		(NVIC_ICER1 |= 1<<( SPI2_IRQ - 32 ))

#endif // STM32F103C6_H_
