#!/bin/bash

cd "$(dirname "$0")/.."

if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

brew install glew glfw glm

echo "Running CMake Configuration..."
cmake -B build -G "Unix Makefiles"

echo "Building Project..."
cmake --build build --config Debug

echo "Running Executable..."
./build/MyProject

read -p "Press Enter to exit..."
