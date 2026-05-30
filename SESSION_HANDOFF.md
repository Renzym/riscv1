# Session handoff: RISC-V UVM testbench + WSL toolchain

**Last updated:** 2026-05-30
**Repo:** `E:\Renzym\riscv1`
**Tools used:** Verilator in WSL, Vivado 2021.2 xsim on Windows

## Goals

1. UVM testbench for Vivado/xsim using `tb_top_uvm`.
2. RISC-V GCC build flow in WSL to generate and verify `Program.hex`.
3. Keep generated simulator/build artifacts out of the repo and avoid large WDB
   files filling the disk.

## Current status

| Item | Status |
|------|--------|
| WSL RISC-V toolchain | Installed (`gcc-riscv64-unknown-elf`, `binutils-riscv64-unknown-elf`) |
| WSL ROM build | PASS: `make install-hex && python3 scripts/verify_hex_format.py && make clean` |
| Verilator flow | PASS: `./sim_wsl.sh` |
| Vivado UVM flow | PASS: `run_uvm.cmd`, 19/19 register checks OK |
| Generated artifact cleanup | Done after verification |

No Vivado/xsim simulator processes were left running after the latest successful
UVM run.

## Important fix from this session

`sim/run_uvm.tcl` previously called `run all` after `launch_simulation`. The UVM
test had already finished at that point, but the testbench clock keeps toggling,
so the second unbounded run kept xsim alive and caused `false.wdb`/wave output to
grow to roughly 88 GB.

Current `sim/run_uvm.tcl` behavior:

- Creates `sim/proj/`.
- Adds files from `sim/filelist.f`.
- Copies `Program.hex` and `Data.hex` into xsim's working directory.
- Runs `launch_simulation -simset sim_1`.
- Closes simulation and project with `close_sim -force` and `close_project`.
- Does not call a second `run all`.
- Does not set `xsim.simulate.wdb` to the literal string `false`.

## Generated artifacts removed

These are safe to regenerate and were cleaned:

| Path | Notes |
|------|-------|
| `sim/proj/` | Vivado UVM project and xsim outputs, recreated by `sim/run_uvm.tcl` |
| `sim/proj_tb/` | One-off plain `tb_riscv` xsim project |
| `obj_dir/`, `obj_dir_wsl/` | Verilator build outputs, recreated by `./sim_wsl.sh` |
| `sw/build/` | WSL software build output, recreated by `make install-hex` |
| `.Xil/` | Vivado scratch |
| `vivado.jou`, `vivado.log`, `vivado_*.backup.*` | Vivado logs |
| `__pycache__/` | Python bytecode cache |

`.gitignore` now ignores these generated paths and common Vivado junk.

If cleanup fails because tools are still open:

```cmd
taskkill /F /IM xsimk.exe
taskkill /F /IM vivado.exe
rd /s /q E:\Renzym\riscv1\sim\proj
```

## UVM architecture

- Top: `tb_top_uvm`, instantiates `Riscv` and `riscv_if`.
- Stimulus: top-level `initial` block, matching `tb_riscv.sv`: 2 reset cycles,
  then `DEFAULT_RUN_CYCLES` (150) cycles, then `stimulus_done = 1`.
- Test: `riscv_regression_test` waits for `stimulus_done`, delays `#1step`, and
  calls the scoreboard.
- Scoreboard: checks 19 registers from `riscv_pkg::REGRESSION_EXPECTS`.
- Register probe: `riscv_vif.regs[i] = dut.RegfileInst.Regs[i]`.
- Memory images: `sim/run_uvm.tcl` copies `Program.hex` and `Data.hex` into
  `sim/proj/.../behav/xsim/` because xsim's working directory is not the repo
  root.
- Interface initialization: `riscv_if` initializes `stimulus_done = 0`; this is
  required to prevent an early UVM check.

## Current regression coverage

The current tests are passing, but they are not a full RV32I compliance suite.
They exercise a targeted subset through `Program.hex`:

- `ADDI`, `ADD`, `SUB`, `LUI`, `AUIPC`, `SLLI`
- `BEQ`, `BLT`, `BGE`, `JAL`
- `LW`, `SW`, `LB`, `LBU`, `SB`, `LH`, `LHU`, `SH`

They do not currently test `ECALL`, `EBREAK`, CSR instructions, or every base
RV32I instruction. Notable untested base instructions include `JALR`, `BNE`,
`BLTU`, `BGEU`, `SLT`, `SLTU`, `SLTI`, `SLTIU`, `XOR`, `OR`, `AND`, `XORI`,
`ORI`, `ANDI`, `SLL`, `SRL`, `SRA`, `SRLI`, and `SRAI`.

## RTL changes to keep

1. `Regfile.sv`: unpacked `logic [31:0] Regs [depth]`; x0 read via mux; no
   `assign Regs[0]`.
2. `RamSp.sv`: `logic` RAM; zero-initializes all words before `$readmemh`
   because xsim leaves sparse memory holes as X.
3. `Alu.sv`: xsim X-propagation fixes:
   - `Subtract` derives from raw `Opc`, `Funct3`, and `Funct7`.
   - `BrTaken` is only asserted when `Opc == OP_BRANCH`.
   - Shifter and `AluOut` mux use raw `Funct3` for math/math_imm.
4. `Program.hex`: `@00c` must remain `04302023`, encoding `sw x3, 64(x0)`.
   The older `02302023` stores at byte address 32 while the test loads from 64.

## WSL toolchain flow

```bash
cd /mnt/e/Renzym/riscv1/sw
bash install_toolchain_wsl.sh
make install-hex
python3 scripts/verify_hex_format.py
make clean
```

Notes:

- `sw/programs/regression.S` uses a `.word` list and `.org 0x34` to preserve the
  intentional gap at PC `0x30` after `jal x9`.
- `sw/scripts/elf2memh.py --sparse` skips all-zero words so generated hex
  matches the checked-in sparse `Program.hex`.
- `sw/scripts/verify_hex_format.py` now expects the corrected `04302023` store
  word.

## How to run

```bash
# WSL: rebuild Program.hex
cd /mnt/e/Renzym/riscv1/sw
make install-hex
python3 scripts/verify_hex_format.py
make clean

# WSL: Verilator
cd /mnt/e/Renzym/riscv1
./sim_wsl.sh
```

```cmd
REM Windows: Vivado UVM
cd E:\Renzym\riscv1
run_uvm.cmd

REM Equivalent direct command
vivado -mode batch -source sim\run_uvm.tcl
```

Default Vivado path in `run_uvm.cmd`:

```cmd
C:\Xilinx\Vivado\2021.2\bin\vivado.bat
```

## Expected registers

Same values are checked by `tb_riscv.sv` and
`uvm_tb/riscv_pkg.sv::REGRESSION_EXPECTS`:

`x1=5`, `x2=10`, `x3=15`, `x4=15`, `x5=0`, `x6=28`, `x7=36`,
`x8=0x12345000`, `x9=48`, `x14=0xAB`, `x15=0xCD`, `x16=0xFFFFFFCD`,
`x17=0xFFFFFF80`, `x21=0xFFFFBEE0`, `x22=0x0000BEE0`,
`x23=0xFFFFBEE0`, `x26=100`, `x27=16`, `x28=1`.

See `Program.hex.txt` for instruction-level notes.
