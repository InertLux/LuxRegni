################################################################################
# WASM Server Target (Node.js/Server-side)
################################################################################

if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "WASM server target requires Emscripten")
endif()


add_executable(luxregni_server
    Private/main.cpp
    Private/DataBase.cpp
    Private/DataManager.cpp
)

target_include_directories(luxregni_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

target_link_libraries(luxregni_server PUBLIC 
    LuxRegni
    sqlite3
)

target_link_options(luxregni_server PRIVATE
    "SHELL:-s WASM=1"
    "SHELL:-s ALLOW_MEMORY_GROWTH=1"
    "SHELL:-s NODERAWFS=1"
    "SHELL:-s EXPORTED_FUNCTIONS=['_malloc','_free']"
)

target_compile_options(luxregni_server PRIVATE
    -std=c++17
    -O3
)

