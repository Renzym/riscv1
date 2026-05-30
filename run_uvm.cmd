@echo off
REM Run UVM regression with Vivado 2021.2 (adjust path if needed).
setlocal
set VIVADO_BIN=C:\Xilinx\Vivado\2021.2\bin\vivado.bat
if not exist "%VIVADO_BIN%" (
  echo Vivado not found at %VIVADO_BIN%
  echo Set VIVADO_BIN to your vivado.bat and retry.
  exit /b 1
)
cd /d "%~dp0"
echo Repo: %CD%
echo Ensure Program.hex and Data.hex exist in repo root.
echo Optional WSL build: wsl bash -lc "cd sw && make install-hex"
"%VIVADO_BIN%" -mode batch -source sim/run_uvm.tcl
echo Exit code: %ERRORLEVEL%
pause
