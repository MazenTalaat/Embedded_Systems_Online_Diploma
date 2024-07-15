#include "stm32f103c6_usart.h"

int main(void) {
	uint16 buff = 0;
	UART_Config uart1;

	uart1.baudRate = UART_BAUDRATE_115200;
	uart1.hwFlowCtl = UART_HWFLOWCTL_NONE;
	uart1.IRQ_enable = UART_IRQ_ENABLE_NONE;
	uart1.parity = UART_PARITY_NONE;
	uart1.payloadLength = UART_PAYLOAD_LENGTH_8BITS;
	uart1.stopBits = UART_STOPBITS_1;
	uart1.mode = UART_MODE_TX_RX;

	MCAL_UART_init(USART1, &uart1);
	MCAL_UART_GPIO_setPins(USART1, &uart1);

	for (;;) {
		// Loop-back
		MCAL_UART_receiveData(USART1, &uart1, &buff, TRUE);
		MCAL_UART_sendData(USART1, &uart1, &buff, TRUE);
	}
}
