# Compile, elaborate, and simulate the UVM regression using standalone XSim tools.
$ErrorActionPreference = 'Stop'
# Adjust this path for your Vivado installation. No PATH setup is needed.
$vivadoBin = 'C:\Xilinx\Vivado\2021.2\bin'

Push-Location $PSScriptRoot
try {
    # Compile the sources, elaborate the top, then run the simulation.
    & "$vivadoBin\xvlog.bat" --sv -L uvm -i uvm_tb -f sim/filelist.f
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    & "$vivadoBin\xelab.bat" -L uvm --timescale 1ns/1ps work.tb_top_uvm -s riscv_uvm
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    & "$vivadoBin\xsim.bat" riscv_uvm -runall
    $result = $LASTEXITCODE
} finally {
    Pop-Location
}
exit $result
