//*****************************************************************************
//
// Module: GPIO
//
// File Name: stm32f103c6_gpio.c
//
// Description: Source file for the GPIO driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c6_gpio.h"

//*****************************************************************************
// Helper Functions Declaration
//*****************************************************************************
static int isOutput(GPIO_PinConfig *pinConfig);
static uint8 getCRLH_Position(uint16 pinNumber);

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Setup the mode of the required pin/port.
// @param[in]  GPIOx  The port to be configured.
// @param[in]  pinConfig  The pin/port configuration.
void MCAL_GPIO_init(GPIO_TypeDef *GPIOx, GPIO_PinConfig *pinConfig) {
	uint32 portConfigValue = (uint32) 0;
	uint8 pinConfigValue = (uint8) 0;
	uint8 i = 0;
	// Configure port
	if (pinConfig->GPIO_pinNumber == GPIO_PIN_All) {
		// Reset GPIO_ODR
		MCAL_GPIO_writePort(GPIOx, LOGIC_LOW);
		// Setting the 32 Bits for CRH and CRL Registers
		for (i = 0; i < 32; i += 4) {
			// OUTPUT MODE
			if (isOutput(pinConfig)) {
				portConfigValue |= (((((pinConfig->GPIO_pinMode
						- GPIO_MODE_OFFSET) << GPIO_CRLH_CNF_SHIFT)
						| pinConfig->GPIO_pinOutputSpeed) & 0x0F) << i);
			}
			// INPUT MODE
			else {
				if (pinConfig->GPIO_pinMode == GPIO_MODE_IN_ANALOG
						|| pinConfig->GPIO_pinMode == GPIO_MODE_IN_FLOATING) {
					portConfigValue |= ((((pinConfig->GPIO_pinMode
							<< GPIO_CRLH_CNF_SHIFT) | 0x00) & 0x0F) << i);
				} else {
					portConfigValue |= ((((GPIO_MODE_IN_PULL_UP
							<< GPIO_CRLH_CNF_SHIFT) | 0x00) & 0x0F) << i);
				}
			}
		}
		// Configure the whole port using CRL and CRH
		GPIOx->CRL = portConfigValue;
		GPIOx->CRH = portConfigValue;
		// Configure input pull-up or pull-down
		// Table 20. Port bit configuration table
		// PxODR register -> 1 for pull-up, 0 for pull-down
		if (pinConfig->GPIO_pinMode == GPIO_MODE_IN_PULL_UP) {
			MCAL_GPIO_writePort(GPIOx, 0xFFFF);
		} else if (pinConfig->GPIO_pinMode == GPIO_MODE_IN_PULL_DOWN) {
			MCAL_GPIO_writePort(GPIOx, LOGIC_LOW);
		}
	}
	// Configure a pin
	else {
		// Reset GPIO_ODR
		MCAL_GPIO_writePin(GPIOx, pinConfig->GPIO_pinNumber,
		LOGIC_LOW);
		// OUTPUT MODE
		if (isOutput(pinConfig)) {
			pinConfigValue = ((((pinConfig->GPIO_pinMode - GPIO_MODE_OFFSET)
					<< GPIO_CRLH_CNF_SHIFT) | pinConfig->GPIO_pinOutputSpeed)
					& 0x0F);
		}
		// INPUT MODE
		else {
			if (pinConfig->GPIO_pinMode == GPIO_MODE_IN_ANALOG
					|| pinConfig->GPIO_pinMode == GPIO_MODE_IN_FLOATING) {
				pinConfigValue = (((pinConfig->GPIO_pinMode
						<< GPIO_CRLH_CNF_SHIFT) | 0x00) & 0x0F);
			} else {
				pinConfigValue = (((GPIO_MODE_IN_PULL_UP << GPIO_CRLH_CNF_SHIFT)
						| 0x00) & 0x0F);
				// Configure input pull-up or pull-down
				// Table 20. Port bit configuration table
				// PxODR register -> 1 for pull-up, 0 for pull-down
				if (pinConfig->GPIO_pinMode == GPIO_MODE_IN_PULL_DOWN) {
					MCAL_GPIO_writePin(GPIOx, pinConfig->GPIO_pinNumber,
					LOGIC_LOW);
				} else {
					MCAL_GPIO_writePin(GPIOx, pinConfig->GPIO_pinNumber,
					LOGIC_HIGH);
				}
			}
		}
		if (pinConfig->GPIO_pinNumber <= GPIO_PIN_7) {
			// Configure using CRL
			// Clear CNF and MODE
			GPIOx->CRL &= ~(0xF << getCRLH_Position(pinConfig->GPIO_pinNumber));
			GPIOx->CRL |= (pinConfigValue
					<< getCRLH_Position(pinConfig->GPIO_pinNumber));
		} else {
			// Configure using CRH
			// Clear CNF and MODE
			GPIOx->CRH &= ~(0xF << getCRLH_Position(pinConfig->GPIO_pinNumber));
			GPIOx->CRH |= (pinConfigValue
					<< getCRLH_Position(pinConfig->GPIO_pinNumber));
		}
	}
}

// @brief Reset the port configuration.
// @param[in]  GPIOx  The port to be reset.
void MCAL_GPIO_deInit(GPIO_TypeDef *GPIOx) {
	if (GPIOx == GPIOA) {
		RCC->APB2RSTR |= (1 << 2);  //Bit 2 IOPARST: IO port A reset
		RCC->APB2RSTR &= ~(1 << 2);

	} else if (GPIOx == GPIOB) {
		RCC->APB2RSTR |= (1 << 3);  //Bit 3 IOPBRST: IO port B reset
		RCC->APB2RSTR &= ~(1 << 3);

	} else if (GPIOx == GPIOC) {
		RCC->APB2RSTR |= (1 << 4);  //Bit 4 IOPCRST: IO port C reset
		RCC->APB2RSTR &= ~(1 << 4);

	} else if (GPIOx == GPIOD) {
		RCC->APB2RSTR |= (1 << 5);  //Bit 5 IOPDRST: IO port D reset
		RCC->APB2RSTR &= ~(1 << 5);
	}
}

// @brief Read the pin value.
// @param[in]  GPIOx  The port to be used.
// @param[in]  pinNumber  The pin number.
// @return The pin value.
uint8 MCAL_GPIO_readPin(GPIO_TypeDef *GPIOx, uint16 pinNumber) {
	if ((GPIOx->IDR & pinNumber) == LOGIC_LOW) {
		return LOGIC_LOW;
	} else {
		return LOGIC_HIGH;
	}
	return LOGIC_LOW;
}

// @brief Read the port value.
// @param[in]  GPIOx  The port to be read.
// @return The port value.
uint16 MCAL_GPIO_readPort(GPIO_TypeDef *GPIOx) {
	return (uint16) (GPIOx->IDR & 0xFFFF);
}

// @brief Set a pin to a value.
// @param[in]  GPIOx  The port to be used.
// @param[in]  pinNumber  The pin number.
// @param[in]  value  The value to be set.
void MCAL_GPIO_writePin(GPIO_TypeDef *GPIOx, uint16 pinNumber, uint8 value) {
	if (value == LOGIC_LOW) {
		GPIOx->ODR &= ~pinNumber;
	} else {
		GPIOx->ODR |= pinNumber;
	}
}

// @brief Set a port to a value.
// @param[in]  GPIOx  The port to be set.
// @param[in]  value  The value to be set.
void MCAL_GPIO_writePort(GPIO_TypeDef *GPIOx, uint16 value) {
	GPIOx->ODR = (uint32) value;
}

// @brief Toggle a pin.
// @param[in]  GPIOx  The port to be used.
// @param[in]  pinNumber  The pin number.
void MCAL_GPIO_togglePin(GPIO_TypeDef *GPIOx, uint16 pinNumber) {
	GPIOx->ODR ^= pinNumber;
}

// @brief Lock a pin.
// @param[in]  GPIOx  The port to be used.
// @param[in]  pinNumber  The pin number.
uint8 MCAL_GPIO_lockPin(GPIO_TypeDef *GPIOx, uint16 pinNumber) {
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)

	// Bit 16 LCKK[16]: Lock key
	// This bit can be read any time. It can only be modified using the Lock Key Writing Sequence.
	// 0: Port configuration lock key not active
	// 1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	volatile uint32 tmp = (1 << 16);
	GPIOx->LCKR |= (pinNumber | tmp);
	GPIOx->LCKR &= ~(tmp);
	GPIOx->LCKR |= (pinNumber | tmp);
	tmp = GPIOx->LCKR;
	tmp = GPIOx->LCKR;
	if (tmp & (1 << 16)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//*****************************************************************************
// Helper Functions Definitions
//*****************************************************************************
// @brief Check if the configuration is output.
// @param[in]  pinConfig  The pin/port configuration.
// @return The 1 or 0.
static int isOutput(GPIO_PinConfig *pinConfig) {
	if (pinConfig->GPIO_pinMode == GPIO_MODE_OUT_PUSH_PULL
			|| pinConfig->GPIO_pinMode == GPIO_MODE_OUT_OPEN_DRAIN
			|| pinConfig->GPIO_pinMode == GPIO_MODE_OUT_AF_PUSH_PULL
			|| pinConfig->GPIO_pinMode == GPIO_MODE_OUT_AF_OPEN_DRAIN) {
		return 1;
	} else {
		return 0;
	}
	return 0;
}

// @brief Get the shift position in CRL and CRH registers.
// @param[in]  pinNumber  The pin number.
// @return The shift position value.
static uint8 getCRLH_Position(uint16 pinNumber) {
	switch (pinNumber) {
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}
