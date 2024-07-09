/*
 * stm32f103c6_exti.h
 *
 *  Created on: Jul 9, 2024
 *      Author: Mazen Talaat
 */

#ifndef STM32F103C6_EXTI_H_
#define STM32F103C6_EXTI_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c6.h"
#include "std_types.h"
#include "stm32f103c6_gpio.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct {
	uint16 EXTI_inputLine;
	GPIO_TypeDef *GPIO_port;
	uint16 pinNumber;
	uint8 IVT_number;
} EXTI_GPIO_Mapping;

typedef struct {
	EXTI_GPIO_Mapping EXTI_pin;
	uint8 triggerCase;
	uint8 IRQ_EN;
	void (*P_IRQ_callBack)(void);
} EXTI_PinConfig;

//*****************************************************************************
// Definitions
//*****************************************************************************
// EXTI_Number_define
#define EXTI0 					0
#define EXTI1 					1
#define EXTI2 					2
#define EXTI3 					3
#define EXTI4 					4
#define EXTI5 					5
#define EXTI6 					6
#define EXTI7 					7
#define EXTI8 					8
#define EXTI9 					9
#define EXTI10 					10
#define EXTI11 					11
#define EXTI12 					12
#define EXTI13					13
#define EXTI14 					14
#define EXTI15 					15

// EXTI_define
// EXTI0
#define EXTI0PA0                        (EXTI_GPIO_Mapping){EXTI0, GPIOA, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PB0                        (EXTI_GPIO_Mapping){EXTI0, GPIOB, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PC0                        (EXTI_GPIO_Mapping){EXTI0, GPIOC, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PD0                        (EXTI_GPIO_Mapping){EXTI0, GPIOD, GPIO_PIN_0, EXTI0_IRQ}

// EXTI1
#define EXTI1PA1                        (EXTI_GPIO_Mapping){EXTI1, GPIOA, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PB1                        (EXTI_GPIO_Mapping){EXTI1, GPIOB, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PC1                        (EXTI_GPIO_Mapping){EXTI1, GPIOC, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PD1                        (EXTI_GPIO_Mapping){EXTI1, GPIOD, GPIO_PIN_1, EXTI1_IRQ}

// EXTI2
#define EXTI2PA2                        (EXTI_GPIO_Mapping){EXTI2, GPIOA, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PB2                        (EXTI_GPIO_Mapping){EXTI2, GPIOB, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PC2                        (EXTI_GPIO_Mapping){EXTI2, GPIOC, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PD2                        (EXTI_GPIO_Mapping){EXTI2, GPIOD, GPIO_PIN_2, EXTI2_IRQ}

// EXTI3
#define EXTI3PA3                        (EXTI_GPIO_Mapping){EXTI3, GPIOA, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PB3                        (EXTI_GPIO_Mapping){EXTI3, GPIOB, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PC3                        (EXTI_GPIO_Mapping){EXTI3, GPIOC, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PD3                        (EXTI_GPIO_Mapping){EXTI3, GPIOD, GPIO_PIN_3, EXTI3_IRQ}

// EXTI4
#define EXTI4PA4                        (EXTI_GPIO_Mapping){EXTI4, GPIOA, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PB4                        (EXTI_GPIO_Mapping){EXTI4, GPIOB, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PC4                        (EXTI_GPIO_Mapping){EXTI4, GPIOC, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PD4                        (EXTI_GPIO_Mapping){EXTI4, GPIOD, GPIO_PIN_4, EXTI4_IRQ}

// EXTI5
#define EXTI5PA5                        (EXTI_GPIO_Mapping){EXTI5, GPIOA, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PB5                        (EXTI_GPIO_Mapping){EXTI5, GPIOB, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PC5                        (EXTI_GPIO_Mapping){EXTI5, GPIOC, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PD5                        (EXTI_GPIO_Mapping){EXTI5, GPIOD, GPIO_PIN_5, EXTI5_IRQ}

// EXTI6
#define EXTI6PA6                        (EXTI_GPIO_Mapping){EXTI6, GPIOA, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PB6                        (EXTI_GPIO_Mapping){EXTI6, GPIOB, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PC6                        (EXTI_GPIO_Mapping){EXTI6, GPIOC, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PD6                        (EXTI_GPIO_Mapping){EXTI6, GPIOD, GPIO_PIN_6, EXTI6_IRQ}

// EXTI7
#define EXTI7PA7                        (EXTI_GPIO_Mapping){EXTI7, GPIOA, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PB7                        (EXTI_GPIO_Mapping){EXTI7, GPIOB, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PC7                        (EXTI_GPIO_Mapping){EXTI7, GPIOC, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PD7                        (EXTI_GPIO_Mapping){EXTI7, GPIOD, GPIO_PIN_7, EXTI7_IRQ}

// EXTI8
#define EXTI8PA8                        (EXTI_GPIO_Mapping){EXTI8, GPIOA, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PB8                        (EXTI_GPIO_Mapping){EXTI8, GPIOB, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PC8                        (EXTI_GPIO_Mapping){EXTI8, GPIOC, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PD8                        (EXTI_GPIO_Mapping){EXTI8, GPIOD, GPIO_PIN_8, EXTI8_IRQ}

// EXTI9
#define EXTI9PA9                        (EXTI_GPIO_Mapping){EXTI9, GPIOA, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PB9                        (EXTI_GPIO_Mapping){EXTI9, GPIOB, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PC9                        (EXTI_GPIO_Mapping){EXTI9, GPIOC, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PD9                        (EXTI_GPIO_Mapping){EXTI9, GPIOD, GPIO_PIN_9, EXTI9_IRQ}

// EXTI10
#define EXTI10PA10                      (EXTI_GPIO_Mapping){EXTI10, GPIOA, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PB10                      (EXTI_GPIO_Mapping){EXTI10, GPIOB, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PC10                      (EXTI_GPIO_Mapping){EXTI10, GPIOC, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PD10                      (EXTI_GPIO_Mapping){EXTI10, GPIOD, GPIO_PIN_10, EXTI10_IRQ}

// EXTI11
#define EXTI11PA11                      (EXTI_GPIO_Mapping){EXTI11, GPIOA, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PB11                      (EXTI_GPIO_Mapping){EXTI11, GPIOB, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PC11                      (EXTI_GPIO_Mapping){EXTI11, GPIOC, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PD11                      (EXTI_GPIO_Mapping){EXTI11, GPIOD, GPIO_PIN_11, EXTI11_IRQ}

// EXTI12
#define EXTI12PA12                      (EXTI_GPIO_Mapping){EXTI12, GPIOA, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PB12                      (EXTI_GPIO_Mapping){EXTI12, GPIOB, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PC12                      (EXTI_GPIO_Mapping){EXTI12, GPIOC, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PD12                      (EXTI_GPIO_Mapping){EXTI12, GPIOD, GPIO_PIN_12, EXTI12_IRQ}

// EXTI13
#define EXTI13PA13                      (EXTI_GPIO_Mapping){EXTI13, GPIOA, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PB13                      (EXTI_GPIO_Mapping){EXTI13, GPIOB, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PC13                      (EXTI_GPIO_Mapping){EXTI13, GPIOC, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PD13                      (EXTI_GPIO_Mapping){EXTI13, GPIOD, GPIO_PIN_13, EXTI13_IRQ}

// EXTI14
#define EXTI14PA14                      (EXTI_GPIO_Mapping){EXTI14, GPIOA, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PB14                      (EXTI_GPIO_Mapping){EXTI14, GPIOB, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PC14                      (EXTI_GPIO_Mapping){EXTI14, GPIOC, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PD14                      (EXTI_GPIO_Mapping){EXTI14, GPIOD, GPIO_PIN_14, EXTI14_IRQ}

// EXTI15
#define EXTI15PA15                      (EXTI_GPIO_Mapping){EXTI15, GPIOA, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PB15                      (EXTI_GPIO_Mapping){EXTI15, GPIOB, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PC15                      (EXTI_GPIO_Mapping){EXTI15, GPIOC, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PD15                      (EXTI_GPIO_Mapping){EXTI15, GPIOD, GPIO_PIN_15, EXTI15_IRQ}

// EXTI_Trigger_define
#define EXTI_TRIGGER_RISING								0
#define EXTI_TRIGGER_FALLING							1
#define EXTI_TRIGGER_BOTH_EDGES							2

// EXTI_IRQ_define
#define EXTI_IRQ_ENABLE 								1
#define EXTI_IRQ_DISABLE 								0


//*****************************************************************************
// Generic macros
//*****************************************************************************
#define AFIO_EXTI_MAPPING(port)			((port==GPIOA)?0:\
										 (port==GPIOB)?1:\
										 (port==GPIOC)?2:\
										 (port==GPIOD)?3:0)

//*****************************************************************************
// Functions Prototypes
//*****************************************************************************
void MCAL_EXTI_init(EXTI_PinConfig *EXTI_config);
void MCAL_EXTI_deInit(void);

#endif /* STM32F103C6_EXTI_H_ */
