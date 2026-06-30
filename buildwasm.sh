#!/bin/bash
EMSDK_PATH=/home/user/Lib/emsdk/  # Set your Emscripten path here


cmake -B build \
  -DCMAKE_TOOLCHAIN_FILE=${EMSDK_PATH}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake \
  -DCMAKE_BUILD_TYPE=Release
cd build && make
