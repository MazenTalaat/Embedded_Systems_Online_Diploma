//*****************************************************************************
//
// Module: EEPROM
//
// File Name: eeprom_i2c.h
//
// Description: Header file for the EEPROM I2C driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef EEPROM_I2C_H_
#define EEPROM_I2C_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c8_i2c.h"

//*****************************************************************************
// Definitions
//*****************************************************************************
#define EEPROM_SLAVE_ADDRESS			0x2A

//*****************************************************************************
// EEPROM I2C APIs Prototypes
//*****************************************************************************
void EEPROM_init(void);
void EEPROM_writeBytes(uint32 memory_address, uint8 *dataTx, uint8 data_length);
void EEPROM_readBytes(uint32 memory_address, uint8 *dataRx, uint8 data_length);

#endif // EEPROM_I2C_H_
