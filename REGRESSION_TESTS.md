# RV32I regression tests

The default regression runs [sw/programs/regression.S](sw/programs/regression.S)
on the single-cycle core and checks its final register values. The same
`Program.hex` runs in both the plain SystemVerilog bench and the UVM bench.
These are directed functional tests, not a full ISA compliance suite.

## Test flows and pass criteria

| Flow | Bench | Checks | Success indication |
|------|-------|--------|--------------------|
| Verilator in WSL | [tb_riscv.sv](tb_riscv.sv) | 21 comparisons using the shared expectation table; a mismatch calls `$fatal` | `PASS: Program.hex regression (33 self-checks, 21 registers).` |
| Vivado xsim / UVM | [tb_top_uvm.sv](uvm_tb/tb_top_uvm.sv) | [riscv_scoreboard.sv](uvm_tb/riscv_scoreboard.sv) compares the same 21 registers | `All expected registers matched`, with zero `UVM_ERROR` and `UVM_FATAL` reports |

Both benches hold reset for two rising clock edges, then run for 500 cycles by
default. The program ends in a loop so its results remain available for checking.
The UVM bench signals `stimulus_done`; its base test waits for this signal before
invoking the scoreboard. UVM can change the execution budget with the simulator
plusarg `+RUN_CYCLES=<count>`; the plain bench uses `DEFAULT_RUN_CYCLES` from
the shared package. Reset is deasserted on a falling edge and results are
sampled after register updates settle.

The benches observe the DUT register file directly. They do not compare every
retired instruction against a reference model or check the entire memory image.

## What the program exercises

All executable instructions use assembly mnemonics. This guide consolidates
the former Program.hex.txt notes. S-type store immediates are split between
instruction bits [31:25] and [11:7]; the assembler handles that encoding.

| Section | Behavior exercised | Result checked |
|---------|--------------------|----------------|
| A, PC `0x00`–`0x28` | `ADDI`, `ADD`, `SW`/`LW` at byte address `0x40`, `BEQ` and `JAL` skips, `AUIPC`, `LUI` | Arithmetic results, loaded word, skipped writes to x5, PC-relative and jump-link values |
| B, PC `0x2c` | `JAL` skips to `0x34` and writes its return address | x9 = `0x30` |
| C, PC `0x34` onward | `SB` writes adjacent byte lanes; `LBU` and `LB` read unsigned and signed values | `0xAB`, `0xCD`, signed `0xCD`, and signed `0x80` |
| D | `SH` writes the low and high halfwords at base `0x60`; `LH` and `LHU` read `0xBEE0` | Signed and unsigned extension, including a high-halfword load |
| E | Directed `BLT` and `BGE` branches with explicit failure jumps | x26 reaches 100 only after both expected decisions |
| F | `SLLI` and `SUB` | x27 = 16; x28 = 1 |
| G, PC `0xac` onward | 20 additional checks for branches, comparisons, logic, shifts, `JALR`, and execution past `FENCE` | x10 counts successful checks and must reach 20 |
| H, PC `0x1f8` onward | 13 checks for store preservation, signed boundaries, shift limits, backward branches and x0 | x10 must finish at 33 |

The word-store encoding at PC `0x00c` must be `04302023` (`sw x3, 64(x0)`),
matching the subsequent load from byte address `0x40`.

### Sections G/H pass counter

Each successful check increments x10. A failed comparison branches to the
`fail` loop, preserving the number of checks completed. The expected sequence is:

| Check | Instruction | Behavior |
|-------|-------------|----------|
| 1 | `BNE` | Branches when 1 and 2 differ |
| 2 | `BLTU` | Treats 1 as less than unsigned `0xFFFFFFFF` |
| 3 | `BGEU` | Treats unsigned `0xFFFFFFFF` as greater than or equal to 1 |
| 4 | `SLT` | Signed -1 is less than 1 |
| 5 | `SLTU` | Unsigned `0xFFFFFFFF` is not less than 1 |
| 6 | `SLTI` | Signed -1 is less than immediate 0 |
| 7 | `SLTIU` | Unsigned 1 is less than immediate 2 |
| 8 | `XOR` | -1 XOR 1 produces -2 |
| 9 | `OR` | 0 OR 1 produces 1 |
| 10 | `AND` | -1 AND 1 produces 1 |
| 11 | `XORI` | 1 XOR 3 produces 2 |
| 12 | `ORI` | 0 OR `0x55` produces `0x55` |
| 13 | `ANDI` | `0x55` AND `0x0F` produces 5 |
| 14 | `SLL` | 1 shifted left by 1 produces 2 |
| 15 | `SRLI` | Logical right shift of -8 by 1 produces `0x7FFFFFFC` |
| 16 | `SRAI` | Arithmetic right shift of -8 by 1 produces -4 |
| 17 | `SRL` | Register-controlled logical right shift produces `0x7FFFFFFC` |
| 18 | `SRA` | Register-controlled arithmetic right shift produces -4 |
| 19 | `JALR` | Reaches the target and writes the correct return address |
| 20 | `FENCE` | Execution continues past the instruction |
| 21 | `SB` / `LBU` | Writes and reads byte lane 3 |
| 22 | `LW` | Byte stores preserve the final word `0x7F80CDAB` |
| 23 | `LHU` | High-halfword store preserved the low halfword |
| 24 | `BLT` | Taken for INT_MIN < INT_MAX |
| 25 | `BLT` | Not taken for INT_MAX < INT_MIN |
| 26 | `BGE` | Taken for INT_MAX >= INT_MIN |
| 27 | `BGE` | Not taken for INT_MIN >= INT_MAX |
| 28 | `SLLI` | Shift by 0 preserves 1 |
| 29 | `SLLI` | Shift by 31 produces `0x80000000` |
| 30 | `SRLI` | Shift `0x80000000` by 31 produces 1 |
| 31 | `SLL` | Register amount 32 is masked to 0 |
| 32 | `BNE` | Backward loop decrements 3 to 0 |
| 33 | x0 | Attempted write is ignored |

For example, x10 = 14 suggests execution stopped during check 15 (`SRLI`),
assuming the counter and control flow work correctly. A low count can also
result from insufficient simulation cycles or an earlier execution fault.

`FENCE` acts as a no-op in this simple core; this check does not validate ordering
against concurrent memory agents.

## Reading the assembly and following the hardware

Registers x0 through x31 hold 32-bit values. Reading x0 always returns zero;
writes to x0 are discarded. Register names do not imply signedness: the
instruction determines whether `0xFFFFFFFF` means signed -1 or unsigned
4,294,967,295. Arithmetic wraps to 32 bits.

`addi rd, rs1, imm` writes `rs1 + sign_extend(imm)` to `rd`. Its immediate is
a signed 12-bit number (-2048 through 2047). `add rd, rs1, rs2` uses two
register operands. `sw rs2, offset(rs1)` stores a register at byte address
`rs1 + offset`; `lw rd, offset(rs1)` loads from that address. A store's first
operand is the data source, not a destination register.

Each instruction here occupies four bytes. Normally PC advances by four.
A taken branch adds its signed offset to the address of the branch itself.
`jal` and `jalr` also save the old PC + 4 in their destination register.
Labels name addresses; `1f` means the next label `1:`, and `1b` means the
previous label `1:`. Local numeric labels can be reused.

For a normal arithmetic instruction, follow this path in
[rtl/Riscv.sv](rtl/Riscv.sv): instruction fetch, register reads, `ImmExt` and
operand selection, [Alu.sv](rtl/Alu.sv), `RegWb`, then register write on the
clock edge. Loads select `LoadWbData` instead of the ALU result; stores assert
`DmemWrEn` and suppress register writeback. Branches update `PcNxt` through
`BrTaken` and `BrPcSel` and also suppress register writeback.

Program and data RAM are separate. Storing to data byte address `0x40` does
not overwrite the instruction at PC `0x40`. Both RAMs use word indices:
byte address / 4 selects the word, and data address bits [1:0] select a byte
within that word. `Program.hex` line number is PC / 4 + 1.

The snippets below follow the source and generated image. Symbolic names such
as `at_1c` make branch targets readable. PCs can change as instructions are added;
`cd sw && make dump` shows the current disassembly.

### A: arithmetic, word memory, branch, and PC writeback

```asm
# PC     instruction             expected effect
# 0x00
addi x1, x0, 5                   # x1 = 5
addi x2, x0, 10                  # x2 = 10
add  x3, x1, x2                  # x3 = 15
sw   x3, 64(x0)                  # data word at 0x40 = 15
lw   x4, 64(x0)                  # x4 = 15
beq  x4, x3, at_1c               # PC 0x14 + 8 = 0x1c
addi x5, x0, 1                   # PC 0x18: must be skipped
at_1c:
auipc x6, 0                      # x6 = current PC 0x1c = 28
jal   x7, at_28                  # PC 0x20: x7 = 0x24 = 36
addi  x5, x0, 2                  # PC 0x24: must be skipped
at_28:
lui   x8, 0x12345                # x8 = 0x12345000
```

The first three instructions exercise immediate selection, register read
addresses, addition, destination decoding, and ALU writeback. The following
store uses effective byte address 64, RAM index 16, and write mask `1111`.
The load reads that word back through the memory writeback path. A broken
store address, write enable, load address, or writeback mux can make x4 differ
from x3.

`BEQ` compares register values, while its immediate supplies the PC offset.
Correct operand selection must therefore keep the comparison operands separate
from the branch-target calculation. Both skips protect x5, which starts at zero
after reset. A failed skip leaves x5 = 1 or 2 for the bench to detect.

`AUIPC` adds its upper immediate shifted left by 12 to the current instruction's
PC, not PC + 4. With immediate zero, x6 directly checks the PC operand path.
`JAL` checks two simultaneous effects: target PC selection and PC + 4 writeback.
`LUI` places its 20-bit immediate in bits [31:12], clearing the low 12 bits;
it checks immediate construction and immediate writeback.

### B: another jump and a deliberately skipped hole

```asm
# PC 0x2c
jal x9, at_34                    # x9 = 0x30; target = 0x34
# PC 0x30 contains 00000000 padding, not a valid RV32I instruction
at_34:
# Section C starts here
```

The source's `.org 0x34` inserts padding to place the next instruction at that
address. The jump must skip the padding. x9 retains the link value 48. Halfword tests use an independent base register.

### C: byte stores, lane selection, and sign extension

The byte-test base is explicitly initialized to data byte address `0x50`.

```asm
addi x11, x0, 0x50               # byte-test base = 80
addi x12, x0, 0xab               # x12 = 171
addi x13, x0, 0xcd               # x13 = 205
sb   x12, 0(x11)                 # byte at 0x50 = AB
sb   x13, 1(x11)                 # byte at 0x51 = CD; preserve byte 0x50
lbu  x14, 0(x11)                 # x14 = 000000AB
lbu  x15, 1(x11)                 # x15 = 000000CD
lb   x16, 1(x11)                 # x16 = FFFFFFCD (-51)
addi x12, x0, -128               # x12 = FFFFFF80
sb   x12, 2(x11)                 # store only low byte 80
lb   x17, 2(x11)                 # x17 = FFFFFF80 (-128)
```

Little-endian RAM places the lowest-addressed byte in bits [7:0]. Starting
from zero-filled RAM, word index 20 evolves as follows:

| Store | Write mask `DmemWrEn[3:0]` | RAM word after the edge |
|-------|---------------------------|-------------------------|
| `sb x12, 0(x11)` | `0001` | `0x000000AB` |
| `sb x13, 1(x11)` | `0010` | `0x0000CDAB` |
| `sb x12, 2(x11)` | `0100` | `0x0080CDAB` |

The RTL replicates the source byte across all four lanes in `DmemWrData`;
the mask decides which lane is actually written. Reading byte 0 after writing
byte 1 checks that an adjacent store preserved earlier data.

`LBU` fills the upper 24 bits with zero. `LB` copies bit 7 of the selected
byte into those bits. Thus the same stored `CD` yields either `000000CD` or
`FFFFFFCD`. The -128 case exercises the byte's sign bit with all other bits
clear. Inspect `DmemByteOff`, `DmemWrData`, `DmemWrEn`, and `LoadWbData` when
debugging these checks. Section H checks lane 3 and the final full word.

### D: halfword placement and signed immediates

```asm
addi x18, x0, 0x60               # halfword-test base = 96
lui  x20, 0xc                    # x20 = 0000C000
addi x20, x20, -288              # x20 = 0000BEE0
sh   x20, 0(x18)                 # base 0x60, independent of JAL link
lh   x21, 0(x18)                 # x21 = FFFFBEE0
lhu  x22, 0(x18)                 # x22 = 0000BEE0
sh   x20, 2(x18)                 # upper half of the same RAM word
lh   x23, 2(x18)                 # x23 = FFFFBEE0
```

The raw ADDI immediate bits are `0xEE0`. As a signed 12-bit number this is
`0xEE0 - 0x1000 = -288`. Therefore `0xC000 - 0x120 = 0xBEE0`.
Using `LUI 0xb` followed by that ADDI would produce `0xAEE0`, not `0xBEE0`.
This is why constructing a constant requires accounting for sign extension.

The accesses are at bytes `0x60` and `0x62`, RAM word index 24. The first
store uses mask `0011` and produces `0000BEE0`; the second uses mask `1100`
and produces `BEE0BEE0`. `LH` extends selected bit 15, which is 1 in `BEE0`;
`LHU` zero-extends. For the high halfword, the RTL selects bits [31:16]
before extending. These checks exercise halfword masks, load selection,
sign extension, and memory writeback. Section H reloads the low halfword to check preservation after the high-halfword store.

### E: signed branches with observable outcomes

```asm
addi x26, x0, 0
addi x24, x0, 1
addi x25, x0, 2
blt x24, x25, 1f                 # 1 < 2: must be taken
jal x0, fail                     # wrong decision cannot reach x26 = 100
1: bge x25, x24, 1f              # 2 >= 1: must be taken
jal x0, fail
1: addi x26, x0, 100
```

Both branches compare register operands as signed values and use a separate
PC-relative target. A wrong decision enters the failure loop immediately.
x26 = 100 therefore records completion of both decisions. Section H adds
negative boundary operands and not-taken cases to distinguish signed from
unsigned comparison and catch subtraction-overflow mistakes.

### F: immediate shift and subtraction

```asm
addi x27, x0, 1
slli x27, x27, 4                 # 00000001 << 4 = 00000010 (16)
sub  x28, x25, x24               # 2 - 1 = 1
```

`SLLI` uses the instruction's shift amount rather than a second register's
value. The result checks the shifter and writeback to the same source register.
`SUB` shares the register-register encoding shape with ADD but uses a different
`funct7`; in this ALU it inverts operand 2 and adds the carry-in of 1 to implement
two's-complement subtraction. x24 and x25 retain the values established in E.

### G: self-checking instruction tests

Section G begins with `addi x10, x0, 0`. For most tests, x13 holds a temporary
result and a `bne` compares it with a known expected value. Only a matching
result reaches `addi x10, x10, 1`. Temporary registers are reused, so final
x13 alone cannot tell you whether all earlier operations passed.

#### Checks 1-3: conditional unsigned control flow

```asm
addi x11, x0, 1
addi x12, x0, 2
bne  x11, x12, 1f
jal  x0, fail
1: addi x10, x10, 1             # check 1 passed

addi x11, x0, 1
addi x12, x0, -1                # bits FFFFFFFF
bltu x11, x12, 1f
jal  x0, fail
1: addi x10, x10, 1             # check 2 passed

bgeu x12, x11, 1f
jal  x0, fail
1: addi x10, x10, 1             # check 3 passed
```

Each branch must skip an unconditional jump to `fail`. BLTU and BGEU interpret
`FFFFFFFF` as a large positive number. A signed comparison would make -1
less than 1 and reverse these outcomes. In `Alu.sv`, inspect the unsigned
comparison and `BrTaken`; in `Riscv.sv`, inspect PC target selection.
After these checks, x11 = 1 and x12 = `FFFFFFFF`; later tests reuse them.

#### Checks 4-7: signed and unsigned less-than results

```asm
slt  x13, x12, x11              # signed -1 < 1: x13 = 1
addi x29, x0, 1
bne  x13, x29, fail
addi x10, x10, 1                # check 4

sltu x13, x12, x11              # unsigned FFFFFFFF < 1: x13 = 0
bne  x13, x0, fail
addi x10, x10, 1                # check 5

slti x13, x12, 0                # signed -1 < 0: x13 = 1
bne  x13, x29, fail
addi x10, x10, 1                # check 6

sltiu x13, x11, 2               # unsigned 1 < 2: x13 = 1
bne   x13, x29, fail
addi  x10, x10, 1               # check 7
```

These instructions write a complete 32-bit 0 or 1; they do not change PC
directly. The ALU comparison result must be zero-filled above bit 0.
The immediate variants also exercise `Op2Sel` and immediate decoding.
SLTIU still sign-extends its immediate before comparing it as unsigned;
this test uses positive 2, so it does not test a negative SLTIU immediate.
x29 remains 1 for the later shift test.

#### Checks 8-10: register logic

```asm
xor  x13, x12, x11              # FFFFFFFF XOR 00000001 = FFFFFFFE
addi x30, x0, -2
bne  x13, x30, fail
addi x10, x10, 1                # check 8

or   x13, x0, x11               # 0 OR 1 = 1
bne  x13, x11, fail
addi x10, x10, 1                # check 9

and  x13, x12, x11              # FFFFFFFF AND 1 = 1
bne  x13, x11, fail
addi x10, x10, 1                # check 10
```

Logic is bitwise: XOR toggles bits where operands differ, OR sets bits present
in either operand, and AND keeps only bits present in both. The same operand
pair distinguishes XOR from AND. These tests exercise register operand reads,
`funct3` selection among `XorOut`, `OrOut`, and `AndOut`, and ALU writeback.

#### Checks 11-13: immediate logic

```asm
xori x13, x11, 3                # 01 XOR 11 = 10 (2)
addi x30, x0, 2
bne  x13, x30, fail
addi x10, x10, 1                # check 11

ori  x13, x0, 0x55              # x13 = 55
addi x31, x0, 0x55
bne  x13, x31, fail
addi x10, x10, 1                # check 12

andi x13, x31, 0x0f             # 01010101 AND 00001111 = 00000101
addi x30, x0, 5
bne  x13, x30, fail
addi x10, x10, 1                # check 13
```

These use the same logic units as the register variants, but select the
sign-extended immediate for operand 2. All chosen immediates are positive;
negative logical immediates are not covered. Check 13 verifies masking of
the high nibble while preserving selected low bits.

#### Check 14: register-controlled left shift

```asm
sll  x13, x29, x11              # x29 = 1, x11 = 1: result 2
addi x18, x0, 2
bne  x13, x18, fail
addi x10, x10, 1
```

SLL obtains its amount from the low five bits of rs2, unlike SLLI in F.
This checks the register operand path into `Shamt` and `ShiftOut`. The small
amount does not test whether high bits of the shift register are ignored.

#### Checks 15-18: logical versus arithmetic right shift

```asm
addi x19, x0, -8                # FFFFFFF8
srli x13, x19, 1                # 7FFFFFFC: fill with zero
lui  x20, 0x80000               # 80000000
addi x20, x20, -4               # 7FFFFFFC: expected result
bne  x13, x20, fail
addi x10, x10, 1                # check 15

srai x13, x19, 1                # FFFFFFFC: fill with sign bit 1
addi x20, x0, -4
bne  x13, x20, fail
addi x10, x10, 1                # check 16

srl  x13, x19, x11              # same logical shift, amount from x11 = 1
lui  x20, 0x80000
addi x20, x20, -4
bne  x13, x20, fail
addi x10, x10, 1                # check 17

sra  x13, x19, x11              # same arithmetic shift, register amount
addi x20, x0, -4
bne  x13, x20, fail
addi x10, x10, 1                # check 18
```

With a negative source, the incoming high bit distinguishes logical and
arithmetic shifts. `FFFFFFF8 >> 1` gives `7FFFFFFC`, while signed arithmetic
shift gives `FFFFFFFC`, representing -4. In SystemVerilog the arithmetic
operation must use a signed left operand; this RTL uses `SignedAluOp1 >>> Shamt`.
Instruction bit 30 selects the arithmetic variant. Testing both register and
immediate forms checks that both decode paths reach the correct shift behavior.

#### Check 19: indirect jump target and return address

```asm
1: auipc x11, %pcrel_hi(jalr_target)
   addi  x11, x11, %pcrel_lo(1b)
   addi  x11, x11, 1             # deliberately odd register target
   jalr  x12, 0(x11)
jalr_link:
   jal   x0, fail
jalr_target:
2: auipc x13, %pcrel_hi(jalr_link)
   addi  x13, x13, %pcrel_lo(2b)
   bne   x12, x13, fail
   addi  x10, x10, 1
```

`%pcrel_hi` and `%pcrel_lo` request linker relocations that split a PC-relative
address into an upper immediate and signed low immediate. The low relocation
names the label on the matching AUIPC, so both parts refer to the same PC.
For the current image, the resolved instructions and addresses are:

```asm
# PC 0x1cc
auipc x11, 0                    # x11 = 1cc
addi  x11, x11, 20              # x11 = 1e0 (target)
addi  x11, x11, 1               # x11 = 1e1: low bit deliberately set
jalr  x12, 0(x11)               # PC 1d8: link = 1dc, target = 1e1 & ~1 = 1e0
# PC 0x1dc: jal x0, fail is skipped
# PC 0x1e0
auipc x13, 0                    # x13 = 1e0
addi  x13, x13, -4              # x13 = 1dc (expected link)
bne   x12, x13, fail
addi  x10, x10, 1
```

Unlike JAL's PC-relative target, JALR computes its target from a register plus
a signed immediate. It still writes PC + 4. Landing at `jalr_link` instead
of the target enters `fail`; reaching the target with an incorrect link also
enters `fail` through BNE. This exercises the ALU target path, `JalPcSel`, and
the PC writeback path. RV32I requires JALR to clear target bit 0; this test
deliberately supplies an odd address and verifies that clearing. `JumpTarget`
clears bit 0 before `PcNxt` selects the JALR target. Bit 1 must still be zero
because this core does not support compressed instructions.

#### Check 20: FENCE

```asm
fence                           # PC 1f0
addi x10, x10, 1                # x10 reaches 20; continue into H
```

The simple memory system has no competing agents or outstanding accesses.
This checks execution past FENCE, not general ordering. FENCE has no register
or memory writeback side effects in this core.

### H: preservation, boundaries, loops, and x0 (checks 21-33)

#### Checks 21-23: finish byte lanes and verify store preservation

```asm
addi x11, x0, 0x50
addi x12, x0, 0x7f
sb x12, 3(x11)                  # final byte lane, mask 1000
lbu x13, 3(x11)
bne x13, x12, fail
addi x10, x10, 1                # check 21
lw x13, 0(x11)                  # byte sequence AB CD 80 7F
lui x12, 0x7f80d
addi x12, x12, -597             # 7F80D000 - 255 = 7F80CDAB (hex)
bne x13, x12, fail
addi x10, x10, 1                # check 22
addi x11, x0, 0x60
lhu x13, 0(x11)                 # reload low halfword after high-halfword store
lui x12, 0xc
addi x12, x12, -288             # 0000BEE0
bne x13, x12, fail
addi x10, x10, 1                # check 23
```

The full-word comparison proves earlier byte stores survived all later lane
writes. The halfword reload checks the same preservation property for mask
1100. The constant uses an upper value rounded up because its low 12-bit
immediate is negative: -597 decimal is -0x255.

#### Checks 24-27: signed comparison extremes

```asm
lui x11, 0x80000                # INT_MIN: 80000000 (-2147483648)
lui x12, 0x80000
addi x12, x12, -1               # INT_MAX: 7FFFFFFF (2147483647)
blt x11, x12, 1f
jal x0, fail
1: addi x10, x10, 1             # 24: taken BLT
blt x12, x11, fail
addi x10, x10, 1                # 25: not-taken BLT
bge x12, x11, 1f
jal x0, fail
1: addi x10, x10, 1             # 26: taken BGE
bge x11, x12, fail
addi x10, x10, 1                # 27: not-taken BGE
```

These operands have opposite sign bits. Subtracting them can overflow a
32-bit signed result, so using only the subtraction sign bit is not a correct
signed less-than implementation. `Alu.sv` compares `$signed` operands directly.
Both taken and not-taken cases must work before the counter reaches 27.

#### Checks 28-31: shift boundary amounts

```asm
addi x11, x0, 1
slli x13, x11, 0
bne x13, x11, fail
addi x10, x10, 1                # 28: shifting by zero preserves input
slli x13, x11, 31
lui x12, 0x80000
bne x13, x12, fail
addi x10, x10, 1                # 29: bit 0 moves to bit 31
srli x13, x12, 31
bne x13, x11, fail
addi x10, x10, 1                # 30: bit 31 moves to bit 0
addi x12, x0, 32
sll x13, x11, x12
bne x13, x11, fail
addi x10, x10, 1                # 31: rs2[4:0] = 0, not a shift by 32
```

RV32 shifts use a five-bit amount. The register amount 32 has bit 5 set,
which must be ignored. These cases check the ends of the shifter range and
the extraction of the register-controlled shift amount.

#### Checks 32-33: backward branch and the zero register

```asm
addi x11, x0, 3
1: addi x11, x11, -1
bne x11, x0, 1b                 # negative offset: loop while count != 0
addi x10, x10, 1                # 32
addi x0, x0, 99                 # attempted write must be discarded
bne x0, x11, fail               # x11 is zero, so this must not branch
addi x10, x10, 1                # 33
```

The loop executes three decrements and checks both taken and not-taken BNE
with a negative B-type immediate. This exercises sign extension and PC-relative
addition in the backward direction. x0 must remain zero after the write attempt;
its register-file read behavior and final bench probe are both checked.

```asm
done: jal x0, done              # PC 2c8: success loop
fail: jal x0, fail              # PC 2cc: failure loop
```

Both loops discard the link and use a zero offset. The benches stop simulation
after the cycle budget. PC 0x2c8 with x10 = 33 indicates success; PC 0x2cc
indicates the failure path. Since early sections precede counter initialization,
x10 alone does not identify every early failure.

### How the bench turns results into a verdict

The plain bench iterates the shared table:

```systemverilog
foreach (REGRESSION_EXPECTS[i]) begin
    if (dut.RegfileInst.Regs[REGRESSION_EXPECTS[i].addr] !== REGRESSION_EXPECTS[i].value)
        $fatal(1, "Register mismatch"); // actual bench also prints register and values
end
```

The `!==` case-inequality operator also treats X or Z bits as mismatches. The
plain bench stops at the first failing assertion. UVM obtains register values
through `riscv_if`, compares the expected map, reports mismatches, and issues
a fatal report if its scoreboard error count is nonzero. Its base test waits
`#1step` after `stimulus_done` before checking. These checks validate stored
results, not the precise sequence of all earlier PC values or memory writes.
Use the assembly PCs and signals above to inspect intermediate behavior in a
waveform when the final result alone cannot identify the cause.

## Expected final registers

These values are defined once in [riscv_pkg.sv](uvm_tb/riscv_pkg.sv) and used
by both benches. The scoreboard preserves four-state values, so X/Z cannot
be converted to zero before comparison.
Registers omitted from the table are not checked by the default benches.

| Register | Expected value | Purpose |
|----------|----------------|---------|
| x0 | 0 | Architectural zero register |
| x1 | 5 | First arithmetic operand |
| x2 | 10 | Second arithmetic operand |
| x3 | 15 | Addition result |
| x4 | 15 | Word loaded after store |
| x5 | 0 | Writes skipped by branch and jump |
| x6 | 28 | `AUIPC` result |
| x7 | 36 | First `JAL` return address |
| x8 | `0x12345000` | `LUI` result |
| x9 | 48 | Second `JAL` return address |
| x10 | 33 | Sections G/H completed-check count |
| x14 | `0x000000AB` | Unsigned byte load |
| x15 | `0x000000CD` | Unsigned byte load from next lane |
| x16 | `0xFFFFFFCD` | Signed byte load |
| x17 | `0xFFFFFF80` | Signed byte load of -128 |
| x21 | `0xFFFFBEE0` | Signed low-halfword load |
| x22 | `0x0000BEE0` | Unsigned halfword load |
| x23 | `0xFFFFBEE0` | Signed high-halfword load |
| x26 | 100 | Both Section E signed branches passed |
| x27 | 16 | Immediate left shift |
| x28 | 1 | Subtraction result |

## Running the regression

Rebuild and verify the default image in WSL, starting at the repo root:

```bash
cd sw
make install-hex
python3 scripts/verify_hex_format.py
cd ..
bash sim_wsl.sh
```

The verifier checks plain eight-digit hex words in `Program.hex` and `Data.hex`,
and compares `Program.hex` with `sw/build/regression.hex` when that build output
exists. Run it before `make clean` to retain that comparison.

For UVM, run from the repo root on Windows:

```cmd
run_uvm.cmd
```

The launcher uses Vivado 2021.2; see [README.md](README.md#run-uvm-on-windows)
for the installation path and direct invocation. The Tcl script copies both
memory images into xsim's working directory before simulation.

If a test fails, check that the default regression image is installed, inspect
the reported register mismatch and x10 count, then use `make dump` in `sw/` to
inspect the compiled instructions. Installing `c_smoke` or another image changes
the executed program but does not change the benches' expected results.

## Extending coverage

Add directed cases to `sw/programs/regression.S`, rebuild `Program.hex`, and
update the shared expectation table when results change. If Section G gains
checks, update the expected x10 count and the sequence above. Increase the cycle
budget in both flows if the program needs more time.

The regression exercises the implemented arithmetic, logic, shift, branch,
jump, load/store, upper-immediate, and `FENCE` instruction groups. It excludes
`ECALL`, `EBREAK`, and CSR behavior because the core has no exception/CSR
subsystem. It does not exhaustively cover operand combinations or every
alignment case. Additional directed tests cover selected invalid encodings,
alignment errors, memory boundaries, and reset during execution.
The core reports unsupported instructions, misaligned accesses, and out-of-range
addresses as faults: it halts and suppresses writes instead of implementing
architectural traps. Dedicated directed tests verify these defined limitations.

## Additional executable checks

From the repo root in WSL:

```bash
bash sim_wsl.sh tb_core_checks
bash sim_wsl.sh tb_c_smoke
bash sim_wsl.sh tb_fault_report
python3 sw/scripts/test_memory_tools.py
```

`tb_core_checks` uses 16-word memories and supplies instructions directly. It
checks invalid opcodes/function fields, unsupported MUL/ECALL, misaligned loads,
stores and branch/jump targets, the first invalid RAM address, the last valid
word of each memory, odd JALR target masking, and reset during a running loop.
For rejected instructions it checks Fault, stationary PC, unchanged registers,
and unchanged data RAM. REPORT_FAULTS is disabled only in this bench so it can
inspect faults; normal simulation terminates with a diagnostic.

`tb_fault_report` deliberately executes an invalid instruction with normal
reporting enabled. Its runner requires the core diagnostic and a nonzero
simulation exit status; an unrelated build/runtime failure is not a pass.
The xsim directed runner also executes this expected-failure test.

The xsim directed runner tests the scoreboard separately with X and Z register
values against an expected zero, then with valid zero. This verifies four-state
comparison in a simulator which preserves unknown values.

`tb_c_smoke` builds its own images without replacing the default root images.
The C program reads initialized data and constants from data RAM, calls a
function that uses a volatile stack local, checks a BSS variable, and writes
12345678 to data address 0x40. The bench poisons zero-filled data RAM above
0x100 before reset to ensure startup really clears BSS. crt0 sets the stack,
zeroes BSS, calls main, and loops when main returns.

The Python checks validate little-endian conversion, zero words, partial-word
padding, base padding, invalid bases, plain hex formatting, capacity rejection,
and generated configuration consistency. Vivado launch scripts require a pass
marker and reject error/fatal reports; elapsed simulation time alone is not success.

## Memory configuration and C runtime

### From source code to RAM contents

The compiler/assembler translates source into instructions and data. The linker
assigns addresses, joins sections, and resolves references such as a jump to
`main` or a load from a global variable. The linker script is the address-layout
specification: for a hardware engineer, it is the software counterpart of the
memory map and reset-vector design.

The linked ELF file contains section contents, addresses, and symbols. ELF is
not the file format consumed by the RTL. The build extracts separate raw
binaries, then converts them to the two RAM initialization files:

```text
assembly program (_start), or C program (main) + crt0.S
                       |
             GCC / assembler / linker
                       |  -T linker.ld selects the memory map
                 build/<name>.elf
                       |
          +------------+----------------+
          |                             |
  objcopy -j .text              objcopy -j .data
  <name>.bin                    <name>.data.bin
          |                             |
   little-endian words          leading zeros to data_origin,
   padded to program RAM        then words padded to data RAM
          |                             |
  <name>.hex                    <name>.data.hex
          |      make install-hex        |
     Program.hex                    Data.hex
          |                             |
    instruction RAM                  data RAM
```

For example, instruction word `0x00500093` occupies binary bytes `93 00 50 00`
and becomes the text line `00500093`. Hex lines hold **words**, but ELF addresses,
linker sizes, PC values, and load/store addresses are in **bytes**. A data word
at byte address `0x100` belongs at RAM index 64, or line 65 of `Data.hex`.
The leading zero words preserve that placement; a raw `.data` binary alone
does not tell `$readmemh` where to begin loading it.

### Reading the MEMORY block

The default generated [sw/linker.ld](sw/linker.ld) begins with:

```ld
MEMORY
{
    rom (rx) : ORIGIN = 0,   LENGTH = 2048
    ram (rw) : ORIGIN = 256, LENGTH = 1792
}
ENTRY(_start)
```

`ORIGIN` is the first byte address available to a region; `LENGTH` is its size
in bytes. `rom` and `ram` are linker region names, not RTL instance names.
The `r`, `w`, and `x` attributes describe intended read/write/execute use to the
linker; they do not create hardware access protection or change the RAM circuit.
The instruction RAM is called `rom` here because software only fetches from it.

| Physical memory | Addresses | Linker allocation |
|-----------------|-----------|-------------------|
| Instruction RAM | `0x000`–`0x7FF` | 2048 bytes for code |
| Data RAM, scratch | `0x000`–`0x0FF` | Not allocated to static C sections; used for directed tests/signatures |
| Data RAM, static data and stack | `0x100`–`0x7FF` | 1792 bytes shared by initialized data, BSS, free space, and stack |

The `ram` region starts at 256 because the linker intentionally leaves low
data RAM available for tests. It does not mean the physical data RAM starts at
256 or has only 1792 bytes. Instruction and data addresses overlap because
they reach separate memories: code at PC `0x100` and a variable at data address
`0x100` can coexist.

`ENTRY(_start)` sets the ELF entry symbol. It does **not** program the RTL reset
PC. This core resets PC to zero, so `_start` must also reside at zero. A simulator
loading plain hex does not read the ELF entry field. Moving the entry point
requires coordinated RTL reset-PC and image-layout changes.

### Reading the SECTIONS block

An input section is a group emitted by a compiler or assembler. The linker
collects input sections into output sections according to this block:

```ld
.text : { KEEP(*(.text.init)) *(.text*) } > rom
.data ORIGIN(ram) : {
    __data_start = .;
    *(.rodata*) *(.srodata*) *(.data*) *(.sdata*)
    __data_end = .;
} > ram
.bss (NOLOAD) : {
    . = ALIGN(4);
    __bss_start = .;
    *(.bss*) *(.sbss*) *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
} > ram
```

`> rom` and `> ram` select the destination region. `*` matches input files or
section-name suffixes; for example, `*(.text*)` gathers `.text` and `.text.foo`.
The dot `.` is the current output address, called the location counter.
`__data_start = .` defines an address symbol; it does not emit a data word or
allocate storage for a variable with that name.

| Output section | Typical contents | How it reaches hardware |
|----------------|------------------|-------------------------|
| `.text` | Startup and function instructions | Extracted into `Program.hex` |
| `.data` | Initialized variables and read-only constants gathered from `.rodata` and other input sections | Extracted into `Data.hex` |
| `.bss` | Uninitialized or zero-initialized static/global variables | Address space allocated by the linker; startup writes zeros |

`KEEP(*(.text.init))` retains the startup section even with `--gc-sections`,
which can discard unreachable sections. It also places startup before the
remaining code. Both `crt0.S` and the assembly regression put `_start` in
`.text.init`. The explicit `.data ORIGIN(ram)` fixes the output section's start
address so binary-to-hex base padding agrees with the linker, even when an
input object needs extra alignment inside that section.

Read-only constants belong in data RAM in this design. A compiler implements
an array lookup with a load instruction, and this core's load port cannot read
instruction RAM. Putting `.rodata` in instruction ROM would therefore produce
the wrong value for an ordinary C load. The current map makes constants
readable through the data port; it does not enforce their read-only status.

`NOLOAD` reserves BSS addresses without providing initialized bytes in the RAM
image. `ALIGN(4)` rounds boundaries up to a multiple of four, allowing startup
to clear BSS using word stores. Startup clears the half-open interval
`[__bss_start, __bss_end)`: the end symbol points just beyond the final byte.

The rest of the script defines the stack boundary and checks available space:

```ld
__stack_top = ORIGIN(ram) + LENGTH(ram);  /* default: 0x800 */
ASSERT(__bss_end <= __stack_top - 256,
       "RAM must leave at least 256 bytes for stack")
```

`0x800` is one byte beyond data RAM, which is appropriate for an initially empty
downward-growing stack. A function decrements `sp` before storing its stack
frame; it must not store directly to the initial `sp`. The assertion prevents
static allocations from consuming the last 256 bytes, but it neither allocates
a stack section nor checks runtime stack depth. Hardware still permits static
data and stack to collide if software uses too much stack.

The `/DISCARD/` block removes metadata and unwind sections that this minimal
runtime does not use. Adding a new output section also requires deciding
whether startup initializes it and whether the hex extraction includes it;
the Makefile currently extracts only `.text` and `.data`.

### What startup supplies for C

There is no operating system or executable loader to prepare memory and call
`main`. [sw/crt0.S](sw/crt0.S) supplies that preparation:

```asm
_start:
    la sp, __stack_top          # load linker-defined stack address
    la t0, __bss_start
    la t1, __bss_end
1:  bgeu t0, t1, 2f            # stop when pointer reaches exclusive end
    sw zero, 0(t0)             # clear one 32-bit word
    addi t0, t0, 4
    jal zero, 1b
2:  call main                  # link in ra; C uses the prepared stack
3:  jal zero, 3b               # main returned: retain results for the bench
```

`sp`, `ra`, `t0`, and `t1` are ABI names for x2, x1, x5, and x6. `la` and `call`
are assembler pseudo-instructions: they expand into real RV32I instructions
and linker relocations. Inspect `make PROG=c_smoke dump` to see their resolved
instructions. The stack remains 16-byte aligned at function-call boundaries
under the RV32 ILP32 calling convention.

Initialized data is already present because `$readmemh` loads `Data.hex` before
execution. This differs from a common embedded arrangement where initialized
data is stored in ROM at a load address and copied to a different runtime RAM
address. This repo uses direct data-RAM initialization; no separate ROM load
address or startup copy loop is required. A boot-from-flash design would need
an explicit initialization mechanism compatible with its memory ports.

The build uses `-march=rv32i -mabi=ilp32` for this instruction set and 32-bit
calling convention. `-nostdlib`, `-nostartfiles`, and `-ffreestanding` keep the
program independent of a hosted C environment; `crt0.S` is linked explicitly.
`-mno-relax` and `-msmall-data-limit=0` prevent the current build from requiring
`gp` (x3) initialization for small-data accesses. If enabling those optimizations,
first add appropriate global-pointer setup and verify the linked instructions.

An assembly-only regression defines `_start` itself and does not link `crt0.S`.
It therefore must initialize any stack or static state it needs; the current
regression uses registers and explicit memory stores instead of C startup.

### Changing the setup

Edit config/memory.json, then run:

```bash
python3 sw/scripts/generate_memory_config.py
cd sw
make install-hex
```

Generated RTL defaults, linker map, and C constants share this configuration.
Build/simulation checks reject stale generated files. Both hex images are padded
to RAM capacity and oversized images are rejected. Program addresses and data
addresses outside capacity fault rather than silently wrapping.

With the default map, low data addresses remain scratch space; C initialized
data/rodata starts at 0x100, BSS follows, and the stack starts at 0x800 and grows
down. The linker reserves at least 256 bytes between static allocations and the
stack top, but does not detect runtime stack overflow. Data.hex preloads data
and rodata directly into data RAM; startup does not copy from instruction ROM.
C sources define main, assembly programs define _start, and no standard library
is linked. Compiler relaxation and small-data addressing are disabled, avoiding
a dependency on an initialized gp register. General library calls, dynamic
allocation, interrupts, exceptions and CSR support remain outside this runtime.

The configuration fields specify **word-address widths**, not byte counts.
For example, changing `program_word_address_bits` from 9 to 10 creates
1024 instruction words, or 4096 bytes. `data_origin` remains a byte address.
Moving it from 256 to 512 reserves more scratch space and reduces the space
available for static data and stack without changing physical RAM size.

| Intended change | Files/settings to update | What to verify |
|-----------------|--------------------------|----------------|
| Increase instruction or data RAM | Edit `config/memory.json`, regenerate, rebuild the image pair | RTL defaults, linker lengths, and hex word counts agree |
| Move static C data | Change `data_origin` in the configuration, regenerate and rebuild | Origin is word aligned, scratch accesses do not overlap static data, and stack space remains |
| Change section placement or minimum stack reserve | Edit the template in `sw/scripts/generate_memory_config.py`, then regenerate | Startup symbols and image extraction still match the layout; adjust configuration checks if geometry format changes |
| Add a C program | Add `sw/programs/<name>.c` defining `main`; run `make PROG=<name>` | Generated instructions stay within implemented RV32I; use a bench with matching results |
| Add assembly startup behavior | Edit that program's `_start`, or `crt0.S` for all C programs | Reset PC, register initialization, BSS handling and calling convention agree |
| Change the hardware reset vector | Update RTL and linker/startup placement together, plus instruction-image base padding | First fetched instruction is `_start`; ELF entry metadata alone cannot redirect reset |

The linker script is generated: editing `sw/linker.ld` directly will be rejected
as configuration drift or overwritten by regeneration. Change the configuration
for geometry changes, or the generator template for structural layout changes.
Per-instance RTL memory overrides do not automatically resize an existing ELF
or image; rebuild software for the intended geometry.

Useful inspection commands, run from `sw/` after building a program:

```bash
make PROG=c_smoke
make PROG=c_smoke dump
riscv64-unknown-elf-readelf -S build/c_smoke.elf   # section addresses and sizes
riscv64-unknown-elf-nm -n build/c_smoke.elf       # symbols sorted by address
```

Check that `_start` is at zero, `.data` begins at the configured origin, BSS
boundaries fit data RAM, and `__stack_top` equals data RAM capacity in bytes.
For a full placement listing, add `-Wl,-Map,build/c_smoke.map` to the link flags
when linking that example; a map shows which input objects contributed to each
output section. Rebuild the ELF after changing link flags, since `make` does not
automatically detect a change to command-line flags as an input-file change.

Use `make PROG=<name> install-hex` to install both images together. The default
regression scoreboard still expects `regression.S`, so use a matching bench for
a custom C program or restore the default with `make install-hex` before running
the default regression.
