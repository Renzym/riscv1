/* Generated from config/memory.json. Harvard instruction/data memories. */
MEMORY
{
    rom (rx) : ORIGIN = 0, LENGTH = 2048
    ram (rw) : ORIGIN = 256, LENGTH = 1792
}
ENTRY(_start)
SECTIONS
{
    .text : { KEEP(*(.text.init)) *(.text*) } > rom
    .data ORIGIN(ram) : { __data_start = .; *(.rodata*) *(.srodata*) *(.data*) *(.sdata*) __data_end = .; } > ram
    .bss (NOLOAD) : { . = ALIGN(4); __bss_start = .; *(.bss*) *(.sbss*) *(COMMON) . = ALIGN(4); __bss_end = .; } > ram
    __stack_top = ORIGIN(ram) + LENGTH(ram);
    ASSERT(__bss_end <= __stack_top - 256, "RAM must leave at least 256 bytes for stack")
    /DISCARD/ : { *(.comment) *(.note*) *(.riscv.attributes) *(.eh_frame*) }
}
