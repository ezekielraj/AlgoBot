#!/bin/bash
set -e  # exit on error

export $(grep -v '^#' .env | xargs)

# Check if the first argument is "debug"
if [ "$1" == "debug" ]; then
    echo "Building in Debug mode..."
    BUILD_TYPE="Debug"
else
    echo "Building in Release mode..."
    BUILD_TYPE="Release"
fi

# Clean and create build folder
rm -rf ./build
mkdir build
cd build

# Run CMake with selected build type
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

# Build the project
make -j
echo "Build completed successfully."