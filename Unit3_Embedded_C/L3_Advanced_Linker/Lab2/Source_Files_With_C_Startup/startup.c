/* startup_cortexM3.c
 * Mazen Talaat 
 * U3 L3 
 * 14-Nov-2021 
 */

#include <stdint.h>

extern unsigned int _S_data;
extern unsigned int _S_bss;
extern unsigned int _E_data;
extern unsigned int _E_bss;
extern unsigned int _E_text;

extern unsigned int _stack_top;

extern int main(void);

void Reset_Handler(void);

void Default_Handler()
{
	Reset_Handler();
}

void NMI_Handler		(void) __attribute__((weak, alias ("Default_Handler")));;
void H_Fault_Handler	(void) __attribute__((weak, alias ("Default_Handler")));;
void MM_Fault_Handler	(void) __attribute__((weak, alias ("Default_Handler")));;
void Bus_Fault_Handler	(void) __attribute__((weak, alias ("Default_Handler")));;
void Usage_Fault_Handler(void) __attribute__((weak, alias ("Default_Handler")));;

uint32_t vectors[] __attribute__((section(".vectors"))) =
{
	(uint32_t) &_stack_top,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_Fault_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault_Handler,
	(uint32_t) &Usage_Fault_Handler
};

void Reset_Handler(void)
{
	unsigned int data_size = (unsigned char*)&_E_data - (unsigned char*)&_S_data;
	unsigned char* P_src = (unsigned char*)&_E_text;
	unsigned char* P_dst = (unsigned char*)&_S_data;
	int i;
	for(i=0; i<data_size; i++){
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src);
	}
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	for(i=0; i<bss_size; i++){
		*((unsigned char*)P_dst++) = (unsigned char)0;
	}
	
	main();
}