################################################################################
# SQLite3 Static Library
################################################################################

add_library(sqlite3 STATIC
    sqlite3.c
)

target_include_directories(sqlite3 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Optimize for WASM if building for Emscripten
if(EMSCRIPTEN)
    target_compile_options(sqlite3 PRIVATE -O3 -Oz)
endif()

# Standard optimizations
target_compile_options(sqlite3 PRIVATE -O3)

# Suppress warnings from third-party code
target_compile_options(sqlite3 PRIVATE -w)
