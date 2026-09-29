@echo off
chcp 65001 >nul
setlocal

echo ============================================
echo   VS UTF-8 Fix - Diagnostic
echo ============================================
echo.

set "DIR=%LOCALAPPDATA%\Microsoft\MSBuild\v4.0"

echo [1] Expected folder:
echo     %DIR%
echo.

if exist "%DIR%" (
    echo     STATUS: EXISTS
) else (
    echo     STATUS: MISSING   ^<-- problem found
)
echo.

echo [2] Files inside:
echo.
dir /B "%DIR%" 2>nul
if errorlevel 1 echo     (none, or folder missing)
echo.

echo [3] Checking the two props files:
echo.
if exist "%DIR%\Microsoft.Cpp.x64.user.props" (
    echo     x64   : FOUND
    type "%DIR%\Microsoft.Cpp.x64.user.props"
) else (
    echo     x64   : NOT FOUND   ^<-- problem found
)
echo.
if exist "%DIR%\Microsoft.Cpp.Win32.user.props" (
    echo     Win32 : FOUND
) else (
    echo     Win32 : NOT FOUND
)
echo.

echo [4] Your project folder check:
echo     Look for Directory.Build.props in your repo root.
echo     (e.g. F:\Github_C_learning\Directory.Build.props)
echo.

echo ============================================
echo   Copy the output above and send it back.
echo ============================================
echo.
pause
