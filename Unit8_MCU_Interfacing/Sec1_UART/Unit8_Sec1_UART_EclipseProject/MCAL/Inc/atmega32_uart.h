//*****************************************************************************
//
// Module: UART
//
// File Name: atmega32_uart.h
//
// Description: Header file for the UART driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

#ifndef INC_ATMEGA32_UART_H_
#define INC_ATMEGA32_UART_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32.h"
#include "std_types.h"
#include "common_macros.h"

//*****************************************************************************
// UART APIs Prototypes
//*****************************************************************************
void UART_init(uint32 baud_rate);
void UART_sendByte(const uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str); // Receive until #

#endif // INC_ATMEGA32_UART_H_
