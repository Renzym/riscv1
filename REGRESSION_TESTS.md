# RV32I regression tests

The default regression runs [sw/programs/regression.S](sw/programs/regression.S)
on the single-cycle core and checks its final register values. The same
`Program.hex` runs in both the plain SystemVerilog bench and the UVM bench.
These are directed functional tests, not a full ISA compliance suite.

## Test flows and pass criteria

| Flow | Bench | Checks | Success indication |
|------|-------|--------|--------------------|
| Verilator in WSL | [tb_riscv.sv](tb_riscv.sv) | 20 explicit register comparisons; a mismatch calls `$fatal` | `PASS: Program.hex regression (RV32I except SYSTEM/CSR traps).` |
| Vivado xsim / UVM | [tb_top_uvm.sv](uvm_tb/tb_top_uvm.sv) | [riscv_scoreboard.sv](uvm_tb/riscv_scoreboard.sv) compares the same 20 registers | `All expected registers matched`, with zero `UVM_ERROR` and `UVM_FATAL` reports |

Both benches hold reset for two rising clock edges, then run for 300 cycles by
default. The program ends in a loop so its results remain available for checking.
The UVM bench signals `stimulus_done`; its base test waits for this signal before
invoking the scoreboard. UVM can change the execution budget with the simulator
plusarg `+RUN_CYCLES=<count>`; the plain bench uses a fixed count in its source.

The benches observe the DUT register file directly. They do not compare every
retired instruction against a reference model or check the entire memory image.

## What the program exercises

The initial sections use explicit instruction encodings (`.word`); Section G
uses assembly mnemonics. [Program.hex.txt](Program.hex.txt) provides additional
instruction-level notes.

| Section | Behavior exercised | Result checked |
|---------|--------------------|----------------|
| A, PC `0x00`–`0x28` | `ADDI`, `ADD`, `SW`/`LW` at byte address `0x40`, `BEQ` and `JAL` skips, `AUIPC`, `LUI` | Arithmetic results, loaded word, skipped writes to x5, PC-relative and jump-link values |
| B, PC `0x2c` | `JAL` skips to `0x34` and writes its return address | x9 = `0x30` |
| C, PC `0x34` onward | `SB` writes adjacent byte lanes; `LBU` and `LB` read unsigned and signed values | `0xAB`, `0xCD`, signed `0xCD`, and signed `0x80` |
| D | `SH` writes the low and high halfwords at base `0x30`; `LH` and `LHU` read `0xBEE0` | Signed and unsigned extension, including a high-halfword load |
| E | Directed `BEQ` and `BNE` branch sequence | x26 ends at 100, but this final write masks branch errors |
| F | `SLLI` and `SUB` | x27 = 16; x28 = 1 |
| G, PC `0xac` onward | 20 additional checks for branches, comparisons, logic, shifts, `JALR`, and execution past `FENCE` | x10 counts successful checks and must reach 20 |

The word-store encoding at PC `0x00c` must be `04302023` (`sw x3, 64(x0)`),
matching the subsequent load from byte address `0x40`.

### Section G pass counter

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

For example, x10 = 14 suggests execution stopped during check 15 (`SRLI`),
assuming the counter and control flow work correctly. A low count can also
result from insufficient simulation cycles or an earlier execution fault.

`FENCE` acts as a no-op in this simple core; this check does not validate ordering
against concurrent memory agents. Section E's final register value is a smoke
check for its sequence, not an independent assertion of each branch outcome.

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

The snippets below decode the checked-in image, rather than replacing its
`.word` directives. Symbolic names such as `at_1c` make numeric branch targets
readable. Section C's invalid instruction is identified explicitly.

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
address. The jump must skip the padding. x9 retains the link value 48, and is
later reused as the halfword-test base address. This dependency matters when
interpreting a halfword-test failure.

### C: byte stores, lane selection, and sign extension

The first word, at PC `0x34`, is `050005b3`. It has R-type opcode `0x33`,
`rd = x11`, `rs1 = x0`, `rs2 = x16`, `funct3 = 000`, and `funct7 = 0000010`.
That `funct7` is not a valid RV32I ADD or SUB encoding. The current ALU does not
reject it: it selects addition, so x11 becomes x0 + x16 = 0 because x16 has
not yet been written after reset. It does **not** initialize x11 to `0x50`.
Consequently, this test currently accesses data addresses 0, 1, and 2.

```asm
.word 0x050005b3                 # current core produces x11 = 0; invalid RV32I
addi x12, x0, 0xab               # x12 = 171
addi x13, x0, 0xcd               # x13 = 205
sb   x12, 0(x11)                 # byte at 0 = AB
sb   x13, 1(x11)                 # byte at 1 = CD; preserve byte 0
lbu  x14, 0(x11)                 # x14 = 000000AB
lbu  x15, 1(x11)                 # x15 = 000000CD
lb   x16, 1(x11)                 # x16 = FFFFFFCD (-51)
addi x12, x0, -128               # x12 = FFFFFF80
sb   x12, 2(x11)                 # store only low byte 80
lb   x17, 2(x11)                 # x17 = FFFFFF80 (-128)
```

Little-endian RAM places the lowest-addressed byte in bits [7:0]. Starting
from zero-filled RAM, word index 0 evolves as follows:

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
debugging these checks. The invalid setup encoding is a limitation of the
current image, not an example to copy into a new RV32I program.

### D: halfword placement and signed immediates

```asm
addi x18, x0, 0x60               # initializes x18, but stores do not use it
lui  x20, 0xc                    # x20 = 0000C000
addi x20, x20, -288              # x20 = 0000BEE0
sh   x20, 0(x9)                  # x9 = 0x30 from Section B
lh   x21, 0(x9)                  # x21 = FFFFBEE0
lhu  x22, 0(x9)                  # x22 = 0000BEE0
sh   x20, 2(x9)                  # upper half of the same RAM word
lh   x23, 2(x9)                  # x23 = FFFFBEE0
```

The raw ADDI immediate bits are `0xEE0`. As a signed 12-bit number this is
`0xEE0 - 0x1000 = -288`. Therefore `0xC000 - 0x120 = 0xBEE0`.
Using `LUI 0xb` followed by that ADDI would produce `0xAEE0`, not `0xBEE0`.
This is why constructing a constant requires accounting for sign extension.

The accesses are at bytes `0x30` and `0x32`, RAM word index 12. The first
store uses mask `0011` and produces `0000BEE0`; the second uses mask `1100`
and produces `BEE0BEE0`. `LH` extends selected bit 15, which is 1 in `BEE0`;
`LHU` zero-extends. For the high halfword, the RTL selects bits [31:16]
before extending. These checks exercise halfword masks, load selection,
sign extension, and memory writeback. They do not check preservation of the
low halfword by reloading it after the second store.

### E: what the encoded branch sequence actually checks

```asm
addi x26, x0, 0
addi x24, x0, 1
addi x25, x0, 2
beq  x3, x25, at_94              # PC 0x8c: 15 != 2, so not taken
addi x26, x0, 1                  # PC 0x90: executes
at_94:
bne  x3, x25, at_9c              # PC 0x94: 15 != 2, so taken
addi x26, x0, 2                  # PC 0x98: skipped
at_9c:
addi x26, x0, 100                # overwrites the earlier result
```

The encodings `01918463` and `01919463` decode as BEQ and BNE. They do not
test BLT or BGE. Moreover, x26 becomes 100 regardless of which earlier x26
assignment executed, provided control reaches `0x9c`. The final x26 assertion
cannot distinguish correct branch decisions from incorrect ones in this
sequence. Section A and Section G provide stronger BEQ/BNE checks. Signed
BLT/BGE coverage remains absent from the current regression.

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
addi  x11, x11, 16              # x11 = 1dc (target)
jalr  x12, 0(x11)               # PC 1d4: link = 1d8, new PC = 1dc
# PC 0x1d8: jal x0, fail is skipped
# PC 0x1dc
auipc x13, 0                    # x13 = 1dc
addi  x13, x13, -4              # x13 = 1d8 (expected link)
bne   x12, x13, fail
addi  x10, x10, 1
```

Unlike JAL's PC-relative target, JALR computes its target from a register plus
a signed immediate. It still writes PC + 4. Landing at `jalr_link` instead
of the target enters `fail`; reaching the target with an incorrect link also
enters `fail` through BNE. This exercises the ALU target path, `JalPcSel`, and
the PC writeback path. RV32I requires JALR to clear target bit 0; this test
uses an aligned target and does not verify that requirement. The current
`PcNxt` logic directly uses `AluOut`, so bit-0 clearing is not implemented there.

#### Check 20 and the terminal loops

```asm
fence                           # PC 1ec
addi x10, x10, 1                # x10 reaches 20
done:
jal x0, done                    # PC 1f4: success loop
fail:
jal x0, fail                    # PC 1f8: failure loop
```

The simple memory system has no competing agents or outstanding accesses;
the test checks that execution continues past FENCE. It does not demonstrate
a general ordering implementation. Both terminal jumps discard their link
by targeting x0 and use a zero PC-relative offset, keeping the PC stationary.
The benches stop simulation after their cycle budget; the program does not
call a host exit routine. A waveform at PC `0x1f4` with x10 = 20 indicates
the successful path, while PC `0x1f8` identifies the failure loop.

### How the bench turns results into a verdict

The plain bench contains checks such as:

```systemverilog
if (dut.RegfileInst.Regs[10] !== 32'd20) begin
    $fatal(1, "x10 mismatch. Full RV32I self-check expected 20 passes, got %0d",
           dut.RegfileInst.Regs[10]);
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

These values are encoded in both [tb_riscv.sv](tb_riscv.sv) and
[riscv_pkg.sv](uvm_tb/riscv_pkg.sv). Keep both expectation sets synchronized.
Registers omitted from the table are not checked by the default benches.

| Register | Expected value | Purpose |
|----------|----------------|---------|
| x1 | 5 | First arithmetic operand |
| x2 | 10 | Second arithmetic operand |
| x3 | 15 | Addition result |
| x4 | 15 | Word loaded after store |
| x5 | 0 | Writes skipped by branch and jump |
| x6 | 28 | `AUIPC` result |
| x7 | 36 | First `JAL` return address |
| x8 | `0x12345000` | `LUI` result |
| x9 | 48 | Second `JAL` return address |
| x10 | 20 | Section G completed-check count |
| x14 | `0x000000AB` | Unsigned byte load |
| x15 | `0x000000CD` | Unsigned byte load from next lane |
| x16 | `0xFFFFFFCD` | Signed byte load |
| x17 | `0xFFFFFF80` | Signed byte load of -128 |
| x21 | `0xFFFFBEE0` | Signed low-halfword load |
| x22 | `0x0000BEE0` | Unsigned halfword load |
| x23 | `0xFFFFBEE0` | Signed high-halfword load |
| x26 | 100 | Final Section E assignment (masks branch outcomes) |
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
update both benches' expected registers when results change. If Section G gains
checks, update its expected x10 count and the sequence above. Increase the cycle
budget in both flows if the program needs more time.

The regression exercises the implemented arithmetic, logic, shift, branch,
jump, load/store, upper-immediate, and `FENCE` instruction groups. It excludes
`ECALL`, `EBREAK`, and CSR behavior because the core has no exception/CSR
subsystem. It does not exhaustively cover operand combinations, all byte lanes,
alignment cases, memory-capacity boundaries, or reset behavior during execution.
BLT and BGE are not exercised by the current image. The invalid encoding in
Section C and the masked outcomes in Section E should be corrected when improving
the regression; this guide describes the existing image without changing it.
