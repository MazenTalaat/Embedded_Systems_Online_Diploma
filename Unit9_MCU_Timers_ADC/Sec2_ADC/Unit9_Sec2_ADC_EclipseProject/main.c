#include "lcd.h"
#include "lm35_sensor.h"
#include "atmega32_adc.h"

int main(void) {
	float temp;
	LCD_init();

	ADC_Config adc;
	adc.IRQ_enable = ADC_IRQ_ENABLE;
	adc.P_IRQ_callBack = NULL_PTR;
	adc.refVolatge = ADC_REF_VOLT_AVCC;
	adc.clkSelect = ADC_CLK_SELECT_8;

	MCAL_ADC_init(&adc);

	LCD_displayString((uint8*) "Temp =    C");

	IRQ_GLOBAL_ENABLE;

	for (;;) {

		temp = LM35_getTemperature();

		LCD_moveCursor(0, 7);
		if (temp >= 100) {
			LCD_intgerToString(temp);
		} else {
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
	}
}
