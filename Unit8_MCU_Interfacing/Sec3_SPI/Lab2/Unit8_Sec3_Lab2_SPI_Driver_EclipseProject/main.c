#include "atmega32_spi.h"
#include "util/delay.h"

void sendCommand(uint8 cmd, uint8 data) {
	MCAL_GPIO_writePin(GPIOB, GPIO_PIN_4, LOGIC_LOW);
	MCAL_SPI_sendData(&cmd, SPI_POLLING_ENABLED);
	MCAL_SPI_sendData(&data, SPI_POLLING_ENABLED);
	MCAL_GPIO_writePin(GPIOB, GPIO_PIN_4, LOGIC_HIGH);
}

int main(void) {
	SPI_Config spi;
	uint8 counter = 0;
	uint8 index;

	spi.frameFormat = SPI_FRAME_FORMAT_MSB;
	spi.clockPhase = SPI_CLK_PHASE_EDGE1;
	spi.clockPolarity = SPI_CLK_POLARITY_LOW_IDLE;
	spi.baudRatePrescaler = SPI_BAUDRATE_PRESCALER_16;
	spi.IRQ_enable = SPI_IRQ_ENABLE_NONE;
	spi.deviceMode = SPI_DEVICE_MODE_MASTER;

	MCAL_SPI_init(&spi);

	sendCommand(0x09, 0xFF); // Decode Mode: Code B decode for digits 7–0
	sendCommand(0x0A, 0xFF); // Intensity: max on
	sendCommand(0x0B, 0xF7); // Scan Limit: Display digits 0 1 2 3 4 5 6 7
	sendCommand(0x0C, 0x01); // Normal Operation
	for (;;) {
		for (index = 1; index < 9; index++) {
			sendCommand(index, counter++);
			_delay_ms(1000);
		}
	}
}
