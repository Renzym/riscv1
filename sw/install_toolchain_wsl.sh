#!/usr/bin/env bash
# Install RISC-V embedded toolchain in WSL (Ubuntu/Debian).
set -euo pipefail
if command -v riscv64-unknown-elf-gcc >/dev/null; then
  echo "Already installed: $(riscv64-unknown-elf-gcc --version | head -1)"
  exit 0
fi
sudo apt-get update
sudo DEBIAN_FRONTEND=noninteractive apt-get install -y \
  gcc-riscv64-unknown-elf \
  binutils-riscv64-unknown-elf
riscv64-unknown-elf-gcc --version | head -1
