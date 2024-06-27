typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

/*********************** Registers Definitions  ***********************/

#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE +  0x08)

#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE +  0x00)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE +  0x04)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE +  0x0C)

//CNF0[1:0] MODE0[1:0] for each pin

//CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
//These bits are written by software to configure the corresponding I/O port.
//Refer to Table 20: Port bit configuration table.
//In input mode (MODE[1:0]=00):
//00: Analog mode
//01: Floating input (reset state)
//10: Input with pull-up / pull-down
//11: Reserved
//In output mode (MODE[1:0] > 00):
//00: General purpose output push-pull
//01: General purpose output Open-drain
//10: Alternate function output Push-pull
//11: Alternate function output Open-drain

//MODEy[1:0]: Port x mode bits (y= 0 .. 7)
//These bits are written by software to configure the corresponding I/O port.
//Refer to Table 20: Port bit configuration table.
//00: Input mode (reset state)
//01: Output mode, max speed 10 MHz.
//10: Output mode, max speed 2 MHz.
//11: Output mode, max speed 50 MHz
#define GPIOA_PIN1_MODE 0b0100
#define GPIOA_PIN13_MODE 0b0100

#define GPIOB_PIN1_MODE 0b0110
#define GPIOB_PIN13_MODE 0b0110

/**********************************************************************/

#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
//Bit 3 IOPBEN: IO port B clock enable
//Bit 2 IOPAEN: IO port A clock enable
#define RCC_APB2ENR_IOPAEN_BIT 2
#define RCC_APB2ENR_IOPBEN_BIT 3

void delay(int n) {
	int i;
	for (i = 0; i < n; i++)
		;
}

int main(void) {
	/* Enable GPIOA, GPIOB Clock */
	RCC_APB2ENR |= ((1 << RCC_APB2ENR_IOPAEN_BIT)
			| (1 << RCC_APB2ENR_IOPBEN_BIT));

	/* Configure LEDs at PB1, PB13 negative logic as Output*/
	/* 01: General purpose output Open-drain */
	/* 10: Output mode, max speed 2 MHz */
	GPIOB_CRL = (GPIOA_CRH & ~(((uint32_t) 0xF) << 4)) | (GPIOB_PIN1_MODE << 4);
	GPIOB_CRH = (GPIOA_CRH & ~(((uint32_t) 0xF) << 20))
			| (GPIOB_PIN13_MODE << 20);
	/* Turn off the LEDs */
	GPIOB_ODR |= ((1 << 1) | (1 << 13));

	/* Configure PB at PA1 pulled up, PA13 pulled down as Input */
	/* 01: Floating input (reset state) */
	/* 00: Input mode (reset state) */
	GPIOA_CRL = (GPIOA_CRL & ~(((uint32_t) 0xF) << 4)) | (GPIOA_PIN1_MODE << 4);
	GPIOA_CRH = (GPIOA_CRL & ~(((uint32_t) 0xF) << 20))
			| (GPIOA_PIN13_MODE << 20);

	uint8_t button1Pressed = 0;
	/* Loop forever */
	for (;;) {
		if ((((GPIOA_IDR >> 1) & 1) == 0) && !button1Pressed) {
			GPIOB_ODR ^= (1 << 1);
			button1Pressed = 1;
		}
		else if(((GPIOA_IDR >> 1) & 1) == 1){
			button1Pressed = 0;
		}

		if (((GPIOA_IDR >> 13) & 1) == 1) {
			GPIOB_ODR ^= (1 << 13);
			delay(5000);
		}
	}
}
