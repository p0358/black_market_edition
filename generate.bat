@echo off

:: This generates Visual Studio projects for building the C++ parts.

git submodule update --init
powershell -ExecutionPolicy Bypass -Command "scripts\get-premake.ps1 5.0.0-beta7"
premake\premake5 vs2022 %*
