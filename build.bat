@echo off
echo Compiling Windows Volume Control with MSVC...
cl volume_control.c /link Ole32.lib
if %ERRORLEVEL% == 0 (
    echo Build successful! Run volume_control.exe to start the program.
) else (
    echo Build failed!
)
pause
