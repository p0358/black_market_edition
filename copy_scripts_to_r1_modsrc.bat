@echo off

:: This scripts copies needed (changed) files from ./bme_scripts/ to ./r1_modsrc/scripts/

:: GIT COPY START

set R1_MODSRC_DIR=%cd%/r1_modsrc
set BME_SCRIPTS_DIR=%cd%/bme_scripts
setlocal enableextensions
set startdir=%cd%
dir /b /s /a "%BME_SCRIPTS_DIR%" | findstr .>NUL 2>&1 || (
    echo Specified directory does not exist!
    echo You forgot to clone the git submodules. Go rethink your life man.
    echo.
    pause
    goto end
)

set COPY_DIR=%R1_MODSRC_DIR%\scripts\
IF NOT EXIST "%COPY_DIR%" MKDIR "%COPY_DIR%"

:: GIT COMMIT HASH ::
set gitcommit=57571b33e2fcea954dd3cd0502281986ce7471d0

:: COPY ::
cd %BME_SCRIPTS_DIR%
git diff --name-only %gitcommit% > %temp%\difftemp.txt
git ls-files --others --exclude-standard >> %temp%\difftemp.txt
for /F "tokens=*" %%A in (%temp%\difftemp.txt) do call :resources_copy %%A
goto :cont
:resources_copy
set a=%1
set a=%a:/=\%
xcopy /Y "%BME_SCRIPTS_DIR%\%a%" "%COPY_DIR%%a%*"
goto :EOF

:cont
erase "%temp%\difftemp.txt"
cd %startdir%
:: GIT COPY END

:end
