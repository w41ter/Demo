:loop
test.exe
b.exe
b1.exe
fc a.txt b.txt
if %errorlevel%==0 goto loop
pause 
