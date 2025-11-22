@echo off
echo Saving latest changes...

echo Compiling snake.cpp...
g++ snake.cpp -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -luser32 -lkernel32 -o snake.exe

if %errorlevel% neq 0 (
    echo.
    echo 
    pause
    exit /b
)

echo.
echo ✔ Compilation successful!
echo Running game...
echo.

snake.exe

echo.
pause
