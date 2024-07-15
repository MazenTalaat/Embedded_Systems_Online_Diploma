//*****************************************************************************
//
// Module: USART
//
// File Name: atmega32_usart.c
//
// Description: Source file for the USART driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32_usart.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
void (*UART_GP_IRQ_callBack[3])(void);

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the UART device
// @param[in]  UART_config  The needed configuration.
void MCAL_UART_init(UART_Config *UART_config) {
	uint16 ubrr_value = 0;

	// double transmission speed
	UCSRA = (1 << U2X);

	// Bit 4 – RXEN: Receiver Enable
	// Bit 3 – TXEN: Transmitter Enable
	UCSRB = UART_config->mode;

	// Bit 5:4 – UPM1:0: Parity Mode
	// Bit 3 – USBS: Stop Bit Select
	// Bit 2:1 – UCSZ1:0: Character Size
	UCSRC = (1 << URSEL) | UART_config->payloadLength | UART_config->parity
			| UART_config->stopBits;

	// Calculate the UBRR register value
	ubrr_value = (uint16) (((F_CPU / (UART_config->baudRate * 8UL))) - 1);

	// First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH
	UBRRH = ubrr_value >> 8;
	UBRRL = ubrr_value;

	if (UART_config->IRQ_enable) {
		UCSRB |= UART_config->IRQ_enable;
		switch (UART_config->IRQ_enable) {
		case UART_IRQ_ENABLE_RXC:
			UART_GP_IRQ_callBack[0] = UART_config->P_IRQ_callBack;
			IRQ14_UART_RXC_ENABLE;
			break;
		case UART_IRQ_ENABLE_UDRE:
			UART_GP_IRQ_callBack[1] = UART_config->P_IRQ_callBack;
			IRQ15_UART_UDRE_ENABLE;
			break;
		case UART_IRQ_ENABLE_TXC:
			UART_GP_IRQ_callBack[2] = UART_config->P_IRQ_callBack;
			IRQ16_UART_TXC_ENABLE;
			break;
		default:
			break;
		}
	}
}

// @brief Reset the UART.
void MCAL_UART_deInit(void) {
	IRQ14_UART_RXC_DISABLE;
	IRQ15_UART_UDRE_DISABLE;
	IRQ16_UART_TXC_DISABLE;

	UCSRA = 0;
	UCSRB = 0;
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) | 0;

	UBRRH = 0;
	UBRRL = 0;
}

// @brief Responsible for send byte to another UART device.
// @param[in]  UART_config  The needed configuration.
// @param[in]  pTxBuffer  The data to be sent.
// @param[in]  pollingEn  Whether to send by polling or not.
void MCAL_UART_sendData(UART_Config *UART_config, uint16 *pTxBuffer,
		uint8 pollingEn) {

	// Wait for Tx buffer (UDR) to be empty
	if (pollingEn)
		while (BIT_IS_CLEAR(UCSRA, UDRE))
			;

	// Send the data
	UDR = (*pTxBuffer & (uint8) 0xFF);
}

// @brief Responsible for receive byte from another UART device.
// @param[in]  UART_config  The needed configuration.
// @param[out] pRxBuffer  The data to be received.
// @param[in]  pollingEn  Whether to receive by polling or not.
void MCAL_UART_receiveData(UART_Config *UART_config, uint16 *pRxBuffer,
		uint8 pollingEn) {
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	if (pollingEn)
		while (BIT_IS_CLEAR(UCSRA, RXC))
			;

	 // Read the received data from the Rx buffer (UDR)
	 // The RXC flag will be cleared after read the data
	*((uint16*) pRxBuffer) = (UDR & (uint8) 0xFF);
}

//*****************************************************************************
// ISR Functions Definitions
//*****************************************************************************
ISR(USART_RXC_vect){
	UART_GP_IRQ_callBack[0]();
}

ISR(USART_UDRE_vect){
	UART_GP_IRQ_callBack[1]();
}

ISR(USART_TXC_vect){
	UART_GP_IRQ_callBack[2]();
}
