#include "stm32f103c6.h"
#include "stm32f103c6_exti.h"
#include "lcd.h"

void EXTI9_callback(void){
	LCD_displayString("Hello IRQ EXTI9");
}

int main(void) {
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	LCD_init();
	LCD_clearScreen();

	EXTI_PinConfig PB1 = { EXTI9PB9, EXTI_TRIGGER_FALLING, EXTI_IRQ_ENABLE, EXTI9_callback };
	MCAL_EXTI_init(&PB1);

	for (;;) {

	}
}
