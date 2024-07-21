#include "atmega32_tim0.h"
#include "atmega32_gpio.h"

uint32 CTC_counter = 0;
uint8 counter = 0;

void TIM0_callback() {
	if (CTC_counter == 521) {
		CTC_counter = 0;
		MCAL_GPIO_writePort(GPIOA, ++counter);
	}
	CTC_counter++;
}

int main(void) {
	GPIO_PinConfig segment = { GPIO_PIN_All, GPIO_MODE_OUT };
	MCAL_GPIO_init(GPIOA, &segment);

	TIM0_Config tim0;
	tim0.clkSelect = TIM0_CLK_SELECT_8;
	tim0.mode = TIM0_MODE_CTC;
	tim0.IRQ_enable = TIM0_IRQ_OUTPUT_COMPARE;
	tim0.P_IRQ_callBack = TIM0_callback;

	MCAL_TIM0_setCompareValue(240);
	MCAL_TIM0_init(&tim0);

	IRQ_GLOBAL_ENABLE;

	for (;;)
		;
}
