SET PATH=C:\Windows\System32;C:\Program Files\PellesC\Lib\Win;C:\Windows\System32;C:\Program Files\PellesC\Lib\;
crinkler.exe /OUT:Intro.exe /HASHTRIES:300 /SUBSYSTEM:WINDOWS /UNSAFEIMPPORT /COMPMODE:SLOW /ORDERTRIES:7000 /TRUNCATEFLOATS:16 /PRINT:IMPORTS /ENTRY:WinMainCRTStartup /PRINT:LABELS /REPORT:report.html /RANGE:opengl32.dll kernel32.lib user32.lib winmm.lib gdi32.lib opengl32.lib glu32.lib ../../demo-skeleton/output/main.obj
copy /B /Y Intro.exe ..\..\bin\Intro.exe
pause