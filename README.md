# UVM simulation and RISC-V software build

This repo contains a single-cycle RV32I core with two simulation flows and a WSL
software build path for generating `Program.hex`.

| Flow | Tool | Top | Purpose |
|------|------|-----|---------|
| Fast lint/sim | Verilator in WSL | `tb_riscv.sv` | Quick regression |
| UVM | Vivado 2021.2 xsim | `tb_top_uvm` | Structured regression with scoreboard |

## Current test coverage

See [Regression tests](REGRESSION_TESTS.md) for an assembly walkthrough of each
test, hardware signal explanations, expected register values, pass criteria,
run commands, and current coverage gaps.

`Program.hex` is generated from `sw/programs/regression.S` by default. It is a
targeted RV32I regression, not a full compliance suite. All instructions in the
regression use mnemonics. Signed branches, memory preservation, shift boundaries,
backward branches and x0 are checked explicitly.

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

Both benches check the same 21 expected register values after 500 cycles, using
one table in `uvm_tb/riscv_pkg.sv`. x10 is the self-check pass counter and must
finish at 33. Additional benches check faults, memory boundaries, reset during
execution, C startup, and four-state scoreboard behavior.

## How Program.hex Is Generated

The Makefile builds a freestanding RV32I ELF with `riscv64-unknown-elf-gcc`,
extracts instruction and initialized-data binaries with `objcopy`, then converts
them to plain `$readmemh` words with `sw/scripts/elf2memh.py`. Images are padded
to the configured RAM capacity; oversized images are rejected.

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

`make install-hex` also installs the matching `../Data.hex`. The verifier compares
`sw/build/regression.hex` against the checked-in `Program.hex` when the build
output is present, and always validates both images' formatting and sizes.

## Generating Hex From C

The same flow can compile a freestanding C file named `sw/programs/<name>.c`.
Example:

```bash
cd sw
make PROG=c_smoke
```

This builds `sw/build/c_smoke.hex` and `sw/build/c_smoke.data.hex` from
`sw/programs/c_smoke.c` and `sw/crt0.S`. To install that image pair:

```bash
cd sw
make PROG=c_smoke install-hex
```

Important: the default benches expect the register results produced by
`regression.S`. If you install a different C-generated `Program.hex`, update the
scoreboard expectations or run it with a matching test.

The C flow is freestanding and links a small startup routine: it sets the stack,
clears BSS, calls `main`, and loops if `main` returns. `Data.hex` preloads initialized
data and read-only constants into data RAM; no ROM-to-RAM copy is needed. C
programs provide `main`; assembly programs provide `_start`. No standard library,
heap, exception or interrupt support is supplied. Low data addresses are reserved
for scratch/signatures; static C data begins at `0x100` by default.

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

`Program.hex` and `Data.hex` contain one eight-digit 32-bit hex word per line,
with no `@` markers. Line 1 loads word index 0 (byte address 0); line 2 loads
word index 1 (byte address 4). Program fetch drops the two byte-offset PC bits,
just as data RAM addressing drops the two byte-offset bits from the ALU result.
Unspecified trailing RAM words are initialized to zero.

Synthesizable SystemVerilog sources live in `rtl/`; `tb_riscv.sv` remains at
the repo root and the UVM bench remains in `uvm_tb/`.

`rtl/Riscv.sv` exposes `PROG_MEM_ADDR_BITS` and `DATA_MEM_ADDR_BITS`, both
defaulting to 9. Each memory therefore contains 512 words (2 KiB). RAM depth,
initialization bounds, and address slices derive from these parameters. The
PC remains 32 bits for RV32I. The old program RAM used byte indexing and wrapped
at 512 bytes; word indexing now makes all 2 KiB usable. Addresses beyond the
configured memory capacity fault rather than wrap. Misaligned instruction
targets and halfword/word data accesses also fault. The core halts and suppresses
writes; normal simulation terminates with a diagnostic. This is a defined
limitation, not an architectural exception/trap implementation.

Edit `config/memory.json` to change memory defaults or the C data origin, then run:

```bash
python3 sw/scripts/generate_memory_config.py
cd sw
make install-hex
```

This generates `rtl/MemoryConfigPkg.sv`, `sw/linker.ld`, and `sw/memory_config.h`.
Build and both simulation flows reject stale generated files. Per-instance RTL parameter
overrides remain useful for directed tests; software images must fit that instance.

## UVM Testbench Layout

```text
uvm_tb/
  riscv_pkg.sv             expected register map and default cycle count
  riscv_if.sv              clock/reset plus sampled registers
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
- `+RUN_CYCLES=600`
- `+UVM_VERBOSITY=UVM_MEDIUM`

## Run UVM On Windows

`run_uvm.cmd` assumes Vivado is installed at:

```cmd
C:\Xilinx\Vivado\2021.2\bin\vivado.bat
```

If your Vivado install is elsewhere, edit the `VIVADO_BIN` variable in
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

Additional checks, also from the repo root:

```bash
bash sim_wsl.sh tb_core_checks
bash sim_wsl.sh tb_c_smoke
bash sim_wsl.sh tb_fault_report
python3 sw/scripts/test_memory_tools.py
tclsh sim/test_sim_result.tcl
```

The C bench builds its own image pair without replacing the root regression
images. To run directed checks and the X/Z scoreboard check in Vivado:

```cmd
vivado -mode batch -source sim\run_directed_checks.tcl
```

Build the C pair first with `cd sw && make PROG=c_smoke` in WSL. Vivado scripts
require a completion marker and reject error/fatal reports; Windows launchers
propagate failure status.

## Disk Cleanup

Close the simulators, then run from PowerShell:

```powershell
.\cleanup_sim.ps1 -WhatIf  # preview the targets
.\cleanup_sim.ps1          # remove simulator outputs
```

The script removes Verilator/Vivado output directories, `.Xil/`, and root Vivado
logs/journals/backups. It works independently of the current working directory,
skips absent outputs, and refuses symbolic links or junctions. Software builds
are cleaned separately in WSL with `make -C sw clean`; root hex images are kept.

The following outputs are generated and safe to delete after tools exit:

- `sim/proj/`
- `sim/proj_tb/`
- `sim/proj_checks/`
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
