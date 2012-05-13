SET PATH=C:\Windows\System32;C:\Program Files\PellesC\Lib\Win;C:\Windows\System32;C:\Program Files\PellesC\Lib\;
crinkler.exe /OUT:julia_1k.exe /HASHTRIES:300 /SUBSYSTEM:WINDOWS /UNSAFEIMPPORT /COMPMODE:SLOW /ORDERTRIES:7000 /TRUNCATEFLOATS:16 /PRINT:IMPORTS /ENTRY:WinMainCRTStartup /PRINT:LABELS /REPORT:report.html /RANGE:opengl32.dll kernel32.lib user32.lib winmm.lib gdi32.lib opengl32.lib ../../project_files/julia_1k/output/julia.obj
move julia_1k.exe ..\..\bin\julia_1k.exe
pause