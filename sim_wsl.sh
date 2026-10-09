#!/usr/bin/env bash
# Run from WSL: ./sim_wsl.sh   (or: bash sim_wsl.sh)
set -euo pipefail
ulimit -c 0 # expected-failure tests must not leave core dumps
cd "$(dirname "$0")"
python3 sw/scripts/generate_memory_config.py --check
python3 sw/scripts/verify_hex_format.py
top="${1:-tb_riscv}"
case "$top" in
  tb_riscv) bench=tb_riscv.sv ;;
  tb_core_checks) bench=sim/tb_core_checks.sv ;;
  tb_c_smoke) make -C sw PROG=c_smoke; bench=sim/tb_c_smoke.sv ;;
  tb_fault_report) bench=sim/tb_fault_report.sv ;;
  *) echo "Unknown bench: $top" >&2; exit 1 ;;
esac
# WSL g++ (e.g. 12.x) needs -fcoroutines when Verilator enables timing (from # delays / timescale).
verilator --binary -Wall -Wno-fatal -Wno-DECLFILENAME \
  -CFLAGS "-std=c++20 -fcoroutines" \
  --top-module "$top" \
  rtl/MemoryConfigPkg.sv rtl/Rv32iPkg.sv rtl/Alu.sv rtl/RamSp.sv rtl/Regfile.sv rtl/Riscv.sv \
  uvm_tb/riscv_pkg.sv "$bench" \
  -Mdir "obj_dir_wsl/$top"
if [[ "$top" == tb_fault_report ]]; then
  result_log="obj_dir_wsl/$top/expected_fault.log"
  if "./obj_dir_wsl/$top/V$top" > "$result_log" 2>&1; then
    echo "Expected a nonzero result from the core diagnostic" >&2
    exit 1
  fi
  if ! grep -q "Core fault:" "$result_log"; then
    cat "$result_log" >&2
    exit 1
  fi
  echo "PASS: normal simulation reports core faults with nonzero status."
else
  "./obj_dir_wsl/$top/V$top"
fi
