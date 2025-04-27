#!/bin/bash

# OBSE64 Linux build script
echo "Building OBSE64 for Linux using MinGW..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring project..."
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/mingw-w64.cmake ..

# Build the project
echo "Building project..."
cmake --build . --config Release

if [ $? -eq 0 ]; then
    echo "Build completed successfully!"
    echo ""
    echo "Output files:"
    echo " - DLL: $(pwd)/obse64/libobse64_0_411_140.dll"
    echo " - EXE: $(pwd)/obse64_loader/obse64_loader.exe"
    echo ""
else
    echo "Build failed!"
fi 