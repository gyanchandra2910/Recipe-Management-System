@echo off
echo Compiling Recipe Management System...
.\mingw64\bin\g++.exe -std=c++14 main.cpp defs.cpp utility.cpp -I"C:\Program Files\MySQL\MySQL Server 8.0\include" "C:\Program Files\MySQL\MySQL Server 8.0\lib\libmysql.lib" -o RecipeApp.exe

if %errorlevel% neq 0 (
    echo Compilation failed!
) else (
    echo Compilation successful! Run RecipeApp.exe to start the program.
)
pause
