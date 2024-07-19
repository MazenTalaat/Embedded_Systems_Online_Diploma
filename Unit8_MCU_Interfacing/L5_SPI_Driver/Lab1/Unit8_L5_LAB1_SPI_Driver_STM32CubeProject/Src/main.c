#include "stm32f103c6_usart.h"
#include "stm32f103c6_spi.h"
#include "stm32f103c6_gpio.h"

uint16 buff = 0;
void UART_IRQ_Callback() {
	MCAL_UART_receiveData(USART1, &buff, UART_POLLING_DISABLED);
	MCAL_UART_sendData(USART1, &buff, UART_POLLING_ENABLED);

	MCAL_GPIO_writePin(GPIOA, GPIO_PIN_4, LOGIC_LOW);
	MCAL_SPI_sendRecieve(SPI1, &buff, SPI_POLLING_ENABLED);
	MCAL_GPIO_writePin(GPIOA, GPIO_PIN_4, LOGIC_HIGH);
}

int main(void) {

	UART_Config uart1;
	SPI_Config spi1;

	uart1.baudRate = UART_BAUDRATE_115200;
	uart1.hwFlowCtl = UART_HWFLOWCTL_NONE;
	uart1.IRQ_enable = UART_IRQ_ENABLE_RXNE;
	uart1.P_IRQ_callBack = UART_IRQ_Callback;
	uart1.parity = UART_PARITY_NONE;
	uart1.payloadLength = UART_PAYLOAD_LENGTH_8BITS;
	uart1.stopBits = UART_STOPBITS_1;
	uart1.mode = UART_MODE_TX_RX;

	MCAL_UART_init(USART1, &uart1);
	MCAL_UART_GPIO_setPins(USART1);

	spi1.clockPhase =SPI_CLK_PHASE_EDGE1;
	spi1.clockPolarity = SPI_CLK_POLARITY_HIGH_IDLE;
	spi1.dataSize = SPI_DATA_SIZE_8BITS;
	spi1.frameFormat = SPI_FRAME_FORMAT_MSB;
	spi1.baudRatePrescaler = SPI_BAUDRATE_PRESCALER_8;
	spi1.commMode = SPI_COMM_MODE_2LINES;

	spi1.deviceMode = SPI_DEVICE_MODE_MASTER;
	spi1.IRQ_enable = SPI_IRQ_ENABLE_NONE;
	spi1.NSS = SPI_NSS_HW_MASTER_OUTPUT_SET;

	MCAL_SPI_init(SPI1, &spi1);
	MCAL_SPI_GPIO_setPins(SPI1);

	for (;;) {

	}
}
