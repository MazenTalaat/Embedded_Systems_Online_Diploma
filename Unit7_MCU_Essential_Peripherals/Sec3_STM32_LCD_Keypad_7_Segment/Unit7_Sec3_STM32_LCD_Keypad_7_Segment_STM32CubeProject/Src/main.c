#include "stm32f103c6.h"
#include "stm32f103c6_gpio.h"
#include "std_types.h"
#include "delay.h"
#include "lcd.h"
#include "keypad.h"
#include "seven_segment.h"

int main(void) {
	uint8 num = 0;
	uint8 state = 0;
	uint8 key = 0;

	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

	LCD_init();
	SEVEN_SEGMENT_Config sig1 = { GPIOB, GPIO_PIN_9, SEVEN_SEGMENT_TYPE_COM_AN };
	SEVEN_SEGMENT_init(&sig1);
	SEVEN_SEGMENT_turnOff(&sig1);

	LCD_displayString("Hello");
	_delay_ms(500);
	LCD_clearScreen();

	for (;;) {
		switch (state) {
		case 0:
			LCD_intgerToString(num);
			SEVEN_SEGMENT_display(&sig1, num++);
			if (num > 9) {
				SEVEN_SEGMENT_display(&sig1, 8);
				state = 1;
			}
			_delay_ms(500);
			break;
		case 1:
			LCD_clearScreen();
			LCD_displayString("Keypad is ready");
			_delay_ms(1000);
			LCD_clearScreen();
			state = 2;
			break;
		case 2:
			key = KEYPAD_getPressedKey();
			if((key>=0) && (key<=9)){
				LCD_intgerToString(key);
				SEVEN_SEGMENT_display(&sig1, key);
			}
			else{
				LCD_displayCharacter(key);
			}
			_delay_ms(200);
		default:
			break;
		}

	}
}
