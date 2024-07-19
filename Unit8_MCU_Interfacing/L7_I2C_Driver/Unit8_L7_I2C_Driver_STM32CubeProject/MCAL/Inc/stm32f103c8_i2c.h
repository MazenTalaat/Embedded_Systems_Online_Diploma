//*****************************************************************************
//
// Module: I2C
//
// File Name: stm32f103c8_i2c.h
//
// Description: Header file for the I2C driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef STM32F103C8_I2C_H_
#define STM32F103C8_I2C_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "stm32f103c8.h"
#include "stm32f103c8_gpio.h"
#include "stm32f103c8_rcc.h"
#include "std_types.h"
#include "common_macros.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct {
	uint32 enableDualAddress;
	uint16 primarySlaveAddress;
	uint16 secondarySlaveAddress;
	uint32 slaveAddressingMode; // Specifies the slave address mode 7/10 bits.
} I2C_Slave_Device_Addressing_Mode;

typedef struct {
	uint32 mode;     						// Specifies the mode I2C/SMBus.
	uint32 deviceMode;     							// Specifies master/slave.
	I2C_Slave_Device_Addressing_Mode slaveAddress; // Specifies the slave address options.
	uint32 clkSpeed; 		    					// Specifies clock speed.
	uint32 stretchMode;			// Enable or disable slave stretching the cLock.
	uint32 ACK_control;								// Specifies the ACK/NACK.
	uint32 generalCallAddressDetection;			// Specifies General call enable
	uint32 IRQ_enable;					// Enable or disable UART interrupts.
	void (*P_IRQ_callBack)(uint8);				// Interrupt callback function.
} I2C_Config;

//*****************************************************************************
// Definitions
//*****************************************************************************
#define I2C_SUPPORTED					2 // I2C1, I2C2
#define I2C_1_INDEX						0
#define I2C_2_INDEX						1

// I2C_mode_define
#define I2C_MODE_I2C 					0
//#define I2C_MODE_SMBUS				I2C_CR1_SMBUS // Not supported yet

// I2C_deviceMode_define
#define I2C_DEVICE_MODE_MASTER 			0
#define I2C_DEVICE_MODE_SLAVE			1

// I2C_slaveAddressingMode_define
#define I2C_SLAVE_ADDRESS_MODE_7BITS	0
//#define I2C_SLAVE_ADDRESS_MODE_10BITS	(1<<15) // Not supported yet

// I2C_enableDualAddress_define
#define I2C_SLAVE_DA_ENABLE				1
#define I2C_SLAVE_DA_MODE_DISABLE		0

//SPI_clkSpeed_define
#define I2C_CLK_SPEED_SM_50KHZ			(50000U)
#define I2C_CLK_SPEED_SM_100KHZ			(100000U)
//#define I2C_CLK_SPEED_FM_200KHZ		(200000U) // Fast Mode Not supported yet
//#define I2C_CLK_SPEED_FM_400KHZ		(400000U) // Fast Mode Not supported yet

// I2C_stretchMode_define
#define I2C_STRETCH_MODE_ENABLE			(0x00000000)
#define I2C_STRETCH_MODE_DISABLE		I2C_CR1_NOSTRETCH

// I2C_ACK_control_define
#define I2C_ACK_CONTROL_ENABLE			I2C_CR1_ACK
#define I2C_ACK_CONTROL_DISABLE			0

// I2C_generalCallAddressDetection_define
#define I2C_GCAD_ENABLE					I2C_CR1_ENGC
#define I2C_GCAD_DISABLE				0x00000000

// I2C_IRQ_enable_define
#define I2C_IRQ_NONE					(0x00000000)
#define I2C_IRQ_EV						(I2C_CR2_ITEVTEN)
#define I2C_IRQ_EV_TXE_RXNE				(I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN)
#define I2C_IRQ_ERR						(I2C_CR2_ITERREN)
#define I2C_IRQ_ALL						(I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN)

// I2C slave states
#define I2C_EV_STOP						0
#define I2C_ERROR_AF					1
#define I2C_EV_ADDR_MATCHED				2
#define I2C_EV_DATA_TX					3 // Data transmitted
#define I2C_EV_DATA_RX					4 // Data received

// I2C stop condition
#define I2C_STOP_WITHOUT 				0
#define I2C_STOP_WITH 					1

// I2C start condition
#define I2C_START_NORMAL 				0
#define I2C_START_REPEATED 				1

// I2C direction
#define I2C_DIRECTION_TRANSMITTER 		0
#define I2C_DIRECTION_RECEIVER 			1

// I2C status flags reset/set
#define I2C_FLAG_STATUS_RESET 			0
#define I2C_FLAG_STATUS_SET 			1

// I2C status flags
#define I2C_FLAG_SB   					0
#define I2C_FLAG_ADDR 					1
#define I2C_FLAG_BTF    				2
#define I2C_FLAG_ADD10  				3
#define I2C_FLAG_STOPF  				4
#define I2C_FLAG_RXNE   				5
#define I2C_FLAG_TXE    				6
#define I2C_FLAG_BERR   				7
#define I2C_FLAG_ARLO   				8
#define I2C_FLAG_AF     				9
#define I2C_FLAG_OVR    				10
#define I2C_FLAG_PECERR 				11
#define I2C_FLAG_MSL  					12
#define I2C_FLAG_BUSY 					13
#define I2C_FLAG_TRA 					14
#define I2C_FLAG_GENCALL				15
#define I2C_FLAG_DUALF					16
#define I2C_FLAG_MASTER_BYTE_TRANSMITTER ((uint32)0x00070080) // ((((MSL) | (BUSY) | (TRA)) << 16) | (TXE))

//*******************************************************************************
// Generic Macros
//*******************************************************************************

//*****************************************************************************
// I2C APIs Prototypes
//*****************************************************************************
void MCAL_I2C_init(I2C_TypeDef *I2Cx, I2C_Config *I2C_config);
void MCAL_I2C_deInit(I2C_TypeDef *I2Cx);

void MCAL_I2C_GPIO_setPins(I2C_TypeDef *I2Cx);

// Master with polling mechanism
void MCAL_I2C_masterTx(I2C_TypeDef *I2Cx, uint16 slaveAddress, uint8 *dataTx,
		uint32 dataLength, uint8 stopCondition, uint8 startCondition);
void MCAL_I2C_masterRx(I2C_TypeDef *I2Cx, uint16 slaveAddress, uint8 *dataRx,
		uint32 dataLength, uint8 stopCondition, uint8 startCondition);

// Slave with interrupt
void MCAL_I2C_saveTx(I2C_TypeDef *I2Cx, uint8 *dataTx);
void MCAL_I2C_slaveRx(I2C_TypeDef *I2Cx, uint8 *dataRx);

void I2C_sendAddress(I2C_TypeDef *I2Cx, uint16 address, uint8 directionMode);
void I2C_generateStart(I2C_TypeDef *I2Cx, uint8 startCondition);
void I2C_generateStop(I2C_TypeDef *I2Cx);
void I2C_ACK_control(I2C_TypeDef *I2Cx, uint16 ACK_state);
uint8 I2C_getFlagStatus(I2C_TypeDef *I2Cx, uint32 flag);

#endif // STM32F103C8_I2C_H_
