//*****************************************************************************
//
// Module: ATMEGA32
//
// File Name: atmega32.h
//
// Description: Header file for the ATmega32
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef ATMEGA32_H_
#define ATMEGA32_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "std_types.h"

//*******************************************************************************
// Base addresses for BUS Peripherals
//*******************************************************************************
#define GPIOA_BASE (uint8)0x39
#define GPIOB_BASE (uint8)0x36
#define GPIOC_BASE (uint8)0x33
#define GPIOD_BASE (uint8)0x30

//*******************************************************************************
// Peripheral register
//*******************************************************************************
// Peripheral register: GPIO
typedef struct {
	volatile uint8 PIN;
	volatile uint8 DDR;
	volatile uint8 PORT;
} GPIO_TypeDef;

//*******************************************************************************
// Peripheral Instants
//*******************************************************************************
#define SREG *(volatile uint8 *)(0x5F)

// EXTI
#define GICR *(volatile uint8 *)(0x5B)
#define INT1    7
#define INT0    6
#define INT2    5
#define IVSEL   1
#define IVCE    0

#define GIFR *(volatile uint8 *)(0x5A)
#define INTF1   7
#define INTF0   6
#define INTF2   5

#define MCUCR *(volatile uint8 *)(0x55)
#define SE      7
#define SM2     6
#define SM1     5
#define SM0     4
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

#define MCUCSR *(volatile uint8 *)(0x54)
#define JTD     7
#define ISC2    6

// UART
#define UBRRH *(volatile uint8 *)(0x40)
#define UCSRC *(volatile uint8 *)(0x40)
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

#define UDR *(volatile uint8 *)(0x2C)
#define UCSRA *(volatile uint8 *)(0x2B)
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

#define UCSRB *(volatile uint8 *)(0x2A)
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

#define UBRRL *(volatile uint8 *)(0x29)

// SPI
#define SPDR *(volatile uint8 *)(0x2F)

#define SPSR *(volatile uint8 *)(0x2E)
#define SPIF    7
#define WCOL    6
/* bits 5-1 reserved */
#define SPI2X   0

#define SPCR *(volatile uint8 *)(0x2D)
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

// GPIO
#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef*) GPIOD_BASE)

//*******************************************************************************
// Definitions
//*******************************************************************************
//EXTI IRQ Number
#define EXTI0_IRQ			2
#define EXTI1_IRQ			3
#define EXTI2_IRQ			4

//USART IRQ Number
#define UART_IRQ_RXC        14 // USART, Rx Complete
#define UART_IRQ_UDRE       15 // USART, Data Register Empty
#define UART_IRQ_TXC        16 // USART, Tx Complete

#define SPI_IRQ_STC         13 // SPI, Serial Transfer Complete

//*******************************************************************************
// Generic Macros
//*******************************************************************************
//EXTI IRQ Enable/Disable
#define IRQ2_EXTI0_ENABLE  	    	(GICR |= (1<<INT0))
#define IRQ3_EXTI1_ENABLE   		(GICR |= (1<<INT1))
#define IRQ4_EXTI2_ENABLE   		(GICR |= (1<<INT2))

#define IRQ2_EXTI0_DISABLE  	    (GICR &= ~(1<<INT0))
#define IRQ3_EXTI1_DISABLE   		(GICR &= ~(1<<INT1))
#define IRQ4_EXTI2_DISABLE   		(GICR &= ~(1<<INT2))

//USART IRQ Enable/Disable
#define IRQ14_UART_RXC_ENABLE  	    (UCSRB |= (1<<RXCIE))
#define IRQ15_UART_UDRE_ENABLE   	(UCSRB |= (1<<TXCIE))
#define IRQ16_UART_TXC_ENABLE   	(UCSRB |= (1<<UDRIE))

#define IRQ14_UART_RXC_DISABLE  	(UCSRB &= ~(1<<RXCIE))
#define IRQ15_UART_UDRE_DISABLE   	(UCSRB &= ~(1<<TXCIE))
#define IRQ16_UART_TXC_DISABLE   	(UCSRB &= ~(1<<UDRIE))

//SPI IRQ Enable/Disable
#define IRQ13_SPI_STC_ENABLE  	    (SPCR |= (1<<SPIE))

#define IRQ13_SPI_STC_DISABLE  	    (SPCR &= ~(1<<SPIE))

#endif // ATMEGA32_H_
