:loop
test.exe
i.exe
i2.exe
fc a.txt b.txt
if %errorlevel%==0 goto loop
pause 
