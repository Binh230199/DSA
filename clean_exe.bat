@echo off
echo ==========================================
echo   DSA Directory Cleanup Script
echo ==========================================
echo.
echo This script will remove all .exe files from the DSA directory
echo Current directory: %CD%
echo.

set /p confirm="Are you sure you want to delete all .exe files? (y/n): "
if /i "%confirm%" neq "y" (
    echo Cleanup cancelled.
    pause
    exit /b
)

echo.
echo Starting cleanup...
echo.

:: Count files before deletion
for /f %%i in ('dir /s /b "*.exe" 2^>nul ^| find /c /v ""') do set count=%%i
echo Found %count% .exe files to delete.

if %count% equ 0 (
    echo No .exe files found to delete.
    echo.
    pause
    exit /b
)

echo.
echo Deleting .exe files...
echo.

:: Delete all .exe files recursively and show progress
for /f "delims=" %%f in ('dir /s /b "*.exe" 2^>nul') do (
    echo Deleting: %%f
    del "%%f" /q
)

echo.
echo ==========================================
echo   Cleanup Complete!
echo ==========================================
echo Successfully removed %count% .exe files.
echo.
pause
