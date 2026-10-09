/* Data.hex preloads initialized data/rodata; startup zeroes BSS and sets stack. */
    .section .text.init, "ax", @progbits
    .globl _start
    .option norvc
_start:
    la sp, __stack_top
    la t0, __bss_start
    la t1, __bss_end
1:  bgeu t0, t1, 2f
    sw zero, 0(t0)
    addi t0, t0, 4
    jal zero, 1b
2:  call main
3:  jal zero, 3b
