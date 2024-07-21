//*****************************************************************************
//
// Module: I2C
//
// File Name: atmega32_i2c.c
//
// Description: Source file for the I2C driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32_i2c.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
I2C_Config I2C_g_config;

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the I2C device
// @param[in]  I2C_config  	The needed configuration.
void MCAL_I2C_init(I2C_Config *I2C_config) {
	I2C_g_config = *I2C_config;

	// Other frequencies not supported yet
	if (I2C_config->clkSpeed == I2C_CLK_SPEED_400KHZ) {
		// SCL frequency = CPU Clock frequency / 16 + 2(TWBR)*4^TWPS
		// Let TWPS = 0
		// 400000 = 8000000 / (16 + 2 * TWBR * 1)
		// TWBR = 2
		// Bits 7..0 I2C Bit Rate Register
		TWBR = 0x02;

		// Bits 1..0 TWPS: I2C Prescaler Bits
		TWSR = 0x00;
	}
	// TWAR
	// Bits 7..1 TWA: I2C (Slave) Address Register
	if (I2C_config->deviceMode == I2C_DEVICE_MODE_SLAVE) {
		TWAR = (I2C_config->slaveAddress << 1);
	}
	// TWAR
	// Bit 0 TWGCE: I2C General Call Recognition Enable Bit
	if (I2C_config->generalCallAddressDetection) {
		TWAR |= I2C_GCAD_ENABLE;
	}

	if (I2C_config->IRQ_enable) {
		IRQ20_I2C_ENABLE;
	}

	// Bit 2 TWEN: I2C Enable Bit
	if (I2C_g_config.ACK_control == I2C_ACK_CONTROL_ENABLE) {
		TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	} else {
		TWCR |= (1 << TWINT) | (1 << TWEN);
	}
}

// @brief Reset the I2C.
void MCAL_I2C_deInit(void) {
	TWCR = 0;
	TWBR = 0;
	TWSR = 0;
	TWDR = 0xFF;
	TWAR = 0xFF;
	IRQ20_I2C_DISABLE;
}

// Master with polling mechanism
// @brief Master sends data
// @param[in]  slaveAddress 	The slave address.
// @param[in]  dataTx  			The data to be sent.
// @param[in]  stopCondition 	Send with or without a stop bit.
// @param[in]  startCondition 	Send a repeated start or not.
// @return	   Return 0 if error occurred
uint8 MCAL_I2C_masterTx(uint16 slaveAddress, uint8 *dataTx, uint32 dataLength,
		uint8 stopCondition, uint8 startCondition) {
	uint32 i = 0;

	// 1. Application writes to TWCR to initiate transmission of START
	// 2. TWINT set. Status code indicates START condition sent
	I2C_generateStart();

	// 3. Check TWSR to see if START was sent.
	if (startCondition == I2C_START_NORMAL) {
		if (!I2C_getFlagStatus(I2C_FLAG_MT_START))
			return FALSE;
	} else {
		if (!I2C_getFlagStatus(I2C_FLAG_MT_REP_START))
			return FALSE;
	}

	// Application loads SLA+W into TWDR, and loads appropriate control signals into TWCR,
	// making sure that TWINT is written to one, and TWSTA is written to zero
	I2C_sendAddress(slaveAddress, I2C_DIRECTION_TRANSMITTER);

	// 4. TWINT set. Status code indicates SLA+W sent, ACK received
	// 5. Check TWSR to see if SLA+W was sent and ACK received. Application
	// loads data into TWDR, and loads appropriate control signals into TWCR,
	// making sure that TWINT is written to one
	if (!I2C_getFlagStatus(I2C_FLAG_MT_SLA_W_ACK))
		return FALSE;

	// Send Data
	for (i = 0; i < dataLength; i++) {
		// Bits 7..0 TWD: I2C Data Register
		TWDR = dataTx[i];

		TWCR = (1 << TWINT) | (1 << TWEN);

		// 6. TWINT set. Status code indicates data sent, ACK received
		// 7. Check TWSR to see if data was sent and ACK received.
		while (!I2C_getFlagStatus(I2C_FLAG_TWINT))
			;
		if (!I2C_getFlagStatus(I2C_FLAG_MT_DATA_ACK))
			return FALSE;
	}

	// Application loads appropriate control signals to send STOP
	// into TWCR, making sure that TWINT is written to one
	// Stop Condition
	if (stopCondition == I2C_STOP_WITH) {
		// Bit 4 TWSTO: I2C STOP Condition Bit
		I2C_generateStop();
	}
	return TRUE;
}

// @brief Master receives data
// @param[in]  slaveAddress 	The slave address.
// @param[out]  dataRx  		The data to be received.
// @param[in]  stopCondition 	Receive with or without a stop bit.
// @param[in]  startCondition 	Receive with a repeated start or not.
// @return	   Return 0 if error occurred
uint8 MCAL_I2C_masterRx(uint16 slaveAddress, uint8 *dataRx, uint32 dataLength,
		uint8 stopCondition, uint8 startCondition) {
	uint32 i = 0;

	// 1. Application writes to TWCR to initiate transmission of START
	// 2. TWINT set. Status code indicates START condition sent
	I2C_generateStart();

	// 3. Check TWSR to see if START was sent.
	if (startCondition == I2C_START_NORMAL) {
		if (!I2C_getFlagStatus(I2C_FLAG_MT_START))
			return FALSE;
	} else {
		if (!I2C_getFlagStatus(I2C_FLAG_MT_REP_START))
			return FALSE;
	}

	// Application loads SLA+R into TWDR, and loads appropriate control signals into TWCR,
	// making sure that TWINT is written to one, and TWSTA is written to zero
	I2C_sendAddress(slaveAddress, I2C_DIRECTION_RECEIVER);

	// 4. TWINT set. Status code indicates SLA+R sent, ACK received
	// 5. Check TWSR to see if SLA+W was sent and ACK received. Application
	// loads data into TWDR, and loads appropriate control signals into TWCR,
	// making sure that TWINT is written to one
	if (!I2C_getFlagStatus(I2C_FLAG_MR_SLA_R_ACK))
		return FALSE;

	// Receive data
	for (i = 0; i < dataLength; i++) {
		if (I2C_g_config.ACK_control == I2C_ACK_CONTROL_ENABLE) {
			TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		} else {
			TWCR = (1 << TWINT) | (1 << TWEN);
		}

		// 6. TWINT set. Status code indicates data received, ACK sent
		// 7. Check TWSR to see if data was received and ACK sent.
		while (!I2C_getFlagStatus(I2C_FLAG_TWINT))
			;
		if (!I2C_getFlagStatus(I2C_FLAG_MR_DATA_ACK))
			return FALSE;

		// Bits 7..0 TWD: I2C Data Register
		dataRx[i] = TWDR;
	}

	// Application loads appropriate control signals to send STOP
	// into TWCR, making sure that TWINT is written to one
	// Stop Condition
	if (stopCondition == I2C_STOP_WITH) {
		// Bit 4 TWSTO: I2C STOP Condition Bit
		I2C_generateStop();
	}
	return TRUE;
}

// Slave with interrupt
// @brief Slave sends data
// @param[in]  dataTx  			The data to be sent.
void MCAL_I2C_slaveTx(uint8 *dataTx) {
	// Bits 7..0 TWD: I2C Data Register
	TWDR = *dataTx;
}

// @brief Slave receives data
// @param[out] dataRx  			The data to be received.
void MCAL_I2C_slaveRx(uint8 *dataRx) {
	// Bits 7..0 TWD: I2C Data Register
	*dataRx = TWDR;
}

// @brief Send an address
// @param[in]  address  		The address to be sent.
// @param[in]  directionMode  	Reading/Writing to the address.
void I2C_sendAddress(uint16 address, uint8 directionMode) {
	// Shift left by 1 to leave a space for the direction bit
	address <<= 1;

	if (directionMode == I2C_DIRECTION_RECEIVER) {
		// Read 1
		address |= (1 << 0);
	} else {
		// Write 0
		address &= ~(1 << 0);
	}
	// Bits 7..0 TWD: I2C Data Register
	TWDR = (uint8) address;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!I2C_getFlagStatus(I2C_FLAG_TWINT))
		;
}

// @brief Send start bit
// @param[in]  startCondition 	Send a repeated start or not.
void I2C_generateStart(void) {
	//The application writes the TWSTA bit to one when it desires to
	//become a master on the Two-wire Serial Bus. The I2C hardware checks
	//if the bus is available, and generates a START condition on
	//the bus if it is free. However, if the bus is not free, the I2C
	//waits until a STOP condition is detected, and then generates
	//a new START condition to claim the bus Master status. TWSTA
	//must be cleared by software when the START condition has been transmitted.
	// Immediately after the application has cleared TWINT,
	// the I2C will initiate transmission of the START condition.

	// Bit 5 TWSTA: I2C START Condition Bit
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (!I2C_getFlagStatus(I2C_FLAG_TWINT))
		;
}

// @brief Send stop bit
void I2C_generateStop(void) {
	//Writing the TWSTO bit to one in Master mode will generate a STOP condition on the Two-wire
	//Serial Bus. When the STOP condition is executed on the bus, the TWSTO bit is cleared automatically.
	//In slave mode, setting the TWSTO bit can be used to recover from an error condition.
	//This will not generate a STOP condition, but the I2C returns to a well-defined un-addressed
	//slave mode and releases the SCL and SDA lines to a high impedance state.
	// Immediately after the application has cleared TWINT,
	// the I2C will initiate transmission of the STOP condition.

	// Bit 4 TWSTO: I2C STOP Condition Bit
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

// @brief Return the status of a flag
// @param[in]  flag  		The flag to be checked.
// @return	   The value of flag status
uint8 I2C_getFlagStatus(uint8 flag) {
	uint8 statusValue = I2C_FLAG_STATUS_RESET;
	uint8 status = TWSR & 0xF8;

	if (flag == I2C_FLAG_TWINT) {
		statusValue = (TWCR & (1 << TWINT)) ?
		I2C_FLAG_STATUS_SET :
												I2C_FLAG_STATUS_RESET;
	} else {
		statusValue = (status == flag) ?
		I2C_FLAG_STATUS_SET :
											I2C_FLAG_STATUS_RESET;
	}
	return statusValue;
}

//*****************************************************************************
// IRQHandler Definitions
//*****************************************************************************
ISR(TWI_vect) {
	// Check for flags
	// Bit 7 TWINT: I2C Interrupt Flag
	//The TWINT Flag must be cleared by software by writing a logic one to it. Note that this flag is not
	//automatically cleared by hardware when executing the interrupt routine. Also note that clearing
	//this flag starts the operation of the I2C, so all accesses to the I2C Address Register (TWAR),
	//I2C Status Register (TWSR), and I2C Data Register (TWDR) must be complete before clearing
	//this flag.
	// Slave mode
	if (I2C_g_config.deviceMode == I2C_DEVICE_MODE_SLAVE) {
		if (I2C_getFlagStatus(I2C_FLAG_SR_SLA_W_ACK)) {
			I2C_g_config.P_IRQ_callBack(I2C_EV_ADDR_MATCHED);
			TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
		}

		if (I2C_getFlagStatus(I2C_FLAG_SR_DATA_ACK)) {
			I2C_g_config.P_IRQ_callBack(I2C_EV_DATA_RX);
			TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
		}

		if (I2C_getFlagStatus(I2C_FLAG_ST_SLA_R_ACK)) {
			TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
		}

		if (I2C_getFlagStatus(I2C_FLAG_ST_DATA_ACK)) {
			I2C_g_config.P_IRQ_callBack(I2C_EV_DATA_TX);
			TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1 << TWIE);
		}
	}

}
