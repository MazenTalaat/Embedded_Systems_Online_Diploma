#include "std_types.h"
#include "atmega32.h"
#include "atmega32_gpio.h"
#include "lcd.h"

int main(void) {
	GPIO_PinConfig RW_config = { GPIO_PIN_2, GPIO_MODE_OUT };
	MCAL_GPIO_init(GPIOB, &RW_config);
	MCAL_GPIO_writePin(GPIOB, GPIO_PIN_2, LOGIC_LOW);

	LCD_init();
	LCD_clearScreen();

	LCD_displayString("learn-in-depth");
	for (;;) {

	}
}
