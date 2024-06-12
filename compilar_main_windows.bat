
@echo off

cscript //nologo maximize.vbs

chcp 65001 > nul
timeout /t 1 /nobreak > nul
gcc main.c presentacionWin.c -o main
main.exe
pause
