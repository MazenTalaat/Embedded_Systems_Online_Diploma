//*****************************************************************************
//
// Module: USART
//
// File Name: stm32f103c6_usart.c
//
// Description: Source file for the USART driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c6_usart.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
UART_Config *UART_gp_configs[UART_SUPPORTED] = { NULL_PTR, NULL_PTR, NULL_PTR };

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the UART device
// @param[in]  USARTx  		The UART to be configured.
// @param[in]  UART_config  The needed configuration.
void MCAL_UART_init(USART_TypeDef *USARTx, UART_Config *UART_config) {
	// Enable clock for the corresponding USART
	if (USARTx == USART1) {
		RCC_USART1_CLK_EN();
		UART_gp_configs[UART_1_INDEX] = UART_config;
	} else if (USARTx == USART2) {
		RCC_USART2_CLK_EN();
		UART_gp_configs[UART_2_INDEX] = UART_config;
	} else if (USARTx == USART3) {
		RCC_USART3_CLK_EN();
		UART_gp_configs[UART_3_INDEX] = UART_config;
	}

	// Enable the USART by writing the UE bit in USART_CR1 register to 1.
	// Bit 13 UE: USART enable
	USARTx->CR1 |= (1 << 13);

	// Program the M bit in USART_CR1 to define the word length.
	// Bit 12 M: Word length
	USARTx->CR1 |= UART_config->payloadLength;

	// Bit 10 PCE: Parity control enable
	// Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_config->parity;

	// Bit 8 PEIE: PE interrupt enable
	// Bit 7 TXEIE: TXE interrupt enable
	// Bit 6 TCIE: Transmission complete interrupt enable
	// Bit 5 RXNEIE: RXNE interrupt enable
	USARTx->CR1 |= UART_config->IRQ_enable;

	// Bit 3 TE: Transmitter enable
	// Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_config->mode;

	// Program the number of stop bits in USART_CR2.
	// Bits 13:12 STOP: STOP bits
	USARTx->CR2 |= UART_config->stopBits;

	// Bit 9 CTSE: CTS enable
	// Bit 8 RTSE: RTS enable
	USARTx->CR3 |= UART_config->hwFlowCtl;

	// Select the desired baud rate using the USART_BRR register.
	if (USARTx == USART1) {
		USARTx->BRR = UART_BRR_REG(MCAL_RCC_getPCLK1Freq(),
				UART_config->baudRate);
	}
	else {
		USARTx->BRR = UART_BRR_REG(MCAL_RCC_getPCLK2Freq(),
				UART_config->baudRate);
	}

	if (UART_config->IRQ_enable) {
		// Enable NVIC For USARTx IRQ
		if (USARTx == USART1) {
			NVIC_IRQ37_USART1_ENABLE;
		} else if (USARTx == USART2) {
			NVIC_IRQ38_USART2_ENABLE;
		} else if (USARTx == USART3) {
			NVIC_IRQ39_USART3_ENABLE;
		}
	}
}

// @brief Reset the UART.
// @param[in]  USARTx  		The UART to get reset.
void MCAL_UART_deInit(USART_TypeDef *USARTx) {
	if (USARTx == USART1) {
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_DISABLE;
	}
	else if (USARTx == USART2) {
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_DISABLE;
	}
	else if (USARTx == USART3) {
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_DISABLE;
	}
}

// @brief Configure GPIO pins for the corresponding UART.
// @param[in]  USARTx  		The corresponding UART.
void MCAL_UART_GPIO_setPins(USART_TypeDef *USARTx) {
	GPIO_PinConfig pinConfig;
	UART_Config *UART_config = UART_gp_configs[UART_INDEX_MAPPING(USARTx)];

	RCC_AFIO_CLK_EN();

	if (USARTx == USART1) {
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS
		RCC_GPIOA_CLK_EN();

		//PA9 TX
		pinConfig.GPIO_pinNumber = GPIO_PIN_9;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
		pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
		MCAL_GPIO_init(GPIOA, &pinConfig);

		//PA10 RX
		pinConfig.GPIO_pinNumber = GPIO_PIN_10;
		pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
		MCAL_GPIO_init(GPIOA, &pinConfig);

		if (UART_config->hwFlowCtl == UART_HWFLOWCTL_CTS
				|| UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS_CTS) {
			//PA11 CTS
			pinConfig.GPIO_pinNumber = GPIO_PIN_11;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOA, &pinConfig);
		}

		if (UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS
				|| UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS_CTS) {
			//PA12 RTS
			pinConfig.GPIO_pinNumber = GPIO_PIN_12;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOA, &pinConfig);

		}
	} else if (USARTx == USART2) {
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS
		RCC_GPIOA_CLK_EN();

		//PA2 TX
		pinConfig.GPIO_pinNumber = GPIO_PIN_2;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
		pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
		MCAL_GPIO_init(GPIOA, &pinConfig);

		//PA3 RX
		pinConfig.GPIO_pinNumber = GPIO_PIN_3;
		pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
		MCAL_GPIO_init(GPIOA, &pinConfig);

		if (UART_config->hwFlowCtl == UART_HWFLOWCTL_CTS
				|| UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS_CTS) {
			//PA0 CTS
			pinConfig.GPIO_pinNumber = GPIO_PIN_0;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOA, &pinConfig);
		}

		if (UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS
				|| UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS_CTS) {
			//PA1 RTS
			pinConfig.GPIO_pinNumber = GPIO_PIN_1;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOA, &pinConfig);
		}
	} else if (USARTx == USART3) {
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS
		RCC_GPIOB_CLK_EN();

		//PB10 TX
		pinConfig.GPIO_pinNumber = GPIO_PIN_10;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
		pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
		MCAL_GPIO_init(GPIOB, &pinConfig);

		//PB11 RX
		pinConfig.GPIO_pinNumber = GPIO_PIN_11;
		pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
		MCAL_GPIO_init(GPIOB, &pinConfig);

		if (UART_config->hwFlowCtl == UART_HWFLOWCTL_CTS
				|| UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS_CTS) {
			//PB13 CTS
			pinConfig.GPIO_pinNumber = GPIO_PIN_13;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOB, &pinConfig);
		}

		if (UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS
				|| UART_config->hwFlowCtl == UART_HWFLOWCTL_RTS_CTS) {
			//PA14 RTS
			RCC_GPIOA_CLK_EN();
			pinConfig.GPIO_pinNumber = GPIO_PIN_14;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOB, &pinConfig);
		}
	}
}

// @brief Responsible for send byte to another UART device.
// @param[in]  USARTx  		The corresponding UART.
// @param[in]  pTxBuffer  The data to be sent.
// @param[in]  pollingEn  Whether to send by polling or not.
void MCAL_UART_sendData(USART_TypeDef *USARTx, uint16 *pTxBuffer,
		uint8 pollingEn) {
	UART_Config *UART_config = UART_gp_configs[UART_INDEX_MAPPING(USARTx)];
	// Wait until TXE flag is set in the SR
	if (pollingEn)
		while (!(USARTx->SR & 1 << 7))
			;

	// Check the payloadLength item for 9 bits or 8 bits in a frame
	if (UART_config->payloadLength == UART_PAYLOAD_LENGTH_9BITS) {
		//if 9 bits, load the DR with 2 bytes masking the bits other than first 9 bits
		USARTx->DR = (*pTxBuffer & (uint16) 0x01FF);
	} else {
		//This is 8bit data transfer
		USARTx->DR = (*pTxBuffer & (uint8) 0xFF);
	}
}

// @brief Responsible for receive byte from another UART device.
// @param[in]  USARTx  		The corresponding UART.
// @param[out] pRxBuffer  The data to be received.
// @param[in]  pollingEn  Whether to receive by polling or not.
void MCAL_UART_receiveData(USART_TypeDef *USARTx, uint16 *pRxBuffer,
		uint8 pollingEn) {
	UART_Config *UART_config = UART_gp_configs[UART_INDEX_MAPPING(USARTx)];
	// Wait until RXNE flag is set in the SR
	if (pollingEn) {
		while (!(USARTx->SR & 1 << 5))
			;
	}
	// Check the payloadLength item for 9 bits or 8 bits in a frame
	if (UART_config->payloadLength == UART_PAYLOAD_LENGTH_9BITS) {
		if (UART_config->parity == UART_PARITY_NONE) {
			// No parity, so all 9 bits are considered data
			*((uint16*) pRxBuffer) = USARTx->DR;

		} else {
			// Parity is used, so 8 bits will be of user data and 1 bit is parity
			*((uint16*) pRxBuffer) = (USARTx->DR & (uint8) 0xFF);
		}
	} else {
		//This is 8bit data
		if (UART_config->parity == UART_PARITY_NONE) {
			// No parity, so all 8 bits are considered data
			*((uint16*) pRxBuffer) = (USARTx->DR & (uint8) 0xFF);

		} else {
			// Parity is used, so 7 bits will be of user data and 1 bit is parity
			*((uint16*) pRxBuffer) = (USARTx->DR & (uint8) 0X7F);
		}
	}
}

//*****************************************************************************
// IRQHandler Definitions
//*****************************************************************************
void USART1_IRQHandler(void) {
	UART_gp_configs[UART_1_INDEX]->P_IRQ_callBack();
}

void USART2_IRQHandler(void) {
	UART_gp_configs[UART_2_INDEX]->P_IRQ_callBack();

}
void USART3_IRQHandler(void) {
	UART_gp_configs[UART_3_INDEX]->P_IRQ_callBack();
}
