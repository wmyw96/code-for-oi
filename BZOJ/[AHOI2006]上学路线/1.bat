:loop
data.exe
[AHOI2006]上学路线route.exe <1.in> 1.out
1.exe <1.in> 2.out
fc 1.out 2.out
if errorlevel 1 pause
goto loop
