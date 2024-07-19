//*****************************************************************************
//
// Module: SPI
//
// File Name: stm32f103c6_spi.h
//
// Description: Header file for the SPI driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef STM32F103C6_SPI_H_
#define STM32F103C6_SPI_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c6.h"
#include "stm32f103c6_gpio.h"
#include "stm32f103c6_rcc.h"
#include "std_types.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct {
	uint16 deviceMode; 		// Specifies device operation mode (Master/Slave).
	uint16 commMode;		// Specifies the SPI communication mode (direction).
	uint16 frameFormat;  		// Specifies start sending the LSB or MSB.
	uint16 dataSize;			// Specifies pay-load number of bits.
	uint16 clockPolarity;		// Specifies the polarity of clock.
	uint16 clockPhase;			// Specifies the phase of clock.
	uint16 NSS;					// Specifies NSS Mode (HW/SW).
	uint16 baudRatePrescaler;	// Specifies The value of Baud Rate Prescaler.
	uint16 IRQ_enable;			// Enable or disable SPI interrupts.
	void (*P_IRQ_callBack)(void); // Interrupt callback function.
} SPI_Config;

//*****************************************************************************
// Definitions
//*****************************************************************************
#define SPI_SUPPORTED						2 // SPI1, SPI2
#define SPI_1_INDEX							0
#define SPI_2_INDEX							1

//SPI_deviceMode_define
#define SPI_DEVICE_MODE_SLAVE				(uint16)(0)
#define SPI_DEVICE_MODE_MASTER				(uint16)(1<<2)

//SPI_commMode_define
// Note other modes are not supported
#define SPI_COMM_MODE_2LINES				(uint16)(0)
//#define SPI_COMM_MODE_2LINES_RX_ONLY		(uint16)(1<<10)
//#define SPI_COMM_MODE_1LINE_RX_ONLY		(uint16)(1<<15)
//#define SPI_COMM_MODE_1LINE_TX_ONLY		(uint16)((1<<15) | (1<<14))

//SPI_frameFormat_define
#define SPI_FRAME_FORMAT_MSB				(uint16)(0)
#define SPI_FRAME_FORMAT_LSB				(uint16)(1<<7)

//SPI_dataSize_define
#define SPI_DATA_SIZE_8BITS					(uint16)(0)
#define SPI_DATA_SIZE_16BITS				(uint16)(1<<11)

//SPI_clockPolarity_define
#define SPI_CLK_POLARITY_LOW_IDLE			(uint16)(0)
#define SPI_CLK_POLARITY_HIGH_IDLE			(uint16)(1<<1)

//SPI_clockPhase_define
#define SPI_CLK_PHASE_EDGE1					(uint16)(0)
#define SPI_CLK_PHASE_EDGE2					(uint16)(1<<0)

//SPI_NSS_define
#define SPI_NSS_SW_INTERNAL_SS_SET			(uint16)((1 << 9) | (1 << 8))
#define SPI_NSS_SW_INTERNAL_SS_CLEAR		(uint16)(1 << 9)

#define SPI_NSS_HW_SLAVE					(uint16)(0)
#define SPI_NSS_HW_MASTER_OUTPUT_SET		(uint16)(1<<2)
#define SPI_NSS_HW_MASTER_OUTPUT_CLEAR		(uint16)(~(1<<2))

//SPI_baudRatePrescaler_define
#define SPI_BAUDRATE_PRESCALER_2			(uint16)(0b000<<3)
#define SPI_BAUDRATE_PRESCALER_4			(uint16)(0b001<<3)
#define SPI_BAUDRATE_PRESCALER_8			(uint16)(0b010<<3)
#define SPI_BAUDRATE_PRESCALER_16			(uint16)(0b011<<3)
#define SPI_BAUDRATE_PRESCALER_32			(uint16)(0b100<<3)
#define SPI_BAUDRATE_PRESCALER_64			(uint16)(0b101<<3)
#define SPI_BAUDRATE_PRESCALER_128			(uint16)(0b110<<3)
#define SPI_BAUDRATE_PRESCALER_256			(uint16)(0b111<<3)

//SPI_IRQ_Enable_define
#define SPI_IRQ_ENABLE_NONE					(uint16)(0)
#define SPI_IRQ_ENABLE_TXEIE				(uint16)(1<<7)
#define SPI_IRQ_ENABLE_RXNEIE				(uint16)(1<<6)
#define SPI_IRQ_ENABLE_ERRIE				(uint16)(1<<5)

// SPI Polling
#define SPI_POLLING_ENABLED                 TRUE
#define SPI_POLLING_DISABLED                FALSE

//*******************************************************************************
// Generic Macros
//*******************************************************************************
#define SPI_INDEX_MAPPING(spi)				(((spi)==SPI1)?SPI_1_INDEX:\
										 	 ((spi)==SPI2)?SPI_2_INDEX:0)
//*****************************************************************************
// SPI APIs Prototypes
//*****************************************************************************
void MCAL_SPI_init(SPI_TypeDef *SPIx, SPI_Config *SPI_config);
void MCAL_SPI_deInit(SPI_TypeDef *SPIx);

void MCAL_SPI_GPIO_setPins(SPI_TypeDef *SPIx);

void MCAL_SPI_sendData(SPI_TypeDef *SPIx, uint16 *ptrTxBuffer, uint8 pollingEn);
void MCAL_SPI_recieveData(SPI_TypeDef *SPIx, uint16 *ptrRxBuffer,
		uint8 pollingEn);
void MCAL_SPI_sendRecieve(SPI_TypeDef *SPIx, uint16 *ptrBuffer, uint8 pollingEn);

#endif // STM32F103C6_SPI_H_
