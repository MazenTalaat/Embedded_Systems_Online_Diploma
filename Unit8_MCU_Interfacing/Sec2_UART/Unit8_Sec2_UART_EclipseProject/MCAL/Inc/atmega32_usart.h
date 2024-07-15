//*****************************************************************************
//
// Module: USART
//
// File Name: atmega32_usart.h
//
// Description: Header file for the USART driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

#ifndef ATMEGA32_USART_H_
#define ATMEGA32_USART_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32.h"
#include "std_types.h"
#include "common_macros.h"
#include "avr/interrupt.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct {
	uint8 mode;     			// Specifies the TX/RX Mode.
	uint32 baudRate; 		    // Set baud rate
	uint8 payloadLength;		// Set pay-load number of bits.
	uint8 parity;				// Specifies the parity mode.
	uint8 stopBits;				// Specifies the number of stop bits.
	uint8 IRQ_enable;			// Enable or disable UART interrupts
	void (*P_IRQ_callBack)(void);	// Interrupt callback function
} UART_Config;

//*****************************************************************************
// Definitions
//*****************************************************************************
//UART_Mode_define
#define UART_MODE_RX                        (1 << RXEN)
#define UART_MODE_TX                       	(1 << TXEN)
#define UART_MODE_TX_RX                     ((1 << RXEN) | (1 << TXEN))

//UART_BaudRate_define
#define UART_BAUDRATE_2400                  2400
#define UART_BAUDRATE_4800                  4800
#define UART_BAUDRATE_9600                  9600
#define UART_BAUDRATE_19200                 19200
#define UART_BAUDRATE_57600                 57600
#define UART_BAUDRATE_115200                115200
#define UART_BAUDRATE_230400                230400
#define UART_BAUDRATE_250000                250000
#define UART_BAUDRATE_460800                460800
#define UART_BAUDRATE_500000                500000

// UART_Payload_Length_define  5, 6, 7, 8, or 9 data bits
// TODO support the other pay-load lengths
//#define UART_PAYLOAD_LENGTH_5BITS           0
//#define UART_PAYLOAD_LENGTH_6BITS           (1 << UCSZ0)
//#define UART_PAYLOAD_LENGTH_7BITS           (1 << UCSZ1)
#define UART_PAYLOAD_LENGTH_8BITS           ((1 << UCSZ1) | (1 << UCSZ0))
//#define UART_PAYLOAD_LENGTH_9BITS           ((1 << UCSZ2) | (1 << UCSZ1) | (1 << UCSZ0))

// UART_Parity_define
#define UART_PARITY_NONE                    0
#define UART_PARITY_EVEN                    (1 << UPM1)
#define UART_PARITY_ODD                     ((1 << UPM1) | (1 << UPM0))

// UART_StopBits_define
#define UART_STOPBITS_1                    	0
#define UART_STOPBITS_2                    	(1<<USBS)

// UART_IRQ_Enable_define
#define UART_IRQ_ENABLE_NONE                0
#define UART_IRQ_ENABLE_RXC                 (1 << RXCIE) // USART, Rx Complete
#define UART_IRQ_ENABLE_UDRE                (1 << UDRIE) // USART, Data Register Empty
#define UART_IRQ_ENABLE_TXC                 (1 << TXCIE) // USART, Tx Complete

// UART Polling
#define UART_POLLING_ENABLED                TRUE
#define UART_POLLING_DISABLED               FALSE

//*****************************************************************************
// UART APIs Prototypes
//*****************************************************************************
void UART_init(uint32 baud_rate);
void UART_sendByte(const uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str); // Receive until #

//*****************************************************************************
// USART APIs Prototypes
//*****************************************************************************
void MCAL_UART_init(UART_Config *UART_config);
void MCAL_UART_deInit(void);

void MCAL_UART_GPIO_setPins(UART_Config *UART_config);

void MCAL_UART_sendData(UART_Config *UART_config, uint16 *pTxBuffer,
		uint8 pollingEn);
void MCAL_UART_receiveData(UART_Config *UART_config, uint16 *pRxBuffer,
		uint8 pollingEn);

#endif // ATMEGA32_USART_H_
