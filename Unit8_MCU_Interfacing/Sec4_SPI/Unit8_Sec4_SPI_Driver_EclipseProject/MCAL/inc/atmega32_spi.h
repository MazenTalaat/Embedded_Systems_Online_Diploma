//*****************************************************************************
//
// Module: SPI
//
// File Name: atmega32_spi.h
//
// Description: Header file for the SPI driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef ATMEGA32_SPI_H_
#define ATMEGA32_SPI_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32.h"
#include "std_types.h"
#include "common_macros.h"
#include "avr/interrupt.h"
#include "atmega32_gpio.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct {
	uint8 deviceMode; 		// Specifies device operation mode (Master/Slave).
	uint8 frameFormat;  		// Specifies start sending the LSB or MSB.
	uint8 clockPolarity;		// Specifies the polarity of clock.
	uint8 clockPhase;			// Specifies the phase of clock.
	uint8 baudRatePrescaler;	// Specifies The value of Baud Rate Prescaler.
	uint8 IRQ_enable;			// Enable or disable SPI interrupts.
	void (*P_IRQ_callBack)(void); // Interrupt callback function.
} SPI_Config;

//*****************************************************************************
// Definitions
//*****************************************************************************
//SPI_deviceMode_define
#define SPI_DEVICE_MODE_SLAVE				(uint8)(0)
#define SPI_DEVICE_MODE_MASTER				(uint8)(1<<MSTR)

//SPI_frameFormat_define
#define SPI_FRAME_FORMAT_MSB				(uint8)(0)
#define SPI_FRAME_FORMAT_LSB				(uint8)(1<<DORD)

//SPI_clockPolarity_define
#define SPI_CLK_POLARITY_LOW_IDLE			(uint8)(0)
#define SPI_CLK_POLARITY_HIGH_IDLE			(uint8)(1<<CPOL)

//SPI_clockPhase_define
#define SPI_CLK_PHASE_EDGE1					(uint8)(0)
#define SPI_CLK_PHASE_EDGE2					(uint8)(1<<CPHA)

//SPI_baudRatePrescaler_define
#define SPI_BAUDRATE_PRESCALER_2			(uint8)(4) //SPI2X
#define SPI_BAUDRATE_PRESCALER_4			(uint8)(0)
#define SPI_BAUDRATE_PRESCALER_8			(uint8)(5) //SPI2X
#define SPI_BAUDRATE_PRESCALER_16			(uint8)(1<<SPR0)
#define SPI_BAUDRATE_PRESCALER_32			(uint8)(6) //SPI2X
#define SPI_BAUDRATE_PRESCALER_64			(uint8)(1<<SPR1)
#define SPI_BAUDRATE_PRESCALER_128			(uint8)((1<<SPR1)|(1<<SPR0))

//SPI_IRQ_Enable_define
#define SPI_IRQ_ENABLE_NONE					(uint8)(0)
#define SPI_IRQ_ENABLE_STC					(uint8)(1)

// SPI Polling
#define SPI_POLLING_ENABLED                 TRUE
#define SPI_POLLING_DISABLED                FALSE

//*****************************************************************************
// SPI APIs Prototypes
//*****************************************************************************
void MCAL_SPI_init(SPI_Config *SPI_config);
void MCAL_SPI_deInit(void);

void MCAL_SPI_GPIO_setPins(SPI_Config *SPI_config);

void MCAL_SPI_sendData(uint8 *ptrTxBuffer, uint8 pollingEn);
void MCAL_SPI_recieveData(uint8 *ptrRxBuffer, uint8 pollingEn);
uint8 MCAL_SPI_sendRecieve(uint8 buffer, uint8 pollingEn);

#endif // ATMEGA32_SPI_H_
