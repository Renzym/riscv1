# Session handoff: RV32I core, regression and software build

**Last updated:** 2026-10-09
**Repo:** this clone of riscv1; commands are relative to the repo root.
**Tools:** Verilator in WSL; Vivado 2021.2 xsim on Windows.

## Current architecture

- Synthesizable RTL lives in rtl/. Riscv is a single-cycle RV32I core with
  separate instruction/data RAM, asynchronous reads and synchronous writes.
- config/memory.json is the source for RAM defaults and the C data origin.
  sw/scripts/generate_memory_config.py generates rtl/MemoryConfigPkg.sv,
  sw/linker.ld and sw/memory_config.h. --check rejects stale generated files.
- Defaults: 512 instruction words / 2 KiB and 512 data words / 2 KiB.
  The PC and architectural registers remain 32 bits. RAM indices discard the
  two byte-offset bits; byte/halfword accesses use lane masks and extension.
- Program.hex and Data.hex are plain eight-digit words, padded to capacity.
  The generator rejects oversized images. They are installed as a matching pair.
- JALR clears target bit 0. Unsupported encodings, misaligned accesses/targets
  and out-of-range addresses assert Fault, halt the core and suppress writes.
  This is not an architectural exception subsystem. Default simulation reports
  a fatal diagnostic; directed tests can set REPORT_FAULTS=0 to inspect Fault.
- x0 reads/probes zero; writes are discarded. Reset clears the other registers
  and PC but does not clear data RAM.

## Regression and benches

See [REGRESSION_TESTS.md](REGRESSION_TESTS.md) for complete assembly snippets,
expected values, hardware behavior, debugging steps and coverage limitations.
Program.hex.txt has been consolidated into that guide.

- Default software source: sw/programs/regression.S, all executable instructions
  written as mnemonics. The original arithmetic/PC checks retain their addresses.
- Byte tests use explicit base 0x50; halfword tests use explicit base 0x60.
- Section E has actual BLT/BGE tests with failure jumps. Sections G/H count
  33 self-checks, including an odd JALR target, store preservation, signed
  boundaries, shift limits, backward branches and x0 writes.
- Both benches use uvm_tb/riscv_pkg.sv: 21 expected registers and 500 cycles.
  Reset deassertion and final sampling happen on falling clock edges.
- The UVM environment contains a scoreboard; unused driver/monitor/agent shells
  were removed. Register samples remain four-state logic to reject X/Z.
- The directed core bench checks faults and side-effect isolation, valid/invalid
  RAM boundaries and reset during execution. The xsim scoreboard unit check
  explicitly rejects X/Z samples against expected zero.
- run_uvm.tcl and run_verilator_tb_xsim.tcl close xsim before reading its flushed
  log, then require a pass marker and reject error/fatal reports. They never
  invoke a second unbounded run all. Windows launchers propagate error status.

## Software runtime

Assembly sources define _start. C sources define main and link sw/crt0.S.
Startup sets sp, clears BSS, calls main and loops when main returns. Compiler
relaxation and small-data addressing are disabled, so gp setup is unnecessary.
No standard library, heap, interrupt/exception or CSR support is provided.

The Harvard linker map places text in program RAM and initialized data/rodata
in data RAM from 0x100 by default. Low data addresses are scratch/signature space.
Data.hex preloads initialized data directly; startup does not copy from ROM.
BSS follows static data. Stack starts at 0x800 and grows down; the linker leaves
at least 256 bytes for it but runtime overflow is not detected.

The C smoke program checks initialized globals, BSS, constants, stack use and
function calls. Its bench poisons zero-filled RAM before startup to verify BSS
clearing, then checks signature 0x12345678 at data byte address 0x40.

## Run commands

```bash
# WSL: regenerate config only after editing config/memory.json
python3 sw/scripts/generate_memory_config.py

# Build/install the default image pair
cd sw
make install-hex
python3 scripts/verify_hex_format.py
make PROG=c_smoke
cd ..

# Verilator and helper checks
bash sim_wsl.sh
bash sim_wsl.sh tb_core_checks
bash sim_wsl.sh tb_c_smoke
bash sim_wsl.sh tb_fault_report
python3 sw/scripts/test_memory_tools.py
tclsh sim/test_sim_result.tcl
```

```cmd
REM Windows / Vivado 2021.2
run_uvm.cmd
vivado -mode batch -source sim\run_verilator_tb_xsim.tcl
vivado -mode batch -source sim\run_directed_checks.tcl
```

The directed xsim checks require the C images to have been built in WSL first.
The C bench reads its own sw/build images without replacing the root regression.
The fault-report bench is an expected-failure test: the runner requires the
specific core diagnostic rather than accepting an unrelated failure.

## Generated artifacts and cleanup

Keep sim/proj/, sim/proj_tb/, sim/proj_checks/, obj_dir/, obj_dir_wsl/,
sw/build/, .Xil/, __pycache__/, Vivado logs/journals and WDBs out of commits.
Memory config outputs and the root regression image pair are checked in.

Do not run another run all after launch_simulation: an earlier version left
an always-running clock alive and grew waveform output to approximately 88 GB.
If tools retain open files, exit them before deleting their output directories.

```cmd
taskkill /F /IM xsimk.exe
taskkill /F /IM vivado.exe
rd /s /q sim\proj
```

## Verification record

The earlier documentation snapshot was committed as 28ecbb6 before these fixes.
Current Verilator results: default regression (33 checks / 21 registers),
directed faults/bounds/JALR/reset, C startup with poisoned BSS, and automatic
fault diagnostics passed. Nine Python memory-tool tests and Tcl result-parser
checks passed; alternate program/data widths (8/10) pass lint.
Vivado UVM and plain regressions passed with correct launcher status. Directed
core, C, four-state scoreboard and expected core diagnostic checks passed.
