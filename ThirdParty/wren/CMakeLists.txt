################################################################################
# Wren C Library
################################################################################

file(GLOB_RECURSE WREN_C_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/vm/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/optional/*.c"
)

add_library(wren_static STATIC ${WREN_C_SOURCES})

target_include_directories(wren_static
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/vm"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/optional"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
)

set_target_properties(wren_static PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    OUTPUT_NAME wren
)

if(MSVC)
    target_compile_options(wren_static PRIVATE /W3)
else()
    target_compile_options(wren_static PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()

################################################################################
# Wren C++ Wrapper
################################################################################

add_library(wren_cpp STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Integration/src/WrenEngine.cpp"
)

target_include_directories(wren_cpp
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Integration/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Integration/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/vm"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/optional"
)

target_link_libraries(wren_cpp PUBLIC wren_static)

set_target_properties(wren_cpp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME wren_cpp
)

if(EMSCRIPTEN)
    target_compile_options(wren_cpp PUBLIC "SHELL:--bind")
    target_link_options(wren_cpp PUBLIC "SHELL:--bind")
endif()

message(STATUS "[Wren] Built wren_static (C) and wren_cpp (C++ wrapper)")
