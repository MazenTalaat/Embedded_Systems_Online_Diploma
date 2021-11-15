/* linker_script_cortexM3.ld
 * Mazen Talaat 
 * U3 L3 
 * 14-Nov-2021 
 */

MEMORY
{
    FLASH(RX) : o = 0x08000000 , l = 128K
	SRAM(RWX) : o = 0x20000000 , l = 20K
}

SECTIONS
{
    .text :
    {
			*(.vectors*)
			*(.text*)
			*(.rodata)
    }> FLASH
	
    .data :
    {
			*(.data)
    }> FLASH
	
	.bss :
	{
			*(.bss)
	}> SRAM
}
