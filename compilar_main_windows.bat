@echo off
chcp 65001 > nul
cscript //nologo maximize.vbs
timeout /t 1 /nobreak > nul
gcc main.c presentacionWin.c -o main
main.exe
pause
