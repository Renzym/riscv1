@echo off
REM Put the Vivado bin directory on PATH before running this script.
setlocal
cd /d "%~dp0"

REM Compile, elaborate, then simulate. Stop if a tool fails.
call xvlog --sv -L uvm -i uvm_tb -f sim/filelist.f
if errorlevel 1 exit /b %ERRORLEVEL%
call xelab -L uvm --timescale 1ns/1ps work.tb_top_uvm -s riscv_uvm
if errorlevel 1 exit /b %ERRORLEVEL%
call xsim riscv_uvm -runall
exit /b %ERRORLEVEL%
