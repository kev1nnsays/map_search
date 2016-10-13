#!/bin/bash
SCRIPT="auto_build_and_exe"

mkdir -p build
cd build

#Build the source code
echo [$SCRIPT] "Executing CMake..."
cmake ..

echo [$SCRIPT] "Executing make..."
make

cd ..
