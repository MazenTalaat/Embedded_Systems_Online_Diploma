/* linker_script_cortexM3.ld
 * Mazen Talaat 
 * U3 L4 
 * 17-Nov-2021 
 */

MEMORY
{
    FLASH(RX) : o = 0x00000000 , l = 512M
	SRAM(RWX) : o = 0x20000000 , l = 512M
}

SECTIONS
{
    .text :
    {
			*(.vectors*)
			*(.text*)
			*(.rodata)
			_E_text = . ;
    }> FLASH
	
    .data :
    {
			_S_data = . ;
			*(.data)
			. = ALIGN(4);
			_E_data = . ;
			
    }> SRAM AT > FLASH
	
	.bss :
	{
			_S_bss = . ;
			*(.bss*)
			. = ALIGN(4);
			_E_bss = . ;
	}> SRAM
}
