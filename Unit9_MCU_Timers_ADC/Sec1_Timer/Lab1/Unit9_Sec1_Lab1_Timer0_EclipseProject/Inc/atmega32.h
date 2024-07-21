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
// bits 5-1 reserved
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

// I2C
#define TWCR *(volatile uint8 *)(0x56)
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
// bit 1 reserved
#define TWIE    0

#define TWDR    *(volatile uint8 *)(0x23)

#define TWAR *(volatile uint8 *)(0x22)
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

#define TWSR *(volatile uint8 *)(0x21)
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
// bit 2 reserved
#define TWPS1   1
#define TWPS0   0

#define TWBR    *(volatile uint8 *)(0x20)

// TIM0
#define OCR0 	*(volatile uint8 *)(0x5C)

#define TIMSK 	*(volatile uint8 *)(0x59)
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

#define TIFR 	*(volatile uint8 *)(0x58)
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0

#define TCCR0 	*(volatile uint8 *)(0x53)
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

#define TCNT0 	*(volatile uint8 *)(0x52)

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

//SPI IRQ Number
#define SPI_IRQ_STC         13 // SPI, Serial Transfer Complete

//I2C IRQ Number
#define I2C_IRQ          	20 // No description

//TIM0 IRQ Number
#define TIM0_COMP_IRQ 		11 // Timer/Counter0 Compare Match
#define TIM0_OVF_IRQ 		12 // Timer/Counter0 Overflow

//*******************************************************************************
// Generic Macros
//*******************************************************************************
// Global interrupt
#define IRQ_GLOBAL_ENABLE  	    	SREG |= (1<<7)
#define IRQ_GLOBAL_DISABLE  	    SREG &= ~(1<<7)

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

//I2C IRQ Enable/Disable
#define IRQ20_I2C_ENABLE  	    	(TWCR |= (1<<TWIE))

#define IRQ20_I2C_DISABLE  	    	(TWCR &= ~(1<<TWIE))

//TIM0 IRQ Enable/Disable
#define IRQ11_TIM0_COMP_ENABLE  	(TIMSK |= (1<<OCIE0))
#define IRQ12_TIM0_OVF_ENABLE  		(TIMSK |= (1<<TOIE0))

#define IRQ11_TIM0_COMP_DISABLE  	(TIMSK &= ~(1<<OCIE0))
#define IRQ12_TIM0_OVF_DISABLE  	(TIMSK &= ~(1<<TOIE0))

#endif // ATMEGA32_H_
