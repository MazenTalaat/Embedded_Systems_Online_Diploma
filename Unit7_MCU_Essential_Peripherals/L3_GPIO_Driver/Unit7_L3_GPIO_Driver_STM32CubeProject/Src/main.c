#include "stm32f103c6.h"
#include "stm32f103c6_gpio.h"
#include "std_types.h"

void delay(int n) {
	int i;
	for (i = 0; i < n; i++)
		;
}

int main(void) {
	/* Enable GPIOA, GPIOB Clock */
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

	/* Configure LEDs at PB1, PB13 negative logic as Output Open-drain 2 MHz*/
	GPIO_PinConfig LED_1 = { GPIO_PIN_1, GPIO_MODE_OUT_OPEN_DRAIN,
	GPIO_OUTPUT_SPEED_2MHZ };
	GPIO_PinConfig LED_2 = { GPIO_PIN_13, GPIO_MODE_OUT_OPEN_DRAIN,
	GPIO_OUTPUT_SPEED_2MHZ };
	MCAL_GPIO_init(GPIOB, &LED_1);
	MCAL_GPIO_init(GPIOB, &LED_2);
	/* Turn off the LEDs */
	MCAL_GPIO_writePin(GPIOB, GPIO_PIN_1, LOGIC_HIGH);
	MCAL_GPIO_writePin(GPIOB, GPIO_PIN_13, LOGIC_HIGH);

	/* Configure PBs at PA1 pulled up, PA13 pulled down as Input floating */
	GPIO_PinConfig BP_1 = { GPIO_PIN_1, GPIO_MODE_IN_FLOATING };
	GPIO_PinConfig BP_2 = { GPIO_PIN_13, GPIO_MODE_IN_FLOATING };
	MCAL_GPIO_init(GPIOA, &BP_1);
	MCAL_GPIO_init(GPIOA, &BP_2);

	uint8 button1Pressed = 0;
	/* Loop forever */
	for (;;) {
		if ((MCAL_GPIO_readPin(GPIOA, GPIO_PIN_1) == 0) && !button1Pressed) {
			MCAL_GPIO_togglePin(GPIOB, GPIO_PIN_1);
			button1Pressed = 1;
		} else if (MCAL_GPIO_readPin(GPIOA, GPIO_PIN_1) == 1) {
			button1Pressed = 0;
		}

		if (MCAL_GPIO_readPin(GPIOA, GPIO_PIN_13) == 1) {
			MCAL_GPIO_togglePin(GPIOB, GPIO_PIN_13);
			delay(5000);
		}
	}
}
