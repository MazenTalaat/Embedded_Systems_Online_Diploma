#include "stm32f103c6_usart.h"
#include "stm32f103c6_spi.h"
#include "stm32f103c6_gpio.h"

//#define MASTER
#define SLAVE

uint16 buff = 0;
#ifdef MASTER
void UART_IRQ_Callback() {

	MCAL_UART_receiveData(USART1, &buff, UART_POLLING_DISABLED);
	MCAL_UART_sendData(USART1, &buff, UART_POLLING_ENABLED);

	MCAL_GPIO_writePin(GPIOA, GPIO_PIN_4, LOGIC_LOW);
	MCAL_SPI_sendRecieve(SPI1, &buff, SPI_POLLING_ENABLED);
	MCAL_GPIO_writePin(GPIOA, GPIO_PIN_4, LOGIC_HIGH);
}
#endif

#ifdef SLAVE
void SPI_IRQ_Callback() {
	MCAL_SPI_sendRecieve(SPI1, &buff, SPI_POLLING_DISABLED);
	MCAL_UART_sendData(USART1, &buff, UART_POLLING_ENABLED);
}
#endif

int main(void) {

	UART_Config uart1;
	SPI_Config spi1;
	GPIO_PinConfig ss;

	uart1.baudRate = UART_BAUDRATE_115200;
	uart1.hwFlowCtl = UART_HWFLOWCTL_NONE;
#ifdef MASTER
	uart1.IRQ_enable = UART_IRQ_ENABLE_RXNE;
	uart1.P_IRQ_callBack = UART_IRQ_Callback;
#endif
#ifdef SLAVE
	uart1.IRQ_enable = UART_IRQ_ENABLE_NONE;
	uart1.P_IRQ_callBack = NULL_PTR;
#endif
	uart1.parity = UART_PARITY_NONE;
	uart1.payloadLength = UART_PAYLOAD_LENGTH_8BITS;
	uart1.stopBits = UART_STOPBITS_1;
	uart1.mode = UART_MODE_TX_RX;

	MCAL_UART_init(USART1, &uart1);
	MCAL_UART_GPIO_setPins(USART1);

	spi1.clockPhase = SPI_CLK_PHASE_EDGE2;
	spi1.clockPolarity = SPI_CLK_POLARITY_HIGH_IDLE;
	spi1.dataSize = SPI_DATA_SIZE_8BITS;
	spi1.frameFormat = SPI_FRAME_FORMAT_MSB;
	spi1.baudRatePrescaler = SPI_BAUDRATE_PRESCALER_8;
	spi1.commMode = SPI_COMM_MODE_2LINES;

#ifdef MASTER
	spi1.deviceMode = SPI_DEVICE_MODE_MASTER;
	spi1.IRQ_enable = SPI_IRQ_ENABLE_NONE;
	spi1.P_IRQ_callBack = NULL_PTR;
	spi1.NSS = SPI_NSS_SW_INTERNAL_SS_SET;

	ss.GPIO_pinNumber = GPIO_PIN_4;
	ss.GPIO_pinMode = GPIO_MODE_OUT_PUSH_PULL;
	ss.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_init(GPIOA, &ss);

	MCAL_GPIO_writePin(GPIOA, GPIO_PIN_4, LOGIC_HIGH);
#endif

#ifdef SLAVE
	spi1.deviceMode = SPI_DEVICE_MODE_SLAVE;
	spi1.IRQ_enable = SPI_IRQ_ENABLE_RXNEIE;
	spi1.P_IRQ_callBack = SPI_IRQ_Callback;
	spi1.NSS = SPI_NSS_HW_SLAVE;
#endif

	MCAL_SPI_init(SPI1, &spi1);
	MCAL_SPI_GPIO_setPins(SPI1);
	for (;;) {
	}
}
