:loop
data.exe
3415.exe <3415.in> 3415.out
3415_f.exe <3415.in> 3415_f.out
3415_s.exe <3415.in> 3415_s.out
fc 3415.out 3415_f.out
fc 3415.out 3415_s.out
if errorlevel 1 pause
goto loop
