//*****************************************************************************
//
// Module: SPI
//
// File Name: stm32f103c6_spi.c
//
// Description: Source file for the SPI driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c6_spi.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
SPI_Config *SPI_gp_configs[SPI_SUPPORTED] = { NULL_PTR, NULL_PTR };

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the SPI device
// @param[in]  SPIx  		The SPI to be configured.
// @param[in]  SPI_config  The needed configuration.
void MCAL_SPI_init(SPI_TypeDef *SPIx, SPI_Config *SPI_config) {
	uint16 CR1_temp = (uint16) 0;
	uint16 CR2_temp = (uint16) 0;

	// Enable clock for the corresponding SPI
	if (SPIx == SPI1) {
		RCC_SPI1_CLK_EN();
		SPI_gp_configs[SPI_1_INDEX] = SPI_config;
	} else if (SPIx == SPI2) {
		RCC_SPI2_CLK_EN();
		SPI_gp_configs[SPI_2_INDEX] = SPI_config;
	}

	// Bit 15 BIDIMODE: Bidirectional data mode enable
	// Bit 14 BIDIOE: Output enable in bidirectional mode
	// Bit 10 RXONLY: Receive only
	CR1_temp |= SPI_config->commMode;
	// Bit 11 DFF: Data frame format
	CR1_temp |= SPI_config->dataSize;

	if (SPI_config->NSS == SPI_NSS_HW_MASTER_OUTPUT_SET) {
		// Bit 2 SSOE: SS output enable
		CR2_temp |= SPI_config->NSS;
	} else if (SPI_config->NSS == SPI_NSS_HW_MASTER_OUTPUT_CLEAR) {
		// Bit 2 SSOE: SS output enable
		CR2_temp &= SPI_config->NSS;
	} else {
		// Bit 9 SSM: Software slave management
		// Bit 8 SSI: Internal slave select
		CR1_temp |= SPI_config->NSS;
	}

	// Bit 7 LSBFIRST: Frame format
	CR1_temp |= SPI_config->frameFormat;
	// Bit 6 SPE: SPI enable
	CR1_temp |= (1 << 6);
	// Bits 5:3 BR[2:0]: Baud rate control
	CR1_temp |= SPI_config->baudRatePrescaler;
	// Bit 2 MSTR: Master selection
	CR1_temp |= SPI_config->deviceMode;
	// Bit1 CPOL: Clock polarity
	CR1_temp |= SPI_config->clockPolarity;
	// Bit 0 CPHA: Clock phase
	CR1_temp |= SPI_config->clockPhase;

	// Bit 7 TXEIE: Tx buffer empty interrupt enable
	// Bit 6 RXNEIE: RX buffer not empty interrupt enable
	// Bit 5 ERRIE: Error interrupt enable
	CR2_temp |= SPI_config->IRQ_enable;

	if (SPI_config->IRQ_enable) {
		// Enable NVIC For SPIx IRQ
		if (SPIx == SPI1) {
			NVIC_IRQ35_SPI1_ENABLE;
		} else if (SPIx == SPI2) {
			NVIC_IRQ36_SPI2_ENABLE;
		}
	}

	SPIx->CR1 = CR1_temp;
	SPIx->CR2 = CR2_temp;
}

// @brief Reset the SPI.
// @param[in]  SPIx  		The SPI to get reset.
void MCAL_SPI_deInit(SPI_TypeDef *SPIx) {
	if (SPIx == SPI1) {
		RCC_SPI1_RESET();
		NVIC_IRQ35_SPI1_DISABLE;
	} else if (SPIx == SPI2) {
		RCC_SPI2_RESET();
		NVIC_IRQ36_SPI2_DISABLE;
	}
}

void MCAL_SPI_GPIO_setPins(SPI_TypeDef *SPIx) {
	GPIO_PinConfig pinConfig;
	SPI_Config *SPI_config = SPI_gp_configs[SPI_INDEX_MAPPING(SPIx)];

	RCC_AFIO_CLK_EN();

	if (SPIx == SPI1) {
		//SPI1
		//PA4 : NSS
		//PA5 : SCK
		//PA6 : MISO
		//PA7 : MOSI
		RCC_GPIOA_CLK_EN();
		if (SPI_config->deviceMode == SPI_DEVICE_MODE_MASTER) {
			//PA4 : NSS
			switch (SPI_config->NSS) {
			case SPI_NSS_HW_MASTER_OUTPUT_CLEAR :
				pinConfig.GPIO_pinNumber = GPIO_PIN_4;
				pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
				MCAL_GPIO_init(GPIOA, &pinConfig);
				break;
			case SPI_NSS_HW_MASTER_OUTPUT_SET :
				pinConfig.GPIO_pinNumber = GPIO_PIN_4;
				pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
				pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
				MCAL_GPIO_init(GPIOA, &pinConfig);
				break;
			}

			//PA5 : SCK
			pinConfig.GPIO_pinNumber = GPIO_PIN_5;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOA, &pinConfig);

			//PA6 : MISO
			pinConfig.GPIO_pinNumber = GPIO_PIN_6;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOA, &pinConfig);

			//PA7 : MOSI
			pinConfig.GPIO_pinNumber = GPIO_PIN_7;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOA, &pinConfig);
		} else {
			//PA4 : NSS
			if (SPI_config->NSS == SPI_NSS_HW_SLAVE) {
				pinConfig.GPIO_pinNumber = GPIO_PIN_4;
				pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
				MCAL_GPIO_init(GPIOA, &pinConfig);
			}

			//PA5 : SCK
			pinConfig.GPIO_pinNumber = GPIO_PIN_5;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOA, &pinConfig);

			//PA6 : MISO
			pinConfig.GPIO_pinNumber = GPIO_PIN_6;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOA, &pinConfig);

			//PA7 : MOSI
			pinConfig.GPIO_pinNumber = GPIO_PIN_7;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOA, &pinConfig);
		}

	} else if (SPIx == SPI2) {
		//SPI2
		//PB12 : NSS
		//PB13 : SCK
		//PB14 : MISO
		//PB15 : MOSI
		RCC_GPIOB_CLK_EN();
		if (SPI_config->deviceMode == SPI_DEVICE_MODE_MASTER) {
			//PB12 : NSS
			switch (SPI_config->NSS) {
			case SPI_NSS_HW_MASTER_OUTPUT_CLEAR :
				pinConfig.GPIO_pinNumber = GPIO_PIN_12;
				pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
				MCAL_GPIO_init(GPIOB, &pinConfig);
				break;
			case SPI_NSS_HW_MASTER_OUTPUT_SET :
				pinConfig.GPIO_pinNumber = GPIO_PIN_12;
				pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
				pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
				MCAL_GPIO_init(GPIOB, &pinConfig);
				break;
			}

			//PB13 : SCK
			pinConfig.GPIO_pinNumber = GPIO_PIN_13;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOB, &pinConfig);

			//PB14 : MISO
			pinConfig.GPIO_pinNumber = GPIO_PIN_14;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOB, &pinConfig);

			//PB15 : MOSI
			pinConfig.GPIO_pinNumber = GPIO_PIN_15;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOB, &pinConfig);

		} else {
			//PB12 : NSS
			if (SPI_config->NSS == SPI_NSS_HW_SLAVE) {
				pinConfig.GPIO_pinNumber = GPIO_PIN_12;
				pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
				MCAL_GPIO_init(GPIOB, &pinConfig);
			}

			//PB13 : SCK
			pinConfig.GPIO_pinNumber = GPIO_PIN_13;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOB, &pinConfig);

			//PB14 : MISO
			pinConfig.GPIO_pinNumber = GPIO_PIN_14;
			pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_PUSH_PULL;
			pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_init(GPIOB, &pinConfig);

			//PB15 : MOSI
			pinConfig.GPIO_pinNumber = GPIO_PIN_15;
			pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
			MCAL_GPIO_init(GPIOB, &pinConfig);
		}
	}
}

// @brief Responsible for send byte to another SPI device.
// @param[in]  SPIx     The corresponding SPI.
// @param[in]  pTxBuffer  The data to be sent.
// @param[in]  pollingEn  Whether to send by polling or not.
void MCAL_SPI_sendData(SPI_TypeDef *SPIx, uint16 *ptrTxBuffer, uint8 pollingEn) {
	// Wait until TXE flag is set in the SR
	if (pollingEn) {
		while (!(SPIx->SR & (1 << 1)))
			;
	}
	SPIx->DR = *ptrTxBuffer;
}

// @brief Responsible for receive byte from another SPI device.
// @param[in]  SPIx  	  The corresponding SPI.
// @param[out] pRxBuffer  The data to be received.
// @param[in]  pollingEn  Whether to receive by polling or not.
void MCAL_SPI_recieveData(SPI_TypeDef *SPIx, uint16 *ptrRxBuffer,
		uint8 pollingEn) {
	// Wait until RXNE flag is set in the SR
	if (pollingEn) {
		while (!(SPIx->SR & (1 << 0)))
			;
	}
	*ptrRxBuffer = SPIx->DR;
}

// @brief Responsible for send and receive byte to another SPI device.
// @param[in]  SPIx       The corresponding SPI.
// @param[in]  ptrBuffer  The data to be sent and received.
// @param[in]  pollingEn  Whether to send by polling or not.
void MCAL_SPI_sendRecieve(SPI_TypeDef *SPIx, uint16 *ptrBuffer, uint8 pollingEn) {
	// Wait until TXE flag is set in the SR
	if (pollingEn) {
		while (!(SPIx->SR & (1 << 1)))
			;
	}
	SPIx->DR = *ptrBuffer;

	// Wait until RXNE flag is set in the SR
	if (pollingEn) {
		while (!(SPIx->SR & (1 << 0)))
			;
	}
	*ptrBuffer = SPIx->DR;
}

//*****************************************************************************
// IRQHandler Definitions
//*****************************************************************************
void SPI1_IRQHandler(void) {
	SPI_gp_configs[SPI_1_INDEX]->P_IRQ_callBack();
}

void SPI2_IRQHandler(void) {
	SPI_gp_configs[SPI_2_INDEX]->P_IRQ_callBack();
}
