################################################################################
# ASCII Adventure Target (Linux Native)
################################################################################

add_executable(ascii_adventure
    Private/main.cpp
)

target_include_directories(ascii_adventure PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Private
)
target_link_libraries(ascii_adventure PRIVATE
    LuxRegni
)

# Set output directory for the executable
set_target_properties(ascii_adventure PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/RegniByte"
)


# Installation
install(TARGETS ascii_adventure DESTINATION bin/RegniByte)

message(STATUS "[ASCII Adventure] Configured for Linux")
