//*****************************************************************************
//
// Module: I2C
//
// File Name: atmega32_i2c.h
//
// Description: Header file for the I2C driver
//
// Author: Mazen Talaat
//
//*****************************************************************************
#ifndef ATMEGA32_I2C_H_
#define ATMEGA32_I2C_H_

//*******************************************************************************
// Includes
//*******************************************************************************
#include "atmega32.h"
#include "atmega32_gpio.h"
#include "avr/interrupt.h"
#include "std_types.h"

//*******************************************************************************
// Types Declaration
//*******************************************************************************
typedef struct {
	uint8 deviceMode;     				// Specifies master/slave.
	uint8 slaveAddress; 				// Specifies the slave address options.
	uint8 clkSpeed; 		    		// Specifies clock speed.
	uint8 ACK_control;					// Specifies the ACK/NACK.
	uint8 generalCallAddressDetection;	// Specifies General call enable
	uint8 IRQ_enable;					// Enable or disable UART interrupts.
	void (*P_IRQ_callBack)(uint8);		// Interrupt callback function.
} I2C_Config;

//*****************************************************************************
// Definitions
//*****************************************************************************
// I2C_deviceMode_define
#define I2C_DEVICE_MODE_MASTER 			0
#define I2C_DEVICE_MODE_SLAVE			1

// I2C_clkSpeed_define
//#define I2C_CLK_SPEED_50KHZ			0
//#define I2C_CLK_SPEED_100KHZ			1
#define I2C_CLK_SPEED_400KHZ			2

// I2C_ACK_control_define
#define I2C_ACK_CONTROL_ENABLE			(1<<TWEA)
#define I2C_ACK_CONTROL_DISABLE			0

// I2C_generalCallAddressDetection_define
#define I2C_GCAD_ENABLE					(1<<TWGCE)
#define I2C_GCAD_DISABLE				0

// I2C_IRQ_enable_define
#define I2C_IRQ_NONE					0
#define I2C_IRQ_ENABLE					1

// I2C slave states
#define I2C_EV_ERROR					1
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
#define I2C_FLAG_TWINT   				0x00
#define I2C_FLAG_MT_START         		0x08 // A START condition has been transmitted
#define I2C_FLAG_MT_REP_START     		0x10 // A repeated START condition has been transmitted

#define I2C_FLAG_MT_SLA_W_ACK  			0x18 // SLA+W has been transmitted; ACK has been received
#define I2C_FLAG_MT_SLA_W_NACK  		0x20 // SLA+W has been transmitted; NOT ACK has been received
#define I2C_FLAG_MT_DATA_ACK   			0x28 // Data byte has been transmitted; ACK has been received
#define I2C_FLAG_MT_DATA_NACK   		0x30 // Data byte has been transmitted; ACK has been received
#define I2C_FLAG_MR_SLA_R_ACK  			0x40 // SLA+R has been transmitted; ACK has been received
#define I2C_FLAG_MR_DATA_ACK   			0x50 // Data byte has been received; ACK has been returned
#define I2C_FLAG_MR_DATA_NACK  			0x58 // Data byte has been received; NOT ACK has been returned

#define I2C_FLAG_ST_SLA_R_ACK  			0xA8 // Own SLA+R has been received; ACK has been returned
#define I2C_FLAG_ST_DATA_ACK  			0xB8 // Data byte in TWDR has been transmitted; ACK has been received
#define I2C_FLAG_ST_DATA_NACK  			0xC0 // Data byte in TWDR has been transmitted; NOT ACK has been received
#define I2C_FLAG_ST_LASTDATA_NACK  		0xC8 //  Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received
#define I2C_FLAG_SR_SLA_W_ACK  			0x60 // Own SLA+W has been received; ACK has been returned
#define I2C_FLAG_SR_DATA_ACK  			0x80 // Previously addressed with own SLA+W; data has been received; ACK has been returned
#define I2C_FLAG_SR_DATA_NACK  			0x88 // Previously addressed with own SLA+W; data has been received; NOT ACK has been returned

//*****************************************************************************
// I2C APIs Prototypes
//*****************************************************************************
void MCAL_I2C_init(I2C_Config *I2C_config);
void MCAL_I2C_deInit(void);

// Master with polling mechanism
uint8 MCAL_I2C_masterTx(uint16 slaveAddress, uint8 *dataTx, uint32 dataLength,
		uint8 stopCondition, uint8 startCondition);
uint8 MCAL_I2C_masterRx(uint16 slaveAddress, uint8 *dataRx, uint32 dataLength,
		uint8 stopCondition, uint8 startCondition);

// Slave with interrupt
void MCAL_I2C_slaveTx(uint8 *dataTx);
void MCAL_I2C_slaveRx(uint8 *dataRx);

void I2C_sendAddress(uint16 address, uint8 directionMode);
void I2C_generateStart(void);
void I2C_generateStop(void);
uint8 I2C_getFlagStatus(uint8 flag);

#endif // ATMEGA32_I2C_H_
