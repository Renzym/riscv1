#!/usr/bin/env bash
# Run from WSL: ./sim_wsl.sh   (or: bash sim_wsl.sh)
set -euo pipefail
cd "$(dirname "$0")"
rm -rf obj_dir_wsl
# WSL g++ (e.g. 12.x) needs -fcoroutines when Verilator enables timing (from # delays / timescale).
verilator --binary -Wall -Wno-fatal -Wno-DECLFILENAME \
  -CFLAGS "-std=c++20 -fcoroutines" \
  --top-module tb_riscv \
  Rv32iPkg.sv Alu.sv RamSp.sv Regfile.sv Riscv.sv tb_riscv.sv \
  -Mdir obj_dir_wsl
./obj_dir_wsl/Vtb_riscv
