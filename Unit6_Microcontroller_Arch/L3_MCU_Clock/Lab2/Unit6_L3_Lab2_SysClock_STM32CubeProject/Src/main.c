#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef volatile unsigned int vuint32_t;

// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_CR *(volatile uint32_t *)(RCC_BASE + 0x00)

//Bit 25 PLLRDY: PLL clock ready flag
//Set by hardware to indicate that the PLL is locked.
//0: PLL unlocked
//1: PLL locked
#define RCC_PLLRDY_BIT 25

//Bit 24 PLLON: PLL enable
//Set and cleared by software to enable PLL.
//Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
//PLL clock is used as system clock or is selected to become the system clock.
//0: PLL OFF
//1: PLL ON
#define RCC_PLLON_BIT 24

#define RCC_CFGR *(volatile uint32_t *)(RCC_BASE + 0x04)

//Bits 21:18 PLLMUL: PLL multiplication factor
//These bits are written by software to define the PLL multiplication factor. These bits can be
//written only when PLL is disabled.
//Caution: The PLL output frequency must not exceed 72 MHz.
//0000: PLL input clock x 2
//0001: PLL input clock x 3
//0010: PLL input clock x 4
//0011: PLL input clock x 5
//0100: PLL input clock x 6
//0101: PLL input clock x 7
//0110: PLL input clock x 8
//0111: PLL input clock x 9
//1000: PLL input clock x 10
//1001: PLL input clock x 11
//1010: PLL input clock x 12
//1011: PLL input clock x 13
//1100: PLL input clock x 14
//1101: PLL input clock x 15
//1110: PLL input clock x 16
//1111: PLL input clock x 16
#define RCC_PLLMUL_BIT 18

enum PLL_MUL {
	PLL_2,
	PLL_3,
	PLL_4,
	PLL_5,
	PLL_6,
	PLL_7,
	PLL_8,
	PLL_9,
	PLL_10,
	PLL_11,
	PLL_12,
	PLL_13,
	PLL_14,
	PLL_15,
	PLL_16
};

//Bit 16 PLLSRC: PLL entry clock source
//Set and cleared by software to select PLL clock source. This bit can be written only when
//PLL is disabled.
//0: HSI oscillator clock / 2 selected as PLL input clock
//1: HSE oscillator clock selected as PLL input clock
#define RCC_PLLSRC_BIT 16

//Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
//Set and cleared by software to control the division factor of the APB high-speed clock
//(PCLK2).
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
#define RCC_PPRE2_BIT 11

//Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
//Set and cleared by software to control the division factor of the APB low-speed clock
//(PCLK1).
//Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
#define RCC_PPRE1_BIT 8

enum HCLK_Prescaler {
	HCLK_1, HCLK_2 = 4, HCLK_4, HCLK_8, HCLK_16
};

//Bits 7:4 HPRE: AHB prescaler
//Set and cleared by software to control the division factor of the AHB clock.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512

enum SYSCLK_Prescaler {
	SYSCLK_1,
	SYSCLK_2 = 8,
	SYSCLK_4,
	SYSCLK_8,
	SYSCLK_16,
	SYSCLK_64,
	SYSCLK_128,
	SYSCLK_256,
	SYSCLK_512
};

//Bits 1:0 SW: System clock switch
//Set and cleared by software to select SYSCLK source.
//Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of
//failure of the HSE oscillator used directly or indirectly as system clock (if the Clock Security
//System is enabled).
//00: HSI selected as system clock
//01: HSE selected as system clock
//10: PLL selected as system clock
//11: not allowed
#define RCC_SW_BIT 0

enum SYSCLK_Source {
	SYSCLK_HSI,
	SYSCLK_HSE,
	SYSCLK_PLL
};

int main(void) {
	/* Required:
	 * APB1 Bus frequency 4MHZ => HCLK/2
	 * APB2 Bus frequency 2MHZ => HCLK/4
	 * AHB frequency 8 MHZ => SYSCLK/1
	 * SysClk 8 MHZ => Use HSI which is 8Mhz RC
	 * Use only internal HSI_RC => SW=0
	 */
//	RCC_CFGR = ((HCLK_4 << RCC_PPRE2_BIT) | (HCLK_2 << RCC_PPRE1_BIT));

	/* Required:
	 * APB1 Bus frequency 16MHZ => HCLK/2
	 * APB2 Bus frequency 8MHZ => HCLK/4
	 * AHB frequency 32 MHZ => SYSCLK/1
	 * SysClk 32 MHZ
	 * Use only internal HSI_RC
	 * => Use PLL with HSI which is 8Mhz/2 * PLL = 8 = 32Mhz
	 */
	RCC_CFGR = ((HCLK_4 << RCC_PPRE2_BIT) | (HCLK_2 << RCC_PPRE1_BIT) | (PLL_8<<RCC_PLLMUL_BIT) | (SYSCLK_PLL<<RCC_SW_BIT));

	RCC_CR |= (1 << RCC_PLLON_BIT);

	// Enable IO Port A Clock
	RCC_APB2ENR |= (1 << 2);

	//Init GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	while (1) {
		GPIOA_ODR |= 1 << 13;
		for (int i = 0; i < 5000; i++)
			; // arbitrary delay
		GPIOA_ODR &= ~(1 << 13);
		for (int i = 0; i < 5000; i++)
			; // arbitrary delay
	}
}
