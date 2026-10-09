@echo off
REM Verilator lives in WSL; this converts this folder to a WSL path and runs sim_wsl.sh.
set RAN=0
for /f "usebackq delims=" %%i in (`wsl wslpath -a "%~dp0."`) do (
  set RAN=1
  wsl -e bash -lc "cd '%%i' && bash sim_wsl.sh"
  if errorlevel 1 exit /b 1
)
if "%RAN%"=="0" exit /b 1
echo.
pause
exit /b 0
