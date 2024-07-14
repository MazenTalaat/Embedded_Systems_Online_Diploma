//*****************************************************************************
//
// Module: UART
//
// File Name: atmega32_uart.c
//
// Description: Source file for the UART driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32_uart.h"

//*****************************************************************************
// Functions Definitions
//*****************************************************************************

// @brief Responsible for initialize the UART device by:// 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.// 2. Enable the UART.// 3. Setup the UART baud rate.
// @param[in]  baud_rate  The baud rate to be configured.
void UART_init(uint32 baud_rate)
{
	uint16 ubrr_value = 0;

	// double transmission speed
	UCSRA = (1<<U2X);

	// Receiver Enable, Transmitter Enable
	UCSRB = (1<<RXEN) | (1<<TXEN);

	// Writing the UCSRC, 8-bit data mode
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

	// Calculate the UBRR register value
	ubrr_value = (uint16)(((F_CPU / (baud_rate * 8UL))) - 1);

	// First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}


// @brief Responsible for send byte to another UART device.
// @param[in]  data  The data to be sent.
void UART_sendByte(const uint8 data)
{
	// Wait for Tx buffer (UDR) to be empty
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	// Send the data
	UDR = data;
}


// @brief Responsible for receive byte from another UART device.
// @return The byte received.
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;
}

// @brief Send the required string through UART to the other UART device.
// @param[in] Str The string to be sent.
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	// Send the whole string
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

// @brief Receive the required string until the '#' symbol through UART from the other UART device.
// @param[out] Str The string received.
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	// Receive the first byte
	Str[i] = UART_recieveByte();

	// Receive the whole string until the '#'
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	// After receiving the whole string plus the '#', replace the '#' with '\0'
	Str[i] = '\0';
}


