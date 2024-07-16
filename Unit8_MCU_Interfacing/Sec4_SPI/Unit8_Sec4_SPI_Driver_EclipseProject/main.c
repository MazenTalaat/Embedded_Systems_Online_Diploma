#include "atmega32_spi.h"
#include "lcd.h"
#include "util/delay.h"

//#define MASTER
#define SLAVE

int main(void) {
	SPI_Config spi;
	uint8 buff = 0;
	uint8 counter = 0;
	uint8 ch = 'A';

	LCD_init();
	LCD_clearScreen();

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

#ifdef MASTER
	LCD_displayString((uint8*) "Master  ");
	for (;;) {
		LCD_moveCursor(0, 9);
		LCD_intgerToString(counter++);
		LCD_moveCursor(1, 0);
		buff = MCAL_SPI_sendRecieve(ch, SPI_POLLING_ENABLED);
		LCD_intgerToString(buff);
		ch++;
		if (ch > 'Z') {
			ch = 'A';
		}
		_delay_ms(1000);
	}
#endif

#ifdef SLAVE
	LCD_displayString((uint8*) "Slave  ");
	for (;;) {
		LCD_moveCursor(1, 0);
		buff = MCAL_SPI_sendRecieve(0xFF, SPI_POLLING_ENABLED);
		LCD_displayCharacter(buff);
		LCD_moveCursor(0, 9);
		LCD_intgerToString(counter++);
	}
#endif
}
