typedef unsigned int uint32_t;


/*********************** Registers Definitions  ***********************/
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
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
#define GPIOA_PIN0_MODE 0b0100
#define GPIOA_PIN13_MODE 0b0110

#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

/**********************************************************************/

#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
//Bit 2 IOPAEN: I/O port A clock enable
//Set and cleared by software.
//0: I/O port A clock disabled
//1:I/O port A clock enabled
#define RCC_APB2ENR_IOPAEN_BIT 2

//Bit 0 AFIOEN: Alternate function I/O clock enable
//Set and cleared by software.
//0: Alternate Function I/O clock disabled
//1:Alternate Function I/O clock enabled
#define RCC_APB2ENR_AFIOEN_BIT 0

/**********************************************************************/

#define AFIO_BASE 0x40010000
#define AFIO_EXTICR1 *(volatile uint32_t *)(AFIO_BASE +  0x08)
//Bits 15:0 EXTIx[3:0]: EXTI x configuration (x= 0 to 3)
//These bits are written by software to select the source input for EXTIx external interrupt.
//Refer to Section 10.2.5: External interrupt/event line mapping
//0000: PA[x] pin
//0001: PB[x] pin
//0010: PC[x] pin
//0011: PD[x] pin
//0100: PE[x] pin
//0101: PF[x] pin
//0110: PG[x] pin

/**********************************************************************/

#define EXTI_BASE 0x40010400
#define EXTI_IMR *(volatile uint32_t *)(EXTI_BASE +  0x00)
//Bits 19:0 MRx: Interrupt Mask on line x
//0: Interrupt request from Line x is masked
//1: Interrupt request from Line x is not masked

#define EXTI_RTSR *(volatile uint32_t *)(EXTI_BASE +  0x08)
//Bits 19:0 TRx: Rising trigger event configuration bit of line x
//0: Rising trigger disabled (for Event and Interrupt) for input line
//1: Rising trigger enabled (for Event and Interrupt) for input line.

#define EXTI_PR *(volatile uint32_t *)(EXTI_BASE +  0x14)
//Bits 19:0 PRx: Pending bit
//0: No trigger request occurred
//1: selected trigger request occurred
//This bit is set when the selected edge event arrives on the external interrupt line. This bit is
//cleared by writing a ‘1’ into the bit.

/**********************************************************************/

#define NVIC_ISER0 *(volatile uint32_t *)(0xE000E100)
//6 13 settable EXTI0 EXTI Line0 interrupt 0x0000_0058


int main(void)
{
	/* Enable GPIOA, AFIO Clock */
	RCC_APB2ENR |= ((1<<RCC_APB2ENR_IOPAEN_BIT) | (1<<RCC_APB2ENR_AFIOEN_BIT));

	/* Configure LED at PA13 negative logic as Output*/
	/* 01: General purpose output Open-drain */
	/* 10: Output mode, max speed 2 MHz */
	GPIOA_CRH = (GPIOA_CRH & ~(0xFF<<20)) | (GPIOA_PIN13_MODE<<20);
	/* Turn off the LED */
	GPIOA_ODR |= (1<<13);

	/* Configure PB at PA0 Pulled down as Input and EXTI */
	/* 01: Floating input (reset state) */
	/* 00: Input mode (reset state) */
	GPIOA_CRL = (GPIOA_CRL & ~(0xFF<<0)) | (GPIOA_PIN0_MODE<<0);

	/* Configure EXTI0 to trigger at rising edge  */
	AFIO_EXTICR1 = 0;
	EXTI_IMR |= (1<<0);
	EXTI_RTSR |= (1<<0);

	/* Enable NVIC EXTI0 */
	NVIC_ISER0 |= (1<<6);

    /* Loop forever */
	for(;;);
}

void EXTI0_IRQHandler(void){
	/* Clear interrupt flag */
	EXTI_PR |= (1<<0);

	/* Toggle the led */
	GPIOA_ODR ^= (1<<13);
}
