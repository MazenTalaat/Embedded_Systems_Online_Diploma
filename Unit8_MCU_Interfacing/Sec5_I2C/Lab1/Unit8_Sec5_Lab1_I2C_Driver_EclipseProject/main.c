#include "atmega32_I2C.h"
#include "atmega32_gpio.h"
#include "util/delay.h"

//#define MASTER
#define SLAVE

uint8 data = 0;

void I2CCallback(uint8 ev) {
	if(ev == I2C_EV_DATA_RX){
		MCAL_I2C_slaveRx(&data);
	}
}

int main(void) {
	I2C_Config I2C;

#ifdef MASTER
	I2C.deviceMode = I2C_DEVICE_MODE_MASTER;
	I2C.clkSpeed = I2C_CLK_SPEED_400KHZ;
	I2C.generalCallAddressDetection = I2C_GCAD_DISABLE;
	I2C.ACK_control = I2C_ACK_CONTROL_DISABLE;
	I2C.IRQ_enable = I2C_IRQ_NONE;

	MCAL_I2C_init(&I2C);
	while (1) {
		_delay_ms(500);
		MCAL_I2C_masterTx(0b01101000, &data, 1, I2C_STOP_WITH, I2C_START_NORMAL);
		data++;
	}
#endif

#ifdef SLAVE
	GPIO_PinConfig segment = {GPIO_PIN_All, GPIO_MODE_OUT};
	MCAL_GPIO_init(GPIOA, &segment);

	I2C.deviceMode = I2C_DEVICE_MODE_SLAVE;
	I2C.clkSpeed = I2C_CLK_SPEED_400KHZ;
	I2C.generalCallAddressDetection = I2C_GCAD_DISABLE;
	I2C.ACK_control = I2C_ACK_CONTROL_ENABLE;
	I2C.IRQ_enable = I2C_IRQ_ENABLE;
	I2C.P_IRQ_callBack = I2CCallback;
	I2C.slaveAddress = 0b01101000;

	IRQ_GLOBAL_ENABLE;

	MCAL_I2C_init(&I2C);
	while (1) {
		MCAL_GPIO_writePort(GPIOA, data);
	}
#endif
}
