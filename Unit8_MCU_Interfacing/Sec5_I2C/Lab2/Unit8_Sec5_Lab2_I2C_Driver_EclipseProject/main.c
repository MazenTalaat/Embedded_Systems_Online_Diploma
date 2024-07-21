#include "atmega32_I2C.h"
#include "atmega32_gpio.h"
#include "util/delay.h"

//#define MASTER
#define SLAVE

uint8 data = 0;

int main(void) {
	I2C_Config I2C;

#ifdef MASTER
	GPIO_PinConfig segment = {GPIO_PIN_All, GPIO_MODE_OUT};
	MCAL_GPIO_init(GPIOA, &segment);

	I2C.deviceMode = I2C_DEVICE_MODE_MASTER;
	I2C.clkSpeed = I2C_CLK_SPEED_400KHZ;
	I2C.generalCallAddressDetection = I2C_GCAD_DISABLE;
	I2C.ACK_control = I2C_ACK_CONTROL_ENABLE;
	I2C.IRQ_enable = I2C_IRQ_NONE;

	MCAL_I2C_init(&I2C);
	while (1) {
		_delay_ms(500);
		MCAL_I2C_masterRx(0b01101000, &data, 1, I2C_STOP_WITH, I2C_START_NORMAL);
		MCAL_GPIO_writePort(GPIOA, data);
	}
#endif

#ifdef SLAVE
	I2C.deviceMode = I2C_DEVICE_MODE_SLAVE;
	I2C.clkSpeed = I2C_CLK_SPEED_400KHZ;
	I2C.generalCallAddressDetection = I2C_GCAD_DISABLE;
	I2C.ACK_control = I2C_ACK_CONTROL_ENABLE;
	I2C.IRQ_enable = I2C_IRQ_NONE;
	I2C.slaveAddress = 0b01101000;

	MCAL_I2C_init(&I2C);
	while (1) {
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while (!I2C_getFlagStatus(I2C_FLAG_TWINT))
			;
		TWDR = data++;
		TWCR = (1 << TWINT) | (1 << TWEN);
		while (!I2C_getFlagStatus(I2C_FLAG_TWINT))
			;
	}
#endif
}
