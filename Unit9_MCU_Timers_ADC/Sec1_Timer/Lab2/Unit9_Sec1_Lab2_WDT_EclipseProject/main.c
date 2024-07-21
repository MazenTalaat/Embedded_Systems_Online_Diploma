#include "atmega32_gpio.h"
#include "atmega32_wdt.h"
#include "util/delay.h"

int main(void) {
	GPIO_PinConfig led = { GPIO_PIN_6, GPIO_MODE_OUT };
	MCAL_GPIO_init(GPIOD, &led);

	_delay_ms(1000);

	MCAL_GPIO_writePin(GPIOD, GPIO_PIN_6, LOGIC_HIGH);

	MCAL_WDT_init(WDT_TIME_2_1s);

	for (;;)
		;
}
