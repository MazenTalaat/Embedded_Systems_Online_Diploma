//*****************************************************************************
//
// Module: EEPROM
//
// File Name: eeprom_i2c.c
//
// Description: Source file for the EEPROM I2C driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
//*******************************************************************************
// Includes
//*******************************************************************************
#include "eeprom_i2c.h"

// @brief Initialize the EEPROM
void EEPROM_init(void) {
	I2C_Config I2C1_config;

	I2C1_config.deviceMode = I2C_DEVICE_MODE_MASTER;
	I2C1_config.mode = I2C_MODE_I2C;
	I2C1_config.generalCallAddressDetection = I2C_GCAD_ENABLE;
	I2C1_config.ACK_control = I2C_ACK_CONTROL_ENABLE;
	I2C1_config.clkSpeed = I2C_CLK_SPEED_SM_100KHZ;
	I2C1_config.IRQ_enable = I2C_IRQ_NONE;
	I2C1_config.stretchMode = I2C_STRETCH_MODE_ENABLE;

	MCAL_I2C_GPIO_setPins(I2C1);
	MCAL_I2C_init(I2C1, &I2C1_config);
}

// @brief Write bytes to EEPROM
// @param[in]  memoryAddress  	The memory address.
// @param[in]  dataTx  			The data to be sent.
// @param[in]  dataLength  		The data length.
void EEPROM_writeBytes(uint32 memoryAddress, uint8 *dataTx, uint8 dataLength) {
	uint8 buffer[256], i = 0;
	buffer[0] = (uint8) (memoryAddress >> 8);
	buffer[1] = (uint8) memoryAddress;

	for (i = 2; i < dataLength + 2; i++) {
		buffer[i] = dataTx[i - 2];
	}

	MCAL_I2C_masterTx(I2C1, EEPROM_SLAVE_ADDRESS, buffer, dataLength + 2,
	I2C_STOP_WITH, I2C_START_NORMAL);
}

// @brief Read bytes from EEPROM
// @param[in]  memoryAddress  	The memory address.
// @param[in]  dataRx  			The data to be received.
// @param[in]  dataLength  		The data length.
void EEPROM_readBytes(uint32 memoryAddress, uint8 *dataRx, uint8 dataLength) {
	uint8 buffer[2];
	buffer[0] = (uint8) (memoryAddress >> 8);
	buffer[1] = (uint8) memoryAddress;

	MCAL_I2C_masterTx(I2C1, EEPROM_SLAVE_ADDRESS, buffer, 2, I2C_STOP_WITHOUT,
			I2C_START_NORMAL);
	MCAL_I2C_masterRx(I2C1, EEPROM_SLAVE_ADDRESS, dataRx, dataLength,
	I2C_STOP_WITH, I2C_START_REPEATED);
}
