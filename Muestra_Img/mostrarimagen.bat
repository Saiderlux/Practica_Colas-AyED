@echo off

cscript //nologo maximize1.vbs
timeout /t 1 /nobreak > nul
gcc pimage.c cambioconsol.c -o p
p.exe
cscript //nologo maximize2.vbs
pause