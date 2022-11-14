@ECHO OFF

IF "%~1" == "" GOTO :EmptyPackageNameLabel

cd ..
mkdir packages 2>nul
cd packages
mkdir windows 2>nul
cd windows
mkdir %~1
cd %~1

REM Deletes all files in the package folder, recursively.
del /S /Q *
REM Deletes all empty folders.
robocopy . . /S /MOVE

REM Copy all relevant game files.
set GAMEDIR=..\..\..
robocopy %GAMEDIR%\bin\data hexterminate\data /e
copy %GAMEDIR%\bin\hexterminate.exe hexterminate\hexterminate.exe

REM Copy the symbols!
mkdir symbols 2>nul
copy %GAMEDIR%\bin\hexterminate.pdb symbols\hexterminate.pdb

cd "%~dp0"
GOTO :End

:EmptyPackageNameLabel
echo "Usage: createpackage.bat <packagename>"

:End