/* Harvard map: instruction and data ports both use low addresses but separate RAMs. */
MEMORY
{
    rom (rx) : ORIGIN = 0x00000000, LENGTH = 2K
    ram (wx) : ORIGIN = 0x00000000, LENGTH = 2K
}

ENTRY(_start)

SECTIONS
{
    .text :
    {
        KEEP(*(.text.init))
        *(.text*)
        *(.rodata*)
    } > rom

    .data :
    {
        __data_start = .;
        *(.data*)
        *(.sdata*)
        __data_end = .;
    } > ram AT > rom

    __data_load = LOADADDR(.data);

    .bss :
    {
        __bss_start = .;
        *(.bss*)
        *(.sbss*)
        *(COMMON)
        __bss_end = .;
    } > ram

    /DISCARD/ :
    {
        *(.comment)
        *(.note*)
        *(.riscv.attributes)
    }
}
