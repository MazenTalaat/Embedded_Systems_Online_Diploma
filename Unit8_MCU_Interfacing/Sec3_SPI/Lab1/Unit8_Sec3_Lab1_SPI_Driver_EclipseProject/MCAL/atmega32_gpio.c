//*****************************************************************************
//
// Module: GPIO
//
// File Name: atmega32_gpio.c
//
// Description: Source file for the GPIO driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32_gpio.h"

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Setup the mode of the required pin/port.
// @param[in]  GPIOx  The port to be configured.
// @param[in]  pinConfig  The pin/port configuration.
void MCAL_GPIO_init(GPIO_TypeDef *GPIOx, GPIO_PinConfig *pinConfig) {
	if (pinConfig->GPIO_pinNumber == GPIO_PIN_All) {
		switch (pinConfig->GPIO_pinMode) {
		case GPIO_MODE_IN_PULL_UP:
			// DDR -> 0 Input
			// PORT -> 1 Pull-up
			GPIOx->DDR = (uint8) 0x00;
			GPIOx->PORT = (uint8) 0xFF;
			break;
		case GPIO_MODE_IN_FLOATING:
			// DDR -> 0 Input
			// PORT -> 0 Pull-down
			GPIOx->DDR = (uint8) 0x00;
			GPIOx->PORT = (uint8) 0x00;
			break;
		case GPIO_MODE_OUT:
			// DDR -> 1 Output
			GPIOx->DDR = (uint8) 0xFF;
			break;
		default:
			break;
		}
	} else {
		switch (pinConfig->GPIO_pinMode) {
		case GPIO_MODE_IN_PULL_UP:
			// DDR -> 0 Input
			// PORT -> 1 Pull-up
			GPIOx->DDR &= ~pinConfig->GPIO_pinNumber;
			GPIOx->PORT |= pinConfig->GPIO_pinNumber;
			break;
		case GPIO_MODE_IN_FLOATING:
			// DDR -> 0 Input
			// PORT -> 0 Pull-down
			GPIOx->DDR &= ~pinConfig->GPIO_pinNumber;
			GPIOx->PORT &= ~pinConfig->GPIO_pinNumber;
			break;
		case GPIO_MODE_OUT:
			// DDR -> 1 Output
			GPIOx->DDR |= pinConfig->GPIO_pinNumber;
			break;
		default:
			break;
		}
	}
}

// @brief Reset the port configuration.
// @param[in]  GPIOx  The port to be reset.
void MCAL_GPIO_deInit(GPIO_TypeDef *GPIOx) {
	// Reset values
	GPIOx->DDR = (uint8) 0xFF;
	GPIOx->PORT = (uint8) 0xFF;
}

// @brief Read the pin value.
// @param[in]  GPIOx  The port to be used.
// @param[in]  pinNumber  The pin number.
// @return The pin value.
uint8 MCAL_GPIO_readPin(GPIO_TypeDef *GPIOx, uint8 pinNumber) {
	if ((GPIOx->PIN & pinNumber) == LOGIC_LOW) {
		return LOGIC_LOW;
	} else {
		return LOGIC_HIGH;
	}
	return LOGIC_LOW;
}

// @brief Read the port value.
// @param[in]  GPIOx  The port to be read.
// @return The port value.
uint8 MCAL_GPIO_readPort(GPIO_TypeDef *GPIOx) {
	return (uint8) (GPIOx->PIN & 0xFF);
}

// @brief Set a pin to a value.
// @param[in]  GPIOx  The port to be used.
// @param[in]  pinNumber  The pin number.
// @param[in]  value  The value to be set.
void MCAL_GPIO_writePin(GPIO_TypeDef *GPIOx, uint8 pinNumber, uint8 value) {
	if (value == LOGIC_LOW) {
		GPIOx->PORT &= ~pinNumber;
	} else {
		GPIOx->PORT |= pinNumber;
	}
}

// @brief Set a port to a value.
// @param[in]  GPIOx  The port to be set.
// @param[in]  value  The value to be set.
void MCAL_GPIO_writePort(GPIO_TypeDef *GPIOx, uint8 value) {
	GPIOx->PORT = (uint8) value;
}

// @brief Toggle a pin.
// @param[in]  GPIOx  The port to be used.
// @param[in]  pinNumber  The pin number.
void MCAL_GPIO_togglePin(GPIO_TypeDef *GPIOx, uint8 pinNumber) {
	GPIOx->PORT ^= pinNumber;
}
