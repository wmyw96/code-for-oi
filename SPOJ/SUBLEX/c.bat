:loop
data.exe
time<enter
SUBLEX.exe <SUBLEX.in> SUBLEX.out
time<enter
time<enter
f.exe <SUBLEX.in> SUBLEX_f.out
time<enter
fc SUBLEX.out SUBLEX_f.out
if errorlevel 1 pause
goto loop
