#!/bin/bash

# Define directories and files to clean
BUILD_DIR="build"
CACHE_DIR=".cache"
DEPS_DIR="_deps"
RCMD_CHECK_DIR="relix.Rcheck"

CACHE_FILES=("CMakeCache.txt" "cmake_install.cmake" "compile_commands.json" "CMakeFiles" "*.o" "*.so" "*.a" "*.log" "relix_*.tar.gz")
TEMP_FILES=("*~" "*.swp" "*.bak")

echo "Starting cleanup..."

if [ -d "$CACHE_DIR" ]; then
	echo "Removing cache directory: $CACHE_DIR"
	rm -rf "$CACHE_DIR"
else
	echo "No cache directory found."
fi

if [ -d "$BUILD_DIR" ]; then
	echo "Removing build directory: $BUILD_DIR"
	rm -rf "$BUILD_DIR"
else
	echo "No build directory found."
fi

if [ -d "$DEPS_DIR" ]; then
	echo "Removing deps directory: $DEPS_DIR"
	rm -rf "$DEPS_DIR"
else
	echo "No deps directory found."
fi

if [ -d "$RCMD_CHECK_DIR" ]; then
	echo "Removing r cmd check directory: $RCMD_CHECK_DIR"
	rm -rf "$RCMD_CHECK_DIR"
else
	echo "No r cmd check directory found."
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

