@echo off
pushd %~dp0\..\
call vender\premake\bin\premake5.exe vs2022
popd
PAUSE