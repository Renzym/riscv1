# UVM simulation and RISC-V software build

This repo contains a single-cycle RV32I core with two simulation flows and a WSL
software build path for generating `Program.hex`.

| Flow | Tool | Top | Purpose |
|------|------|-----|---------|
| Fast lint/sim | Verilator in WSL | `tb_riscv.sv` | Quick regression |
| UVM | Vivado 2021.2 xsim | `tb_top_uvm` | Structured regression with scoreboard |

## Current test coverage

The current `Program.hex` regression is not a full RV32I compliance suite. It is
a targeted smoke/regression program that exercises these base RV32I instructions:

- Arithmetic/control/immediate: `ADDI`, `ADD`, `SUB`, `LUI`, `AUIPC`, `SLLI`
- Control flow: `BEQ`, `BLT`, `BGE`, `JAL`
- Memory: `LW`, `SW`, `LB`, `LBU`, `SB`, `LH`, `LHU`, `SH`

It does not currently exercise `ECALL`, `EBREAK`, CSR instructions, or every
RV32I base instruction. Notable untested base instructions include `JALR`,
`BNE`, `BLTU`, `BGEU`, `SLT`, `SLTU`, `SLTI`, `SLTIU`, `XOR`, `OR`, `AND`,
`XORI`, `ORI`, `ANDI`, `SLL`, `SRL`, `SRA`, `SRLI`, and `SRAI`.

Both benches check the same 19 expected register values after 150 cycles. The
expected values live in `tb_riscv.sv` and `uvm_tb/riscv_pkg.sv`.

## RISC-V toolchain in WSL

Install once:

```bash
cd /mnt/e/Renzym/riscv1/sw
bash install_toolchain_wsl.sh
```

Or manually:

```bash
sudo apt-get update
sudo apt-get install -y gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf
```

Build the program ROM image and copy it to the repo root:

```bash
cd /mnt/e/Renzym/riscv1/sw
make install-hex
python3 scripts/verify_hex_format.py
make clean
```

`make install-hex` writes `../Program.hex` and ensures `../Data.hex` exists.
`verify_hex_format.py` verifies the generated sparse memory image against the
checked-in `Program.hex`.

The core uses Harvard memories: instruction fetches use `Program.hex`; loads and
stores use `Data.hex`. Numeric addresses can overlap between the instruction and
data memories because they are separate physical RAMs.

`Program.hex` uses `@` addresses that match byte addresses seen by `Pc[8:0]`
(`0`, `4`, `8`, ...), not dense word indices (`0`, `1`, `2`, ...).

## UVM testbench layout

```text
uvm_tb/
  riscv_pkg.sv            expected register map and default cycle count
  riscv_if.sv             clock/reset plus sampled registers
  riscv_agent.sv          passive agent wrapper
  riscv_scoreboard.sv     register scoreboard
  riscv_env.sv            UVM environment
  riscv_base_test.sv      shared test setup
  riscv_regression_test.sv default Program.hex regression
  tb_top_uvm.sv           DUT wrapper and run_test()
sim/
  filelist.f
  run_uvm.tcl
  run_verilator_tb_xsim.tcl
run_uvm.cmd               Windows Vivado launcher
```

Default test: `riscv_regression_test`. It waits for the top-level stimulus to
complete, samples the DUT register file through `riscv_if`, and checks the
expected register map.

Useful plusargs:

- `+UVM_TESTNAME=riscv_regression_test`
- `+RUN_CYCLES=200`
- `+UVM_VERBOSITY=UVM_MEDIUM`

## Run UVM on Windows

Vivado path used by `run_uvm.cmd`:

```cmd
C:\Xilinx\Vivado\2021.2\bin\vivado.bat
```

Run from the repo root:

```cmd
cd E:\Renzym\riscv1
run_uvm.cmd
```

Equivalent direct command:

```cmd
vivado -mode batch -source sim\run_uvm.tcl
```

`sim/run_uvm.tcl` creates `sim/proj/`, copies `Program.hex` and `Data.hex` into
the xsim working directory, launches the simulation, then closes xsim and the
Vivado project. The script intentionally does not call an extra `run all` after
`launch_simulation`; doing so leaves the always-running clock alive and can grow
waveform output until the disk fills.

## Run Verilator in WSL

```bash
cd /mnt/e/Renzym/riscv1
./sim_wsl.sh
```

## Disk cleanup

The following outputs are generated and safe to delete after tools exit:

- `sim/proj/`
- `sim/proj_tb/`
- `obj_dir/`
- `obj_dir_wsl/`
- `sw/build/`
- `.Xil/`
- root `vivado.jou`, `vivado.log`, and `vivado_*.backup.*`

If Vivado or xsim still holds files open:

```cmd
taskkill /F /IM xsimk.exe
taskkill /F /IM vivado.exe
rd /s /q sim\proj
```

See `SESSION_HANDOFF.md` for the current project state and verification record.
