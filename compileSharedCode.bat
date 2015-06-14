@echo off
haxe lime-shared.hxml
if %ERRORLEVEL% neq 0 (
	exit /b
)
copy /b lime-shared.hxml+lime-shared.hxml.part lime-export.hxml
haxe lime-export.hxml