/* Directed RV32I regression; see REGRESSION_TESTS.md for each check. */
    .section .text.init, "ax", @progbits
    .globl _start
    .option norvc
_start:
    /* A/B: arithmetic, word memory, BEQ/JAL skips and PC-relative results. */
    addi x1, x0, 5
    addi x2, x0, 10
    add x3, x1, x2
    sw x3, 64(x0)
    lw x4, 64(x0)
    beq x4, x3, 1f
    addi x5, x0, 1
1:  auipc x6, 0
    jal x7, 1f
    addi x5, x0, 2
1:  lui x8, 0x12345
    jal x9, byte_tests
    .org 0x34
byte_tests:
    /* C: explicit byte base and signed/unsigned loads. */
    addi x11, x0, 0x50
    addi x12, x0, 0xab
    addi x13, x0, 0xcd
    sb x12, 0(x11)
    sb x13, 1(x11)
    lbu x14, 0(x11)
    lbu x15, 1(x11)
    lb x16, 1(x11)
    addi x12, x0, -128
    sb x12, 2(x11)
    lb x17, 2(x11)
    /* D: explicit halfword base, independent of JAL link register. */
    addi x18, x0, 0x60
    lui x20, 0xc
    addi x20, x20, -288
    sh x20, 0(x18)
    lh x21, 0(x18)
    lhu x22, 0(x18)
    sh x20, 2(x18)
    lh x23, 2(x18)
    /* E: signed branch decisions cannot be masked by a later assignment. */
    addi x26, x0, 0
    addi x24, x0, 1
    addi x25, x0, 2
    blt x24, x25, 1f
    jal x0, fail
1:  bge x25, x24, 1f
    jal x0, fail
1:  addi x26, x0, 100
    /* F: shift immediate and subtraction. */
    addi x27, x0, 1
    slli x27, x27, 4
    sub x28, x25, x24

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
    addi  x11, x11, 1 /* odd target: JALR must clear bit 0 */
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

    /* H, checks 21-23: all byte lanes and preservation after stores. */
    addi x11, x0, 0x50
    addi x12, x0, 0x7f
    sb x12, 3(x11)
    lbu x13, 3(x11)
    bne x13, x12, fail
    addi x10, x10, 1
    lw x13, 0(x11)
    lui x12, 0x7f80d
    addi x12, x12, -597 /* 0x7f80cdab */
    bne x13, x12, fail
    addi x10, x10, 1
    addi x11, x0, 0x60
    lhu x13, 0(x11)
    lui x12, 0xc
    addi x12, x12, -288
    bne x13, x12, fail
    addi x10, x10, 1

    /* Checks 24-27: signed extreme operands, taken and not-taken branches. */
    lui x11, 0x80000 /* INT_MIN */
    lui x12, 0x80000
    addi x12, x12, -1 /* INT_MAX */
    blt x11, x12, 1f
    jal x0, fail
1:  addi x10, x10, 1
    blt x12, x11, fail
    addi x10, x10, 1
    bge x12, x11, 1f
    jal x0, fail
1:  addi x10, x10, 1
    bge x11, x12, fail
    addi x10, x10, 1

    /* Checks 28-31: zero/31 shift amounts and rs2 high-bit masking. */
    addi x11, x0, 1
    slli x13, x11, 0
    bne x13, x11, fail
    addi x10, x10, 1
    slli x13, x11, 31
    lui x12, 0x80000
    bne x13, x12, fail
    addi x10, x10, 1
    srli x13, x12, 31
    bne x13, x11, fail
    addi x10, x10, 1
    addi x12, x0, 32
    sll x13, x11, x12 /* low five bits = 0 */
    bne x13, x11, fail
    addi x10, x10, 1

    /* Check 32: negative B-immediate and finite backward loop. */
    addi x11, x0, 3
1:  addi x11, x11, -1
    bne x11, x0, 1b
    addi x10, x10, 1
    /* Check 33: x0 must ignore writes. */
    addi x0, x0, 99
    bne x0, x11, fail /* x11 is zero */
    addi x10, x10, 1

done:
    jal x0, done

fail:
    jal x0, fail
