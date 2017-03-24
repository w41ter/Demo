@echo off 
:loop 
Data.exe 
right.exe 
test.exe
fc right.out test.out 
if not errorlevel 1 goto loop
pause
goto loop
