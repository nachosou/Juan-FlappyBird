@echo off

echo Copying asstets

xcopy /y /i /s "$(ProjectDir)Assets" "$(OutDir)Assets"

echo Assets copied successfully
