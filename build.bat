@ECHO OFF
SETLOCAL EnableDelayedExpansion

WHERE cl >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
)

REM Create folders if not exist
IF NOT EXIST ..\Bin MKDIR ..\Bin
IF NOT EXIST ..\Bin\App MKDIR ..\Bin\App
IF NOT EXIST ..\Bin\Intermediate MKDIR ..\Bin\Intermediate

REM Set paths
SET ExeName=WAVSimilarity
SET ExePath=..\Bin\App\%ExeName%

SET PDBFiles=..\Bin\App\
SET IntermediatePath=..\Bin\Intermediate\

REM Delete files from paths
DEL /Q /S %IntermediatePath%*.* 1>NUL
DEL /Q %PDBFiles%*.pdb 2>NUL

DEL /Q %PDBFiles%*.Exe 2>NUL
DEL /Q %PDBFiles%*.ilk 2>NUL

REM Compiler flags
SET CommonCompilerFlags= /nologo /MP /O2 /MT /Z7 /EHsc /Fd%PDBFiles% /Fo%IntermediatePath% /Fe%ExePath%
SET CommonLinkerFlags= /nologo /incremental:no /opt:ref
SET Defines= /DWIN32 /DNDENUG

REM Get all cpp files
SET CPPFiles=
FOR /R . %%i IN (*.cpp) DO SET CPPFiles=!CPPFiles! %%~i

REM Compile
call cl %CommonCompilerFlags% %Defines% %CPPFiles% /link %CommonLinkerFlags%
