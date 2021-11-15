/*  10-Nov-2021
    U3 L2
    Mazen Talaat
*/

ENTRY(reset)
MEMORY
{
    Mem (rwx) : o = 0x00000000 , l = 64M
}

SECTIONS
{
    . = 0x10000 ;
    .startup . :
    {
        startup.o(.text)
    }> Mem
    .text :
    {
        *(.text) *(.rodata)
    }> Mem
    .data :
    {
        *(.data)
    }> Mem
    .bss :
    {
        *(.bss) *(COMMON)
    }> Mem
    . = . + 0x1000 ;
    stack_top = . ;
}
