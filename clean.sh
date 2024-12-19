#!/bin/bash

# Define directories and files to clean
BUILD_DIR="build"
CACHE_FILES=("CMakeCache.txt" "compile_commands.json" "CMakeFiles" "*.o" "*.so" "*.a" "*.log", "rleix_*.tar.gz")
TEMP_FILES=("*~" "*.swp" "*.bak")

echo "Starting cleanup..."

# Remove the build directory
if [ -d "$BUILD_DIR" ]; then
    echo "Removing build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
else
    echo "No build directory found."
fi

# Remove CMake cache and generated files
for file in "${CACHE_FILES[@]}"; do
    echo "Removing $file"
    rm -rf $file
done

# Remove temporary files
for temp in "${TEMP_FILES[@]}"; do
    echo "Removing temporary file pattern: $temp"
    rm -f $temp
done

echo "Cleanup completed!"

