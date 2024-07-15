#include "atmega32_usart.h"
#include "lcd.h"

UART_Config uart1;
uint16 buff = 0;

void UART_IRQ_Callback(void) {
	MCAL_UART_receiveData(&uart1, &buff, UART_POLLING_DISABLED);
	MCAL_UART_sendData(&uart1, &buff, UART_POLLING_ENABLED);
	LCD_displayCharacter(buff);
}

int main(void) {
	LCD_init();

	uart1.baudRate = UART_BAUDRATE_9600;
	uart1.IRQ_enable = UART_IRQ_ENABLE_RXC;
	uart1.P_IRQ_callBack = UART_IRQ_Callback;
	uart1.parity = UART_PARITY_NONE;
	uart1.payloadLength = UART_PAYLOAD_LENGTH_8BITS;
	uart1.stopBits = UART_STOPBITS_1;
	uart1.mode = UART_MODE_TX_RX;

	MCAL_UART_init(&uart1);

	SREG |= (1 << 7);

	for (;;)
		;

	return 0;
}
