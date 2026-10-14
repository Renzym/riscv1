# Run a plain or directed bench with standalone XSim tools.
param(
    [ValidateSet('tb_riscv', 'tb_core_checks', 'tb_c_smoke', 'tb_scoreboard_checks', 'tb_fault_report')]
    [string]$Bench = 'tb_riscv'
)
$ErrorActionPreference = 'Stop'
# Adjust this path for your Vivado installation.
$vivadoBin = 'C:\Xilinx\Vivado\2021.2\bin'
$benchFile = if ($Bench -eq 'tb_riscv') { 'tb_riscv.sv' } else { "sim/$Bench.sv" }

Push-Location $PSScriptRoot
try {
    & "$vivadoBin\xvlog.bat" --sv -L uvm -i uvm_tb -f sim/rtl.f $benchFile
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    & "$vivadoBin\xelab.bat" -L uvm --timescale 1ns/1ps "work.$Bench" -s $Bench
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    & "$vivadoBin\xsim.bat" $Bench -runall
    $result = $LASTEXITCODE
} finally {
    Pop-Location
}
exit $result
