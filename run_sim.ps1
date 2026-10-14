# Run a Verilator bench through sim_wsl.sh in the repository's WSL directory.
param([string]$Bench = 'tb_riscv')
$ErrorActionPreference = 'Stop'

wsl --cd "$PSScriptRoot" --exec bash ./sim_wsl.sh $Bench
exit $LASTEXITCODE
