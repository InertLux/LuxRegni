#!/bin/bash
set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

mkdir -p build
cd build && cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DBUILD_ASCII_ADVENTURE=ON \
  -DBUILD_WASM_CLIENT=OFF \
  -DBUILD_WASM_SERVER=OFF

echo -e "${BLUE}[CMake]${NC} Configuring..."
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_ASCII_ADVENTURE=ON

echo -e "${BLUE}[Build]${NC} Compiling..."
cmake --build . --parallel $(nproc)

if [ -f "./bin/RegniByte/ascii_adventure" ]; then
    echo -e "${GREEN}[Success]${NC} Build complete"
    ./bin/RegniByte/ascii_adventure
else
    echo -e "${RED}[Error]${NC} Binary not found at ./bin/RegniByte/ascii_adventure"
    echo -e "${RED}[Debug]${NC} Checking build artifacts:"
    find . -name "ascii_adventure" -o -name "*.a" -o -name "*.o" 2>/dev/null | head -20
    exit 1
fi
