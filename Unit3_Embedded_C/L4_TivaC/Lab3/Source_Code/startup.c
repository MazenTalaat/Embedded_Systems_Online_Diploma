/* startup_cortexM3.c
 * Mazen Talaat 
 * U3 L4 
 * 17-Nov-2021 
 */

#include <stdint.h>

/* Functions declaration */
extern int main();
void Reset_Handler();
void Default_Handler()
{
	Reset_Handler();
}
void NMI_Handler		() __attribute__((weak, alias ("Default_Handler")));;
void H_Fault_Handler	() __attribute__((weak, alias ("Default_Handler")));;

/* Variables declaration */
static unsigned long Stack_top[256]; /*256*4 = 1024B */

extern unsigned int _S_data;
extern unsigned int _S_bss;
extern unsigned int _E_data;
extern unsigned int _E_bss;
extern unsigned int _E_text;

/* Vector table declaration */
/* Array of pointers to a function returns nothing */
void (* const g_p_fn_Vectors[])() __attribute__((section(".vectors"))) =
{
	(void (*)()) ((unsigned long)Stack_top + sizeof(Stack_top)),
	&Reset_Handler,
	&NMI_Handler,
	&H_Fault_Handler
};

/* Reset function body */
void Reset_Handler(void)
{
	unsigned int data_size = (unsigned char*)&_E_data - (unsigned char*)&_S_data;
	unsigned char* P_src = (unsigned char*)&_E_text;
	unsigned char* P_dst = (unsigned char*)&_S_data;
	int i;
	/* copying data from ROM to RAM */
	for(i=0; i<data_size; i++){
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src);
	}
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	/*Initializing .bss with zeros */
	for(i=0; i<bss_size; i++){
		*((unsigned char*)P_dst++) = (unsigned char)0;
	}
	main();
}