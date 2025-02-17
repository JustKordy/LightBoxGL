#!/bin/bash

# Navigate to the project root
cd "$(dirname "$0")/.."

# Ensure build directory exists
if [ ! -d "build" ]; then
    echo "[🔧] Creating build directory..."
    mkdir build
fi

# Run CMake configuration
echo "[🔧] Running CMake Configuration..."
cmake -B build -G "Unix Makefiles"

# Build the project
echo "[🔨] Building Project..."
cmake --build build --config Debug

# Run the executable
echo "[🚀] Running Executable..."
./build/MyProject

# Keep the terminal open after execution
read -p "Press Enter to exit..."
