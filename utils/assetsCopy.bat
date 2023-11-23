@echo off

echo Copying asstets

set dirToCopy=%~1
set targetDir=%~2

echo Copying

echo %dirToCopy%
echo %targetDir%

cd "%targetDir%"
mkdir "Assets"
xcopy /y /s /e "%dirToCopy%" "%targetDir%/Assets"

pause
REM cd "$(OutDir)"
REM mkdir "Assets"
REM xcopy /s /e /y "$(SolutionDir)Assets" "$(OutDir)Assets"

echo Assets copied successfully
