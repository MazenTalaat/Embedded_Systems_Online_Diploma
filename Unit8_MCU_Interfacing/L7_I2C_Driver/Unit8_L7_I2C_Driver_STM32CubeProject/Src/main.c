#include "eeprom_i2c.h"

int main(void) {
	// Test Case 1
	uint8 ch1[] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7 };
	uint8 ch2[7] = { 0 };

	EEPROM_init();
	EEPROM_writeBytes(0xAF, ch1, 7);
	EEPROM_readBytes(0xAF, ch2, 7);

	// Test case 2
	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;

	EEPROM_writeBytes(0xFFF, ch1, 4);
	EEPROM_readBytes(0xFFF, ch2, 4);

	for (;;) {

	}
}
