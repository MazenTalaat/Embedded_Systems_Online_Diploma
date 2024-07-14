#include "lcd.h"
#include "atmega32_uart.h"

int main(void) {
	uint8 myChar = 0;
	LCD_init();
	UART_init(9600);

	for (;;){
		myChar = UART_recieveByte();
		UART_sendByte(myChar);
		LCD_displayCharacter(myChar);
	}

	return 0;
}
