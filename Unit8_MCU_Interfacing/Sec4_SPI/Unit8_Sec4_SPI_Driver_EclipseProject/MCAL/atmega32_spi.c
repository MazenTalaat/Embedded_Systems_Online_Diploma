//*****************************************************************************
//
// Module: SPI
//
// File Name: atmega32_spi.c
//
// Description: Source file for the SPI driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32_spi.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
void (*SPI_gp_IRQ_callBack)(void);

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the SPI device
// @param[in]  SPI_config  The needed configuration.
void MCAL_SPI_init(SPI_Config *SPI_config) {
	uint8 SPCR_temp = (uint8) 0;

	MCAL_SPI_GPIO_setPins(SPI_config);

	if (SPI_config->deviceMode == SPI_DEVICE_MODE_MASTER) {
		switch (SPI_config->baudRatePrescaler) {
		case SPI_BAUDRATE_PRESCALER_2 :
			SPSR |= (1 << SPI2X);
			break;
		case SPI_BAUDRATE_PRESCALER_8 :
			SPSR |= (1 << SPI2X);
			SPCR_temp |= (1 << SPR0);
			break;
		case SPI_BAUDRATE_PRESCALER_32 :
			SPSR |= (1 << SPI2X);
			SPCR_temp |= (1 << SPR1);
			break;
		default:
			SPCR_temp |= SPI_config->baudRatePrescaler;
		}
	}

	SPCR_temp |= SPI_config->deviceMode;

	SPCR_temp |= SPI_config->clockPhase;

	SPCR_temp |= SPI_config->clockPolarity;

	SPCR_temp |= SPI_config->frameFormat;

	SPCR_temp |= SPI_config->IRQ_enable;
	if (SPI_config->IRQ_enable) {
		SPI_gp_IRQ_callBack = SPI_config->P_IRQ_callBack;
	}

	SPCR_temp |= (1 << SPE);

	SPCR = SPCR_temp;
}

// @brief Reset the SPI.
void MCAL_SPI_deInit(void) {
	SPSR = (uint8) 0;
	SPCR = (uint8) 0;
}

void MCAL_SPI_GPIO_setPins(SPI_Config *SPI_config) {
	GPIO_PinConfig pinConfig;

	if (SPI_config->deviceMode == SPI_DEVICE_MODE_MASTER) {
		// SS(PB4)   -> Output
		pinConfig.GPIO_pinNumber = GPIO_PIN_4;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT;
		MCAL_GPIO_init(GPIOB, &pinConfig);
		// MOSI(PB5) -> Output
		pinConfig.GPIO_pinNumber = GPIO_PIN_5;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT;
		MCAL_GPIO_init(GPIOB, &pinConfig);
		// MISO(PB6) -> Input
		pinConfig.GPIO_pinNumber = GPIO_PIN_6;
		pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
		MCAL_GPIO_init(GPIOB, &pinConfig);
		// SCK(PB7)  -> Output
		pinConfig.GPIO_pinNumber = GPIO_PIN_7;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT;
		MCAL_GPIO_init(GPIOB, &pinConfig);
	} else {
		// SS(PB4)   -> Input
		pinConfig.GPIO_pinNumber = GPIO_PIN_4;
		pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
		MCAL_GPIO_init(GPIOB, &pinConfig);
		// MOSI(PB5) -> Input
		pinConfig.GPIO_pinNumber = GPIO_PIN_5;
		pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
		MCAL_GPIO_init(GPIOB, &pinConfig);
		// MISO(PB6) -> Output
		pinConfig.GPIO_pinNumber = GPIO_PIN_6;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT;
		MCAL_GPIO_init(GPIOB, &pinConfig);
		// SCK(PB7)  -> Input
		pinConfig.GPIO_pinNumber = GPIO_PIN_7;
		pinConfig.GPIO_pinMode = GPIO_MODE_IN_FLOATING;
		MCAL_GPIO_init(GPIOB, &pinConfig);
	}
}

// @brief Responsible for send byte to another SPI device.
// @param[in]  pTxBuffer  The data to be sent.
// @param[in]  pollingEn  Whether to send by polling or not.
void MCAL_SPI_sendData(uint8 *ptrTxBuffer, uint8 pollingEn){
	uint8 dummyData = 0xFF;
	SPDR = *ptrTxBuffer;
	// Wait until SPIF flag is set in the SR
	if (pollingEn) {
		while (BIT_IS_CLEAR(SPSR, SPIF))
			;
	}
	dummyData = SPDR;
}

// @brief Responsible for receive byte from another SPI device.
// @param[out] pRxBuffer  The data to be received.
// @param[in]  pollingEn  Whether to receive by polling or not.
void MCAL_SPI_recieveData(uint8 *ptrRxBuffer, uint8 pollingEn){
	uint8 dummyData = 0xFF;
	SPDR = dummyData;
	// Wait until SPIF flag is set in the SR
	if (pollingEn) {
		while (BIT_IS_CLEAR(SPSR, SPIF))
			;
	}
	*ptrRxBuffer = SPDR;
}

// @brief Responsible for send and receive byte to another SPI device.
// @param[in]  ptrBuffer  The data to be sent and received.
// @param[in]  pollingEn  Whether to send by polling or not.
uint8 MCAL_SPI_sendRecieve(uint8 buffer, uint8 pollingEn) {
	SPDR = buffer;
	// Wait until SPIF flag is set in the SR
	if (pollingEn) {
		while (BIT_IS_CLEAR(SPSR, SPIF))
			;
	}
	return SPDR;
}

//*****************************************************************************
// ISR Functions Definitions
//*****************************************************************************
ISR(SPI_STC_vect) {
	SPI_gp_IRQ_callBack();
}

