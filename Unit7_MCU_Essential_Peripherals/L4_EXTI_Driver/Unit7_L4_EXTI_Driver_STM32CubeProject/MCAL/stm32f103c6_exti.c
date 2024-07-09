/*
 * stm32f103c6_exti.c
 *
 *  Created on: Jul 9, 2024
 *      Author: Mazen Talaat
 */

#include "stm32f103c6_exti.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
void (*GP_IRQ_callBack[15])(void);

void NVIC_enableEXTI(uint16 IRQ) {
	switch (IRQ) {
	case 0:
		NVIC_IRQ6_EXTI0_ENABLE;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_ENABLE;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_ENABLE;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_ENABLE;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_ENABLE;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_ENABLE;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_ENABLE;
		break;
	}
}

void NVIC_disableEXTI(uint16 IRQ) {
	switch (IRQ) {
	case 0:
		NVIC_IRQ6_EXTI0_DISABLE;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_DISABLE;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_DISABLE;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_DISABLE;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_DISABLE;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_DISABLE;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_DISABLE;
		break;
	}
}

void MCAL_EXTI_init(EXTI_PinConfig *EXTI_config) {
	// AFIO_EXTICRx register index
	uint8 EXTICR_index = EXTI_config->EXTI_pin.EXTI_inputLine / 4;
	// Shift value for register AFIO_EXTICRx
	uint8 EXTICR_shift = (EXTI_config->EXTI_pin.EXTI_inputLine % 4) * 4;

	// Configure pin as input floating
	GPIO_PinConfig pinConfig = { GPIO_MODE_IN_FLOATING,
			EXTI_config->EXTI_pin.pinNumber };
	MCAL_GPIO_init(EXTI_config->EXTI_pin.GPIO_port, &pinConfig);

	// Clear and set value
	AFIO->EXTICR[EXTICR_index] &= ~(0xF << EXTICR_shift);
	AFIO->EXTICR[EXTICR_index] |=
			(AFIO_EXTI_MAPPING(EXTI_config->EXTI_pin.GPIO_port) << EXTICR_shift);

	// Reset triggers
	EXTI->FTSR &= ~(0x1 << EXTI_config->EXTI_pin.EXTI_inputLine);
	EXTI->RTSR &= ~(0x1 << EXTI_config->EXTI_pin.EXTI_inputLine);

	// Set triggers
	if (EXTI_config->triggerCase == EXTI_TRIGGER_RISING) {
		EXTI->RTSR |= (1 << EXTI_config->EXTI_pin.EXTI_inputLine);

	} else if (EXTI_config->triggerCase == EXTI_TRIGGER_FALLING) {
		EXTI->FTSR |= (1 << EXTI_config->EXTI_pin.EXTI_inputLine);

	} else if (EXTI_config->triggerCase == EXTI_TRIGGER_BOTH_EDGES) {
		EXTI->RTSR |= (1 << EXTI_config->EXTI_pin.EXTI_inputLine);
		EXTI->FTSR |= (1 << EXTI_config->EXTI_pin.EXTI_inputLine);
	}

	// Set callback
	GP_IRQ_callBack[EXTI_config->EXTI_pin.EXTI_inputLine] =
			EXTI_config->P_IRQ_callBack;

	// Enable or disable NVIC EXTI
	if (EXTI_config->IRQ_EN == EXTI_IRQ_ENABLE) {
		EXTI->IMR |= (1 << EXTI_config->EXTI_pin.EXTI_inputLine);
		NVIC_enableEXTI(EXTI_config->EXTI_pin.EXTI_inputLine);
	} else {
		EXTI->IMR &= ~(1 << EXTI_config->EXTI_pin.EXTI_inputLine);
		NVIC_disableEXTI(EXTI_config->EXTI_pin.EXTI_inputLine);
	}

}

void MCAL_EXTI_deInit(void) {
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;

	EXTI->RTSR = 0x00000000;

	EXTI->FTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;

	//rc_w1  cleared by writing a ‘1’ into the PR
	EXTI->PR = 0xFFFFFFFF;

	//Disable EXTI IRQ From NVIC
	NVIC_IRQ6_EXTI0_DISABLE;
	NVIC_IRQ7_EXTI1_DISABLE;
	NVIC_IRQ8_EXTI2_DISABLE;
	NVIC_IRQ9_EXTI3_DISABLE;
	NVIC_IRQ10_EXTI4_DISABLE;
	NVIC_IRQ23_EXTI5_9_DISABLE;
	NVIC_IRQ40_EXTI10_15_DISABLE;
}

void EXTI0_IRQHandler(void) {
	//cleared by writing a ‘1’ into the bit Pending register (EXTI_PR)
	EXTI->PR |= 1 << 0;
	//CALL IRQ_CALL
	GP_IRQ_callBack[0]();
}

void EXTI1_IRQHandler(void) {
	EXTI->PR |= (1 << 1);

	GP_IRQ_callBack[1]();
}

void EXTI2_IRQHandler(void) {
	EXTI->PR |= (1 << 2);

	GP_IRQ_callBack[2]();
}

void EXTI3_IRQHandler(void) {
	EXTI->PR |= (1 << 3);

	GP_IRQ_callBack[3]();
}

void EXTI4_IRQHandler(void) {
	EXTI->PR |= (1 << 4);
	GP_IRQ_callBack[4]();
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI->PR & 1 << 5) {
		EXTI->PR |= (1 << 5);
		GP_IRQ_callBack[5]();
	}
	if (EXTI->PR & 1 << 6) {
		EXTI->PR |= (1 << 6);
		GP_IRQ_callBack[6]();
	}
	if (EXTI->PR & 1 << 7) {
		EXTI->PR |= (1 << 7);
		GP_IRQ_callBack[7]();
	}
	if (EXTI->PR & 1 << 8) {
		EXTI->PR |= (1 << 8);
		GP_IRQ_callBack[8]();
	}
	if (EXTI->PR & 1 << 9) {
		EXTI->PR |= (1 << 9);
		GP_IRQ_callBack[9]();
	}
}

void EXTI15_10_IRQHandler(void) {
	if (EXTI->PR & 1 << 10) {
		EXTI->PR |= (1 << 10);
		GP_IRQ_callBack[10]();
	}
	if (EXTI->PR & 1 << 11) {
		EXTI->PR |= (1 << 11);
		GP_IRQ_callBack[11]();
	}
	if (EXTI->PR & 1 << 12) {
		EXTI->PR |= (1 << 12);
		GP_IRQ_callBack[12]();
	}
	if (EXTI->PR & 1 << 13) {
		EXTI->PR |= (1 << 13);
		GP_IRQ_callBack[13]();
	}
	if (EXTI->PR & 1 << 14) {
		EXTI->PR |= (1 << 14);
		GP_IRQ_callBack[14]();
	}
	if (EXTI->PR & 1 << 15) {
		EXTI->PR |= (1 << 15);
		GP_IRQ_callBack[15]();
	}
}
