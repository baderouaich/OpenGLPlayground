::Generates Visual Studio 2019 Project using premake5::
@echo off
call .\Premake\Windows\premake5.exe --file=premake5.lua vs2019 
IF %ERRORLEVEL% NEQ 0 (PAUSE)