#include "atmega32_spi.h"
#include "atmega32_gpio.h"
#include "util/delay.h"

#define MASTER
//#define SLAVE

int main(void) {
	SPI_Config spi;
	uint8 buff = 0;
	uint8 temp = 0;
	GPIO_PinConfig segments;

	spi.frameFormat = SPI_FRAME_FORMAT_MSB;
	spi.clockPhase = SPI_CLK_PHASE_EDGE1;
	spi.clockPolarity = SPI_CLK_POLARITY_LOW_IDLE;
	spi.baudRatePrescaler = SPI_BAUDRATE_PRESCALER_16;
	spi.IRQ_enable = SPI_IRQ_ENABLE_NONE;
#ifdef MASTER
	spi.deviceMode = SPI_DEVICE_MODE_MASTER;
#endif
#ifdef SLAVE
	spi.deviceMode = SPI_DEVICE_MODE_SLAVE;
#endif
	MCAL_SPI_init(&spi);

	segments.GPIO_pinMode = GPIO_MODE_OUT;
	segments.GPIO_pinNumber = GPIO_PIN_All;
	MCAL_GPIO_init(GPIOA, &segments);

#ifdef MASTER
	for (buff = 0; buff <= 255; buff++) {
		temp = buff;
		_delay_ms(1000);
		MCAL_SPI_sendRecieve(&temp, SPI_POLLING_ENABLED);
		MCAL_GPIO_writePort(GPIOA, temp);
	}
#endif

#ifdef SLAVE
	for (buff = 255; buff >= 0; buff--) {
		temp = buff;
		MCAL_SPI_sendRecieve(&temp, SPI_POLLING_ENABLED);
		MCAL_GPIO_writePort(GPIOA, temp);
	}
#endif
}
