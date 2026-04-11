@echo off
REM Verilator lives in WSL; this converts this folder to a WSL path and runs sim_wsl.sh.
for /f "usebackq delims=" %%i in (`wsl wslpath -a "%~dp0."`) do (
  wsl -e bash -lc "cd '%%i' && bash sim_wsl.sh"
)
echo.
pause
