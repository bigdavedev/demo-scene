SET PATH=C:\Windows\System32;C:\Program Files\PellesC\Lib\Win;C:\Windows\System32;C:\Program Files\PellesC\Lib\;
crinkler.exe /OUT:hypershapes_1k.exe /HASHTRIES:300 /SUBSYSTEM:WINDOWS /UNSAFEIMPPORT /COMPMODE:SLOW /ORDERTRIES:7000 /TRUNCATEFLOATS:16 /PRINT:IMPORTS /ENTRY:WinMainCRTStartup /PRINT:LABELS /REPORT:report.html /RANGE:opengl32.dll kernel32.lib user32.lib winmm.lib gdi32.lib opengl32.lib glu32.lib ../../project_files/hypershapes/output/hypershapes.obj
move hypershapes_1k.exe ..\..\bin\hypershapes_1k.exe
pause