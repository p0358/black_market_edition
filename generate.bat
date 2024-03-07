@echo off

:: This generates Visual Studio projects for building the C++ parts.

git submodule update --init
premake\premake5 %* vs2022