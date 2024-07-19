//*****************************************************************************
//
// Module: I2C
//
// File Name: stm32f103c8_i2c.c
//
// Description: Source file for the I2C driver
//
// Author: Mazen Talaat
//
//*****************************************************************************

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c8_i2c.h"

//*****************************************************************************
// Global variables
//*****************************************************************************
I2C_Config I2C_g_configs[I2C_SUPPORTED];

//*****************************************************************************
// Functions Definitions
//*****************************************************************************
// @brief Initialize the I2C device
// @param[in]  I2Cx  		The I2C to be configured.
// @param[in]  I2C_config  	The needed configuration.
void MCAL_I2C_init(I2C_TypeDef *I2Cx, I2C_Config *I2C_config) {
	uint32 PCLK1_Hz = MCAL_RCC_getPCLK1Freq();
	uint16 PCLK1_MHz = (uint16) (PCLK1_Hz / 1000000);

	// Enable RCC Clock
	if (I2Cx == I2C1) {
		RCC_I2C1_CLK_EN();
		I2C_g_configs[I2C_1_INDEX] = *I2C_config;
	} else if (I2Cx == I2C2) {
		RCC_I2C2_CLK_EN();
		I2C_g_configs[I2C_2_INDEX] = *I2C_config;
	}

	// Disable the peripheral in case if initialized before
	I2Cx->CR1 &= ~(I2C_CR1_PE);

	if (I2C_config->mode == I2C_MODE_I2C) {
		// Program the peripheral input clock in I2C_CR2 Register
		// in order to generate correct timings
		// Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		// Clear the bits
		I2Cx->CR2 &= ~(I2C_CR2_FREQ_Msk);
		I2Cx->CR2 |= PCLK1_MHz;

		if ((I2C_config->clkSpeed == I2C_CLK_SPEED_SM_50KHZ)
				|| (I2C_config->clkSpeed == I2C_CLK_SPEED_SM_100KHZ)) {
			// Configure the clock control registers
			// Bit 15 Fm/Sm: I2C master mode selection
			// Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode (Master mode)
			// Sm mode
			// Thigh = CCR * TPCLK1
			// Tlow = CCR * TPCLK1
			// Tclk/2 = CCR * TPCLK1
			// CCR = (Tclk / 2 * TPCLK1)
			// CCR =(FPCLK1 / 2 * Fclk)
			I2Cx->CCR = (uint16) (PCLK1_Hz / (I2C_config->clkSpeed << 1));

			// Configure the rise time register
			// Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
			// These bits should provide the maximum duration of the SCL feedback loop in master mode.
			// (1000 ns / TPCLK1 ns = x + 1)
			I2Cx->TRISE = (PCLK1_MHz + 1);
		} else {
			// Fast Mode not supported yet
		}

		// Program the I2C_CR1 register to enable the peripheral
		// Bit 10 ACK: Acknowledge enable
		// Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
		// Bit 6 ENGC: General call enable
		// Bit 1 SMBUS: SMBus mode
		I2Cx->CR1 |=
				((I2C_config->ACK_control) | (I2C_config->stretchMode)
						| (I2C_config->generalCallAddressDetection)
						| (I2C_config->mode));

		// Program the I2C_OAR1, I2C_OAR2 registers in case of slave
		if (I2C_config->slaveAddress.enableDualAddress == I2C_SLAVE_DA_ENABLE) {
			// Bit 0 ENDUAL: Dual addressing mode enable
			I2Cx->OAR2 |= I2C_OAR2_ENDUAL;
			// Bits 7:1 ADD2[7:1]: Interface address
			I2Cx->OAR2 |= ((I2C_config->slaveAddress.secondarySlaveAddress)
					<< I2C_OAR2_ADD2_Pos);
		}

		// Bits 7:1 ADD[7:1]: Interface address
		I2Cx->OAR1 |= ((I2C_config->slaveAddress.primarySlaveAddress) << 1);

		// Bit 15 ADDMODE Addressing mode (slave mode)
		I2Cx->OAR1 |= I2C_config->slaveAddress.slaveAddressingMode;

	} else {
		// SMBus not supported
	}

	if (I2C_config->IRQ_enable) {
		I2Cx->CR2 |= I2C_config->IRQ_enable;

		// Enable NVIC
		if (I2Cx == I2C1) {
			if (I2C_config->IRQ_enable == I2C_IRQ_ALL) {
				NVIC_IRQ31_I2C1_EV_ENABLE;
				NVIC_IRQ32_I2C1_ER_ENABLE;
			} else if ((I2C_config->IRQ_enable == I2C_IRQ_EV)
					|| (I2C_config->IRQ_enable == I2C_IRQ_EV_TXE_RXNE)) {
				NVIC_IRQ31_I2C1_EV_ENABLE;
			} else {
				NVIC_IRQ32_I2C1_ER_ENABLE;
			}

		} else if (I2Cx == I2C2) {
			if (I2C_config->IRQ_enable == I2C_IRQ_ALL) {
				NVIC_IRQ33_I2C2_EV_ENABLE;
				NVIC_IRQ34_I2C2_ER_ENABLE;
			} else if ((I2C_config->IRQ_enable == I2C_IRQ_EV)
					|| (I2C_config->IRQ_enable == I2C_IRQ_EV_TXE_RXNE)) {
				NVIC_IRQ33_I2C2_EV_ENABLE;
			} else {
				NVIC_IRQ34_I2C2_ER_ENABLE;
			}
		}
		// Reset status registers
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}
	// Bit 0 PE: Peripheral enable
	I2Cx->CR1 |= I2C_CR1_PE;
}

// @brief Reset the I2C.
// @param[in]  I2Cx  		The I2C to get reset.
void MCAL_I2C_deInit(I2C_TypeDef *I2Cx) {
	if (I2Cx == I2C1) {
		RCC_I2C1_RESET();
		NVIC_IRQ31_I2C1_EV_DISABLE;
		NVIC_IRQ32_I2C1_ER_DISABLE;
	} else if (I2Cx == I2C2) {
		RCC_I2C2_RESET();
		NVIC_IRQ33_I2C2_EV_DISABLE;
		NVIC_IRQ34_I2C2_ER_DISABLE;
	}
}

// @brief Initialize GPIO pins.
// @param[in]  I2Cx  		The corresponding I2C.
void MCAL_I2C_GPIO_setPins(I2C_TypeDef *I2Cx) {
	GPIO_PinConfig pinConfig;

	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	if (I2Cx == I2C1) {
		// PB6 : SCL
		pinConfig.GPIO_pinNumber = GPIO_PIN_6;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_OPEN_DRAIN;
		pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
		MCAL_GPIO_init(GPIOB, &pinConfig);

		// PB7 : SDA
		pinConfig.GPIO_pinNumber = GPIO_PIN_7;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_OPEN_DRAIN;
		pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
		MCAL_GPIO_init(GPIOB, &pinConfig);

	} else if (I2Cx == I2C2) {
		// PB10 : SCL
		pinConfig.GPIO_pinNumber = GPIO_PIN_10;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_OPEN_DRAIN;
		pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
		MCAL_GPIO_init(GPIOB, &pinConfig);

		// PB11 : SDA
		pinConfig.GPIO_pinNumber = GPIO_PIN_11;
		pinConfig.GPIO_pinMode = GPIO_MODE_OUT_AF_OPEN_DRAIN;
		pinConfig.GPIO_pinOutputSpeed = GPIO_OUTPUT_SPEED_10MHZ;
		MCAL_GPIO_init(GPIOB, &pinConfig);

	}
}

// Master with polling mechanism
// @brief Master sends data
// @param[in]  I2Cx  			The corresponding I2C.
// @param[in]  slaveAddress 	The slave address.
// @param[in]  dataTx  			The data to be sent.
// @param[in]  stopCondition 	Send with or without a stop bit.
// @param[in]  startCondition 	Send a repeated start or not.
void MCAL_I2C_masterTx(I2C_TypeDef *I2Cx, uint16 slaveAddress, uint8 *dataTx,
		uint32 dataLength, uint8 stopCondition, uint8 startCondition) {
	uint32 i = 0;

	// Set the START bit in the I2C_CR1 register to generate a Start condition.
	I2C_generateStart(I2Cx, startCondition);

	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	// Bit 0 SB: Start bit (Master mode).
	while (!I2C_getFlagStatus(I2Cx, I2C_FLAG_SB))
		;

	// Send slave address.
	// Bits 7:0 DR[7:0] 8-bit data register.
	I2C_sendAddress(I2Cx, slaveAddress, I2C_DIRECTION_TRANSMITTER);

	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	// Bit 1 ADDR: Address sent (master mode)/matched (slave mode).
	while (!(I2C_getFlagStatus(I2Cx, I2C_FLAG_ADDR)))
		;

	// Check Event that Master transmitted byte TRA , MSL , BUSY , TXE
	// EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	while (!(I2C_getFlagStatus(I2Cx, I2C_FLAG_MASTER_BYTE_TRANSMITTER)))
		;

	// Send Data
	for (i = 0; i < dataLength; i++) {
		// Bits 7:0 DR[7:0] 8-bit data register
		I2Cx->DR = dataTx[i];

		// EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while (!I2C_getFlagStatus(I2Cx, I2C_FLAG_TXE))
			;
	}

	// Stop Condition
	if (stopCondition == I2C_STOP_WITH) {
		// EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
		// Bit 9 STOP: Stop generation
		I2C_generateStop(I2Cx);
	}
}

// @brief Master receives data
// @param[in]  I2Cx  			The corresponding I2C.
// @param[in]  slaveAddress 	The slave address.
// @param[out]  dataRx  		The data to be received.
// @param[in]  stopCondition 	Receive with or without a stop bit.
// @param[in]  startCondition 	Receive with a repeated start or not.
void MCAL_I2C_masterRx(I2C_TypeDef *I2Cx, uint16 slaveAddress, uint8 *dataRx,
		uint32 dataLength, uint8 stopCondition, uint8 startCondition) {
	uint32 i = 0;
	// Bit 0 SB: Start bit (Master mode).
	I2C_generateStart(I2Cx, startCondition);

	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	// Bit 0 SB: Start bit (Master mode).
	while (!I2C_getFlagStatus(I2Cx, I2C_FLAG_SB))
		;

	// Send slave address.
	// Bits 7:0 DR[7:0] 8-bit data register.
	I2C_sendAddress(I2Cx, slaveAddress, I2C_DIRECTION_RECEIVER);

	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	// Bit 1 ADDR: Address sent (master mode)/matched (slave mode).
	while (!(I2C_getFlagStatus(I2Cx, I2C_FLAG_ADDR)))
		;

	// Bit 10 ACK: Acknowledge enable.
	I2C_ACK_control(I2Cx, I2C_ACK_CONTROL_ENABLE);

	for (i = 0; i < dataLength; i++) {
		// EV7: RxNE=1 cleared by reading DR register.
		// Bit 6 RxNE: Data register not empty (receivers).
		while (!(I2C_getFlagStatus(I2Cx, I2C_FLAG_RXNE)))
			;

		dataRx[i] = I2Cx->DR;
	}
	// EV7_1: RxNE=1 cleared by reading DR register, program ACK=0 and STOP request.
	// Bit 10 ACK: Acknowledge enable.
	I2C_ACK_control(I2Cx, I2C_ACK_CONTROL_DISABLE);

	// Stop Condition.
	if (stopCondition == I2C_STOP_WITH) {
		// Bit 9 STOP: Stop generation.
		I2C_generateStop(I2Cx);
	}

	// Re-enable ACK if true.
	if (I2Cx == I2C1) {
		if (I2C_g_configs[0].ACK_control == I2C_ACK_CONTROL_ENABLE) {
			I2C_ACK_control(I2Cx, I2C_ACK_CONTROL_ENABLE);
		}
	} else if (I2Cx == I2C2) {
		if (I2C_g_configs[1].ACK_control == I2C_ACK_CONTROL_ENABLE) {
			I2C_ACK_control(I2Cx, I2C_ACK_CONTROL_ENABLE);
		}
	}
}

// Slave with interrupt
// @brief Slave sends data
// @param[in]  I2Cx  			The corresponding I2C.
// @param[in]  dataTx  			The data to be sent.
void MCAL_I2C_saveTx(I2C_TypeDef *I2Cx, uint8 *dataTx) {
	I2Cx->DR = *dataTx;
}

// @brief Slave receives data
// @param[in]  I2Cx  			The corresponding I2C.
// @param[out] dataRx  			The data to be received.
void MCAL_I2C_slaveRx(I2C_TypeDef *I2Cx, uint8 *dataRx) {
	*dataRx = I2Cx->DR;
}

// @brief Send an address
// @param[in]  I2Cx  			The corresponding I2C.
// @param[in]  address  		The address to be sent.
// @param[in]  directionMode  	Reading/Writing to the address.
void I2C_sendAddress(I2C_TypeDef *I2Cx, uint16 address, uint8 directionMode) {
	// Shift left by 1 to leave a space for the direction bit
	address <<= 1;

	if (directionMode == I2C_DIRECTION_RECEIVER) {
		// Read 1
		address |= (1 << 0);
	} else {
		// Write 0
		address &= ~(1 << 0);
	}
	// Bits 7:0 DR[7:0] 8-bit data register
	I2Cx->DR = address;
}

// @brief Send start bit
// @param[in]  I2Cx  			The corresponding I2C.
// @param[in]  startCondition 	Send a repeated start or not.
void I2C_generateStart(I2C_TypeDef *I2Cx, uint8 startCondition) {
	// Set the START bit in the I2C_CR1 register to generate a Start condition
	if (startCondition == I2C_START_NORMAL) {
		// Bit 1 BUSY: Bus busy
		while (I2C_getFlagStatus(I2Cx, I2C_FLAG_BUSY))
			;
	}
	// Bit 8 START: Start generation
	I2Cx->CR1 |= I2C_CR1_START;
}

// @brief Send stop bit
// @param[in]  I2Cx  			The corresponding I2C.
void I2C_generateStop(I2C_TypeDef *I2Cx) {
	// Bit 9 STOP: Stop generation
	I2Cx->CR1 |= I2C_CR1_STOP;
}

// @brief Send ACK or NACK
// @param[in]  I2Cx  			The corresponding I2C.
// @param[in]  ACK_state  		Enable/Disable ACK.
void I2C_ACK_control(I2C_TypeDef *I2Cx, uint16 ACK_state) {
	// Bit 10 ACK: Acknowledge enable
	if (ACK_state == I2C_ACK_CONTROL_ENABLE) {
		I2Cx->CR1 |= I2C_ACK_CONTROL_ENABLE;
	} else {
		I2Cx->CR1 &= ~I2C_ACK_CONTROL_ENABLE;
	}
}

// @brief Return the status of a flag
// @param[in]  I2Cx  		The corresponding I2C.
// @param[in]  flag  		Enable/Disable ACK.
// @return	   The value of flag status
uint8 I2C_getFlagStatus(I2C_TypeDef *I2Cx, uint32 flag) {
	volatile uint32 dummyRead = 0;
	uint32 flag1 = 0, flag2 = 0, lastevent = 0;
	uint32 statusValue = I2C_FLAG_STATUS_RESET;

	switch (flag) {
	case I2C_FLAG_SB: {
		//Bit 0 SB: Start bit (Master mode)
		//0: No Start condition
		//1: Start condition generated.
		//– Set when a Start condition generated.
		//– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//hardware when PE=0
		statusValue =
		GET_BIT(I2Cx->SR1, I2C_SR1_SB_Pos) ?
		I2C_FLAG_STATUS_SET :
												I2C_FLAG_STATUS_RESET;
		break;
	}
	case I2C_FLAG_ADDR: {
		//Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		//This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
		//when PE=0.
		//Address matched (Slave)
		//0: Address mismatched or not received.
		//1: Received address matched.
		//Address sent (Master)
		//0: No end of address transmission
		//1: End of address transmission
		statusValue =
		GET_BIT(I2Cx->SR1, I2C_SR1_ADDR_Pos) ?
		I2C_FLAG_STATUS_SET :
												I2C_FLAG_STATUS_RESET;
		dummyRead = I2Cx->SR2;
		break;
	}
	case I2C_FLAG_STOPF: {
		//Bit 4 STOPF: Stop detection (slave mode)
		//0: No Stop condition detected
		//1: Stop condition detected
		//– Set by hardware when a Stop condition is detected on the bus by the slave after an
		//acknowledge (if ACK=1).
		//– Cleared by software reading the SR1 register followed by a write in the CR1 register, or by
		//hardware when PE=0
		statusValue =
		GET_BIT(I2Cx->SR1, I2C_SR1_STOPF_Pos) ?
		I2C_FLAG_STATUS_SET :
												I2C_FLAG_STATUS_RESET;
		break;
	}
	case I2C_FLAG_RXNE: {
		//Bit 6 RxNE: Data register not empty (receivers)
		//0: Data register empty
		//1: Data register not empty
		//– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//– Cleared by software reading or writing the DR register or by hardware when PE=0.
		//RxNE is not set in case of ARLO event.
		statusValue =
		GET_BIT(I2Cx->SR1, I2C_SR1_RXNE_Pos) ?
		I2C_FLAG_STATUS_SET :
												I2C_FLAG_STATUS_RESET;
		break;
	}
	case I2C_FLAG_TXE: {
		//Bit 7 TxE: Data register empty (transmitters)
		//0: Data register not empty
		//1: Data register empty
		//– Set when DR is empty in transmission. TxE is not set during address phase.
		//– Cleared by software writing to the DR register or by hardware after a start or a stop condition
		//or when PE=0.
		//TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
		statusValue =
		GET_BIT(I2Cx->SR1, I2C_SR1_TXE_Pos) ?
		I2C_FLAG_STATUS_SET :
												I2C_FLAG_STATUS_RESET;
		break;
	}
	case I2C_FLAG_TRA: {
		//Bit 2 TRA: Transmitter/receiver
		//0: Data bytes received
		//1: Data bytes transmitted
		//This bit is set depending on the R/W bit of the address byte, at the end of total address
		//phase.
		//It is also cleared by hardware after detection of Stop condition (STOPF=1), repeated Start
		//condition, loss of bus arbitration (ARLO=1), or when PE=0.
		statusValue =
		GET_BIT(I2Cx->SR2, I2C_SR2_TRA_Pos) ?
		I2C_FLAG_STATUS_SET :
												I2C_FLAG_STATUS_RESET;
		break;
	}
	case I2C_FLAG_BUSY: {
		//Bit 1 BUSY: Bus busy
		//0: No communication on the bus
		//1: Communication ongoing on the bus
		//– Set by hardware on detection of SDA or SCL low
		//– cleared by hardware on detection of a Stop condition.
		//It indicates a communication in progress on the bus. This information is still updated when
		//the interface is disabled (PE=0).
		statusValue =
		GET_BIT(I2Cx->SR2, I2C_SR2_BUSY_Pos) ?
		I2C_FLAG_STATUS_SET :
												I2C_FLAG_STATUS_RESET;
		break;
	}
	case I2C_FLAG_MASTER_BYTE_TRANSMITTER: {
		// ((I2C_FLAG_TRA) | (I2C_FLAG_BUSY) | (I2C_FLAG_TXE) | (I2C_FLAG_MSL))
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2 << 16;
		//Get last event value from I2C Status Register
		lastevent = (flag1 | flag2) & ((uint32) 0x00FFFFFF);
		statusValue = ((lastevent & flag) == flag) ?
		I2C_FLAG_STATUS_SET :
														I2C_FLAG_STATUS_RESET;
		break;
	}
	}
	return statusValue;
}

//*****************************************************************************
// Helper functions definitions
//*****************************************************************************
static uint8 I2C_IRQ_type(uint8 I2C_index, uint8 event) {
	uint32 IRQ_type = I2C_g_configs[I2C_index].IRQ_enable;
	switch (IRQ_type) {
	case I2C_IRQ_NONE:
		return 0;
		break;
	case I2C_IRQ_EV:
		if (I2C_EV_ADDR_MATCHED == event) {
			return 1;
		} else {
			return 0;
		}
		break;
	case I2C_IRQ_EV_TXE_RXNE:
		if ((I2C_EV_ADDR_MATCHED == event) || (I2C_EV_DATA_TX == event)
				|| (I2C_EV_DATA_RX == event)) {
			return 1;
		} else {
			return 0;
		}
		break;
	case I2C_IRQ_ERR:
		if (I2C_ERROR_AF == event) {
			return 1;
		} else {
			return 0;
		}
		break;
	case I2C_IRQ_ALL:
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

//*****************************************************************************
// IRQHandler Definitions
//*****************************************************************************
void I2C1_EV_IRQHandler(void) {
	volatile uint32 dummyRead = 0;

	// Slave mode
	if (I2C_g_configs[I2C_1_INDEX].deviceMode == I2C_DEVICE_MODE_SLAVE) {
		// handle interrupt generated by stop Event
		// Bit 4 STOPF: Stop detection (slave mode)
		if (I2C_IRQ_type(I2C_1_INDEX, I2C_EV_STOP)
				&& I2C_getFlagStatus(I2C1, I2C_FLAG_STOPF)) {
			//– Cleared by software reading the SR1 register followed by a write in the CR1 register, or by
			//hardware when PE=0
			dummyRead = I2C1->SR1;
			I2C1->CR1 |= 0;
			I2C_g_configs[I2C_1_INDEX].P_IRQ_callBack(I2C_EV_STOP);
		}
		// handle interrupt generated by address matched event
		// Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		if (I2C_IRQ_type(I2C_1_INDEX, I2C_EV_ADDR_MATCHED)
				&& I2C_getFlagStatus(I2C1, I2C_FLAG_ADDR)) {
			//This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
			//when PE=0.
			dummyRead = I2C1->SR1;
			dummyRead = I2C1->SR2;
			I2C_g_configs[I2C_1_INDEX].P_IRQ_callBack(
			I2C_EV_ADDR_MATCHED);
		}
		// handle interrupt generated by RXNE event
		// Bit 6 RxNE: Data register not empty (receivers)
		if (I2C_IRQ_type(I2C_1_INDEX, I2C_EV_DATA_RX)
				&& I2C_getFlagStatus(I2C1, I2C_FLAG_RXNE)) {
			I2C_g_configs[I2C_1_INDEX].P_IRQ_callBack(
			I2C_EV_DATA_RX);
		}
		// handle interrupt generated by TXE event
		// Bit 7 TxE: Data register empty (transmitters)
		if (I2C_IRQ_type(I2C_1_INDEX, I2C_EV_DATA_TX)
				&& I2C_getFlagStatus(I2C1, I2C_FLAG_TXE)) {
			I2C_g_configs[I2C_1_INDEX].P_IRQ_callBack(
			I2C_EV_DATA_TX);
		}
	} else {
		// Master mode is not supported
	}
}

void I2C1_ER_IRQHandler(void) {

}

void I2C2_EV_IRQHandler(void) {
	volatile uint32 dummyRead = 0;

	// Slave mode
	if (I2C_g_configs[I2C_2_INDEX].deviceMode == I2C_DEVICE_MODE_SLAVE) {
		// handle interrupt generated by stop Event
		// Bit 4 STOPF: Stop detection (slave mode)
		if (I2C_IRQ_type(I2C_2_INDEX, I2C_EV_STOP)
				&& I2C_getFlagStatus(I2C2, I2C_FLAG_STOPF)) {
			//– Cleared by software reading the SR1 register followed by a write in the CR1 register, or by
			//hardware when PE=0
			dummyRead = I2C2->SR1;
			// Clear PE
			I2C2->CR1 &= ~(I2C_CR1_PE_Msk);
			I2C_g_configs[I2C_2_INDEX].P_IRQ_callBack(I2C_EV_STOP);
		}
		// handle interrupt generated by address matched event
		// Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		if (I2C_IRQ_type(I2C_2_INDEX, I2C_EV_ADDR_MATCHED)
				&& I2C_getFlagStatus(I2C2, I2C_FLAG_ADDR)) {
			//This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
			//when PE=0.
			dummyRead = I2C2->SR1;
			dummyRead = I2C2->SR2;
			I2C_g_configs[I2C_2_INDEX].P_IRQ_callBack(
			I2C_EV_ADDR_MATCHED);
		}
		// handle interrupt generated by RXNE event
		// Bit 6 RxNE: Data register not empty (receivers)
		if (I2C_IRQ_type(I2C_2_INDEX, I2C_EV_DATA_RX)
				&& I2C_getFlagStatus(I2C2, I2C_FLAG_RXNE)) {
			// Bit 2 TRA: Transmitter/receiver
			if (!I2C_getFlagStatus(I2C2, I2C_FLAG_TRA)) {
				I2C_g_configs[I2C_2_INDEX].P_IRQ_callBack(
				I2C_EV_DATA_RX);
			}
		}
		// handle interrupt generated by TXE event
		// Bit 7 TxE: Data register empty (transmitters)
		if (I2C_IRQ_type(I2C_2_INDEX, I2C_EV_DATA_TX)
				&& I2C_getFlagStatus(I2C2, I2C_FLAG_TXE)) {
			// Bit 2 TRA: Transmitter/receiver
			if (I2C_getFlagStatus(I2C2, I2C_FLAG_TRA)) {
				I2C_g_configs[I2C_2_INDEX].P_IRQ_callBack(
				I2C_EV_DATA_TX);
			}
		}
	} else {
		// Master mode is not supported
	}
}

void I2C2_ER_IRQHandler(void) {

}
