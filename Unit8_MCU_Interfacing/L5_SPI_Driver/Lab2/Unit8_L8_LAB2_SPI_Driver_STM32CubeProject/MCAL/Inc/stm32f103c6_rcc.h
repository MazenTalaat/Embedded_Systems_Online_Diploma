//*****************************************************************************
//
// Module: RCC
//
// File Name: stm32f103c6_rcc.h
//
// Description: Header file for the RCC driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

#ifndef STM32F103C6_RCC_H_
#define STM32F103C6_RCC_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c6.h"
#include "std_types.h"

//*****************************************************************************
// Definitions
//*****************************************************************************
#define HSE_CLOCK			(uint32)16000000
#define HSI_CLOCK			(uint32)8000000

//*****************************************************************************
// Generic macros
//*****************************************************************************
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
#define RCC_AHB_PRESCALER_MAPPING(pre)			(((pre)==0b0000)?1:\
										 	 	 ((pre)==0b1000)?2:\
										 	 	 ((pre)==0b1001)?8:\
												 ((pre)==0b1011)?16:\
										 	 	 ((pre)==0b1100)?64:\
												 ((pre)==0b1101)?128:\
										 	 	 ((pre)==0b1110)?256:\
										 	 	 ((pre)==0b1111)?512:0)
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
#define RCC_APB_PRESCALER_MAPPING(pre)			(((pre)==0b000)?1:\
										 	 	 ((pre)==0b100)?2:\
										 	 	 ((pre)==0b101)?4:\
												 ((pre)==0b110)?8:\
										 	 	 ((pre)==0b111)?16:0)

//*******************************************************************************
// Clock Enable Macros
//*******************************************************************************
#define RCC_AFIO_CLK_EN()	( RCC->APB2ENR |= (1<<0) )

#define RCC_GPIOA_CLK_EN()	( RCC->APB2ENR |= (1<<2) )
#define RCC_GPIOB_CLK_EN()	( RCC->APB2ENR |= (1<<3) )
#define RCC_GPIOC_CLK_EN()	( RCC->APB2ENR |= (1<<4) )
#define RCC_GPIOD_CLK_EN()	( RCC->APB2ENR |= (1<<5) )

#define RCC_USART1_CLK_EN()	( RCC->APB2ENR |= (1<<14) )
#define RCC_USART2_CLK_EN()	( RCC->APB1ENR |= (1<<17) )
#define RCC_USART3_CLK_EN()	( RCC->APB1ENR |= (1<<18) )

#define RCC_SPI1_CLK_EN()	( RCC->APB2ENR |= (1<<12) )
#define RCC_SPI2_CLK_EN()	( RCC->APB1ENR |= (1<<14) )

//*******************************************************************************
// Clock disable Macros
//*******************************************************************************
#define RCC_USART1_RESET()	( RCC->APB2RSTR |= (1<<14) )
#define RCC_USART2_RESET()	( RCC->APB1RSTR |= (1<<17) )
#define RCC_USART3_RESET()	( RCC->APB1RSTR |= (1<<18) )

#define RCC_SPI1_RESET()	( RCC->APB2RSTR |= (1<<12) )
#define RCC_SPI2_RESET()	( RCC->APB1RSTR |= (1<<14) )

//*****************************************************************************
// Functions Prototypes
//*****************************************************************************
uint32 MCAL_RCC_getSysCLKFreq(void);
uint32 MCAL_RCC_getHCLKFreq(void);
uint32 MCAL_RCC_getPCLK1Freq(void);
uint32 MCAL_RCC_getPCLK2Freq(void);

#endif // STM32F103C6_RCC_H_
