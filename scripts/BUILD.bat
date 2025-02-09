@echo off
cd ..
echo [🔧] Running CMake Configuration...
cmake -B build -G "Visual Studio 17 2022"

echo [🔨] Building Project...
cmake --build build --config Debug

echo [🚀] Running Executable...
cd build/Debug
MyProject.exe

pause
