//*****************************************************************************
//
// Module: USART
//
// File Name: stm32f103c6_usart.h
//
// Description: Header file for the USART driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef STM32F103C6_USART_H_
#define STM32F103C6_USART_H_

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
	uint8 mode;     			// Specifies the TX/RX Mode.
	uint32 baudRate; 		    // Specifies baud rate.
	uint16 payloadLength;		// Specifies pay-load number of bits.
	uint16 parity;				// Specifies the parity mode.
	uint16 stopBits;				// Specifies the number of stop bits.
	uint16 hwFlowCtl;			// Specifies whether the hardware flow control mode is enabled or disabled.
	uint16 IRQ_enable;			// Enable or disable UART interrupts.
	void (*P_IRQ_callBack)(void);	// Interrupt callback function.
} UART_Config;

//*****************************************************************************
// Definitions
//*****************************************************************************
#define UART_SUPPORTED						3 // UART1, UART2, UART3
#define UART_1_INDEX						0
#define UART_2_INDEX						1
#define UART_3_INDEX						2

// UART_Mode_define
#define UART_MODE_RX                        (uint32)(1<<2)
#define UART_MODE_TX                       	(uint32)(1<<3)
#define UART_MODE_TX_RX                     (uint32)(1<<2 | 1<<3)

// UART_BaudRate_define
#define UART_BAUDRATE_2400                  2400
#define UART_BAUDRATE_9600                  9600
#define UART_BAUDRATE_19200                 19200
#define UART_BAUDRATE_57600                 57600
#define UART_BAUDRATE_115200                115200
#define UART_BAUDRATE_230400                230400
#define UART_BAUDRATE_460800                460800
#define UART_BAUDRATE_921600                921600
#define UART_BAUDRATE_2250000               2250000
#define UART_BAUDRATE_4500000               4500000

// UART_Payload_Length_define
#define UART_PAYLOAD_LENGTH_8BITS           (uint32)(0)
#define UART_PAYLOAD_LENGTH_9BITS           (uint32)(1<<12)

// UART_Parity_define
#define UART_PARITY_NONE                    (uint32)(0)
#define UART_PARITY_EVEN                    (uint32)(1<<10)
#define UART_PARITY_ODD                     (uint32)(1<<10 | 1<<9)

// UART_StopBits_define
#define UART_STOPBITS_0_5                 	(uint32)(1<<12)
#define UART_STOPBITS_1                    	(uint32)(0)
#define UART_STOPBITS_1_5               	(uint32)(3<<12)
#define UART_STOPBITS_2                    	(uint32)(2<<12)

// UART_HwFlowCtl_define
#define UART_HWFLOWCTL_NONE                 (uint32)(0)
#define UART_HWFLOWCTL_RTS                  (uint32)(1<<8)
#define UART_HWFLOWCTL_CTS                  (uint32)(1<<9)
#define UART_HWFLOWCTL_RTS_CTS              (uint32)(1<<8 | 1<<9)

// UART_IRQ_Enable_define
#define UART_IRQ_ENABLE_NONE                (uint32)(0)
#define UART_IRQ_ENABLE_PE                  (uint32)(1<<8) //Parity error
#define UART_IRQ_ENABLE_TXE                 (uint32)(1<<7) //Transmit data register empty
#define UART_IRQ_ENABLE_TC                  (uint32)(1<<6) //Transmission complete
#define UART_IRQ_ENABLE_RXNE              	(uint32)(1<<5) //Received data ready to be read & Overrun error detected

// UART Polling
#define UART_POLLING_ENABLED                TRUE
#define UART_POLLING_DISABLED               FALSE

//*******************************************************************************
// Generic Macros
//*******************************************************************************
#define UARTDIV(_PCLK_, _BAUD_)					(uint32) (_PCLK_/(16 * _BAUD_ ))
#define UARTDIV_MUL100(_PCLK_, _BAUD_)			(uint32) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define MANTISSA_MUL100(_PCLK_, _BAUD_)			(uint32) (UARTDIV(_PCLK_, _BAUD_) * 100)
#define MANTISSA(_PCLK_, _BAUD_)				(uint32) (UARTDIV(_PCLK_, _BAUD_))
#define DIV_FRACTION(_PCLK_, _BAUD_)			(uint32) (((UARTDIV_MUL100(_PCLK_, _BAUD_) -  MANTISSA_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_REG(_PCLK_, _BAUD_)			(( MANTISSA (_PCLK_, _BAUD_)) << 4 ) | (( DIV_FRACTION(_PCLK_, _BAUD_)) & 0xF )

#define UART_INDEX_MAPPING(uart)				(((uart)==USART1)?UART_1_INDEX:\
										 	 	 ((uart)==USART2)?UART_2_INDEX:\
										 	 	 ((uart)==USART3)?UART_3_INDEX:0)

//*****************************************************************************
// USART APIs Prototypes
//*****************************************************************************
void MCAL_UART_init(USART_TypeDef *USARTx, UART_Config *UART_config);
void MCAL_UART_deInit(USART_TypeDef *USARTx);

void MCAL_UART_GPIO_setPins(USART_TypeDef *USARTx);

void MCAL_UART_sendData(USART_TypeDef *USARTx, uint16 *pTxBuffer,
		uint8 pollingEn);
void MCAL_UART_receiveData(USART_TypeDef *USARTx, uint16 *pRxBuffer,
		uint8 pollingEn);

#endif // STM32F103C6_USART_H_
