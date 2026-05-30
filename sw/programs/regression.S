/* Golden regression image - instruction words match Program.hex (see Program.hex.txt). */
    .section .text.init, "ax", @progbits
    .globl _start
    .option norvc
_start:
    .word 0x00500093
    .word 0x00a00113
    .word 0x002081b3
    .word 0x04302023
    .word 0x04002203
    .word 0x00320463
    .word 0x00100293
    .word 0x00000317
    .word 0x008003ef
    .word 0x00200293
    .word 0x12345437
    .word 0x008004ef
    .org 0x34
    .word 0x050005b3
    .word 0x0ab00613
    .word 0x0cd00693
    .word 0x00c58023
    .word 0x00d580a3
    .word 0x0005c703
    .word 0x0015c783
    .word 0x00158803
    .word 0xf8000613
    .word 0x00c58123
    .word 0x00258883
    .word 0x06000913
    .word 0x0000ca37
    .word 0xee0a0a13
    .word 0x01449023
    .word 0x00049a83
    .word 0x0004db03
    .word 0x01449123
    .word 0x00249b83
    .word 0x00000d13
    .word 0x00100c13
    .word 0x00200c93
    .word 0x01918463
    .word 0x00100d13
    .word 0x01919463
    .word 0x00200d13
    .word 0x06400d13
    .word 0x00100d93
    .word 0x004d9d93
    .word 0x418c8e33

    /* Section G: remaining RV32I base instructions except SYSTEM/CSR traps. */
    addi x10, x0, 0

    /* BNE */
    addi x11, x0, 1
    addi x12, x0, 2
    bne  x11, x12, 1f
    jal  x0, fail
1:  addi x10, x10, 1

    /* BLTU */
    addi x11, x0, 1
    addi x12, x0, -1
    bltu x11, x12, 1f
    jal  x0, fail
1:  addi x10, x10, 1

    /* BGEU */
    bgeu x12, x11, 1f
    jal  x0, fail
1:  addi x10, x10, 1

    /* SLT / SLTU / SLTI / SLTIU */
    slt  x13, x12, x11
    addi x29, x0, 1
    bne  x13, x29, fail
    addi x10, x10, 1

    sltu x13, x12, x11
    bne  x13, x0, fail
    addi x10, x10, 1

    slti x13, x12, 0
    bne  x13, x29, fail
    addi x10, x10, 1

    sltiu x13, x11, 2
    bne  x13, x29, fail
    addi x10, x10, 1

    /* XOR / OR / AND / XORI / ORI / ANDI */
    xor  x13, x12, x11
    addi x30, x0, -2
    bne  x13, x30, fail
    addi x10, x10, 1

    or   x13, x0, x11
    bne  x13, x11, fail
    addi x10, x10, 1

    and  x13, x12, x11
    bne  x13, x11, fail
    addi x10, x10, 1

    xori x13, x11, 3
    addi x30, x0, 2
    bne  x13, x30, fail
    addi x10, x10, 1

    ori  x13, x0, 0x55
    addi x31, x0, 0x55
    bne  x13, x31, fail
    addi x10, x10, 1

    andi x13, x31, 0x0f
    addi x30, x0, 5
    bne  x13, x30, fail
    addi x10, x10, 1

    /* SLL / SRL / SRA / SRLI / SRAI */
    sll  x13, x29, x11
    addi x18, x0, 2
    bne  x13, x18, fail
    addi x10, x10, 1

    addi x19, x0, -8
    srli x13, x19, 1
    lui  x20, 0x80000
    addi x20, x20, -4
    bne  x13, x20, fail
    addi x10, x10, 1

    srai x13, x19, 1
    addi x20, x0, -4
    bne  x13, x20, fail
    addi x10, x10, 1

    srl  x13, x19, x11
    lui  x20, 0x80000
    addi x20, x20, -4
    bne  x13, x20, fail
    addi x10, x10, 1

    sra  x13, x19, x11
    addi x20, x0, -4
    bne  x13, x20, fail
    addi x10, x10, 1

    /* JALR: verify both target and link register. */
1:  auipc x11, %pcrel_hi(jalr_target)
    addi  x11, x11, %pcrel_lo(1b)
    jalr  x12, 0(x11)
jalr_link:
    jal   x0, fail
jalr_target:
2:  auipc x13, %pcrel_hi(jalr_link)
    addi  x13, x13, %pcrel_lo(2b)
    bne   x12, x13, fail
    addi  x10, x10, 1

    /* FENCE is architecturally a no-op for this simple core. */
    fence
    addi x10, x10, 1

done:
    jal x0, done

fail:
    jal x0, fail
