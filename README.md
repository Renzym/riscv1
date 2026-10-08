# UVM simulation and RISC-V software build

This repo contains a single-cycle RV32I core with two simulation flows and a WSL
software build path for generating `Program.hex`.

All commands below are written relative to the repo root. If the repo is cloned
elsewhere, start from that clone directory; no `E:\...` or `/mnt/e/...` path is
required.

| Flow | Tool | Top | Purpose |
|------|------|-----|---------|
| Fast lint/sim | Verilator in WSL | `tb_riscv.sv` | Quick regression |
| UVM | Vivado 2021.2 xsim | `tb_top_uvm` | Structured regression with scoreboard |

## Current test coverage

`Program.hex` is generated from `sw/programs/regression.S` by default. It is a
targeted RV32I regression, not a full compliance suite, but it now exercises all
base RV32I instruction groups implemented by this core except system/trap and
CSR instructions.

Covered instructions:

- Integer arithmetic/immediates: `ADDI`, `ADD`, `SUB`, `SLT`, `SLTU`, `SLTI`,
  `SLTIU`
- Logic/immediates: `XOR`, `OR`, `AND`, `XORI`, `ORI`, `ANDI`
- Shifts: `SLL`, `SLLI`, `SRL`, `SRLI`, `SRA`, `SRAI`
- Control flow: `BEQ`, `BNE`, `BLT`, `BGE`, `BLTU`, `BGEU`, `JAL`, `JALR`
- Memory: `LB`, `LH`, `LW`, `LBU`, `LHU`, `SB`, `SH`, `SW`
- Upper/immediate and ordering: `LUI`, `AUIPC`, `FENCE`

Not covered: `ECALL`, `EBREAK`, and CSR instructions. Those are intentionally
excluded because this simple core has no exception/CSR subsystem.

Both benches check the same 20 expected register values after 300 cycles. The
new x10 check is a self-check pass counter for the added RV32I coverage; it must
finish at 20.

## How Program.hex Is Generated

The Makefile builds a freestanding RV32I ELF with `riscv64-unknown-elf-gcc`,
converts it to a raw binary with `objcopy`, then converts that binary to Vivado
`$readmemh` format with `sw/scripts/elf2memh.py`.

The default program is assembly:

```bash
cd sw
make install-hex
python3 scripts/verify_hex_format.py
make clean
```

That builds:

```text
programs/regression.S -> build/regression.elf -> build/regression.bin
                      -> build/regression.hex -> ../Program.hex
```

`make install-hex` also ensures `../Data.hex` exists. The verifier compares
`sw/build/regression.hex` against the checked-in `Program.hex` when the build
output is present, and always validates `Program.hex` formatting.

## Generating Hex From C

The same flow can compile a freestanding C file named `sw/programs/<name>.c`.
Example:

```bash
cd sw
make PROG=c_smoke
```

This builds `sw/build/c_smoke.hex` from `sw/programs/c_smoke.c`. To install that
image as the simulator ROM:

```bash
cd sw
make PROG=c_smoke install-hex
```

Important: the default benches expect the register results produced by
`regression.S`. If you install a different C-generated `Program.hex`, update the
scoreboard expectations or run it with a matching test.

The C flow is freestanding: no C runtime, no standard library startup, and no
automatic data/BSS initialization code. C programs must provide `_start` and
should avoid library calls unless you add runtime support.

## RISC-V Toolchain In WSL

Install once from the repo root:

```bash
cd sw
bash install_toolchain_wsl.sh
```

Or manually:

```bash
sudo apt-get update
sudo apt-get install -y gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf
```

The core uses Harvard memories: instruction fetches use `Program.hex`; loads and
stores use `Data.hex`. Numeric addresses can overlap between the instruction and
data memories because they are separate physical RAMs.

`Program.hex` uses `@` addresses that match byte addresses seen by `Pc[8:0]`
(`0`, `4`, `8`, ...), not dense word indices (`0`, `1`, `2`, ...).

## UVM Testbench Layout

```text
uvm_tb/
  riscv_pkg.sv             expected register map and default cycle count
  riscv_if.sv              clock/reset plus sampled registers
  riscv_agent.sv           passive agent wrapper
  riscv_scoreboard.sv      register scoreboard
  riscv_env.sv             UVM environment
  riscv_base_test.sv       shared test setup
  riscv_regression_test.sv default Program.hex regression
  tb_top_uvm.sv            DUT wrapper and run_test()
sim/
  filelist.f
  run_uvm.tcl
  run_verilator_tb_xsim.tcl
run_uvm.cmd                Windows Vivado launcher
```

Default test: `riscv_regression_test`. It waits for the top-level stimulus to
complete, samples the DUT register file through `riscv_if`, and checks the
expected register map.

Useful plusargs:

- `+UVM_TESTNAME=riscv_regression_test`
- `+RUN_CYCLES=400`
- `+UVM_VERBOSITY=UVM_MEDIUM`

## Run UVM On Windows

`run_uvm.cmd` assumes Vivado is installed at:

```cmd
C:\Xilinx\Vivado\2021.2\bin\vivado.bat
```

If your Vivado install is elsewhere, edit the `VIVADO_BAT` variable in
`run_uvm.cmd`.

Run from the repo root:

```cmd
run_uvm.cmd
```

Equivalent direct command when `vivado` is on `PATH`:

```cmd
vivado -mode batch -source sim\run_uvm.tcl
```

`sim/run_uvm.tcl` creates `sim/proj/`, copies `Program.hex` and `Data.hex` into
the xsim working directory, launches the simulation, then closes xsim and the
Vivado project. It intentionally does not call an extra `run all` after
`launch_simulation`; doing so leaves the always-running clock alive and can grow
waveform output until the disk fills.

## Run Verilator In WSL

From the repo root:

```bash
./sim_wsl.sh
```

## Disk Cleanup

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
