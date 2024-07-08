#include "lcd.h"
#include "keypad.h"
#include <util/delay.h> /* For the delay functions */

void calculator(void) {
	unsigned char key, op;
	int n1 = 0, n2 = 0;

	LCD_clearScreen();
	// Get the first number
	while (1) {
		key = KEYPAD_getPressedKey();
		if ((key <= 9) && (key >= 0)) {
			LCD_intgerToString(key);
			n1 = key + n1 * 10;
		} else if (key == '~') {
			return;
		} else if (key == '=') {
			continue;
		} else {
			break;
		}
		_delay_ms(200);
	}

	_delay_ms(200);
	// Get the operation
	LCD_displayCharacter(key);
	op = key;

	// Get the second number
	while (1) {
		key = KEYPAD_getPressedKey();
		if ((key <= 9) && (key >= 0)) {
			LCD_intgerToString(key);
			n2 = key + n2 * 10;
		} else if (key == '~') {
			return;
		} else if (key == '=') {
			break;
		}
		_delay_ms(200);
	}

	// calculate the result
	switch (op) {
	case '+':
		n2 = n1 + n2;
		break;
	case '-':
		n2 = n1 - n2;
		break;
	case '/':
		n2 = n1 / n2;
		break;
	case '*':
		n2 = n1 * n2;
		break;
	default:

		break;
	}
	LCD_displayCharacter('=');

	// Handle the negative sign
	if (n2 < 0) {
		LCD_displayCharacter('-');
		n2 = -1 * n2;
	}

	// show the result
	LCD_intgerToString(n2);

	// wait of ON to be pressed
	while (KEYPAD_getPressedKey() != '~') {
		_delay_ms(15);
	}
	_delay_ms(250);
}

int main(void) {

	LCD_init();

	while (1) {
		calculator();
	}
}
