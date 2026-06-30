################################################################################
# LuxRegni Root CMakeLists.txt
################################################################################

cmake_minimum_required(VERSION 3.16)

project(LuxRegni VERSION 1.0.0 LANGUAGES CXX C)

# Build options
option(BUILD_WASM_CLIENT "Build WASM client" ON)
option(BUILD_WASM_SERVER "Build WASM server" ON)
option(BUILD_UE5_PLUGIN "Build UE5 plugin" OFF)
option(BUILD_GODOT_PLUGIN "Build Godot plugin" OFF)
option(BUILD_ASCII_ADVENTURE "Build Ascii Adventure" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

################################################################################
# Third-party
################################################################################

add_subdirectory(ThirdParty/wren)
add_subdirectory(ThirdParty/sqlite3)


# Utility modules
add_subdirectory(ThirdParty/nlohmann)

################################################################################
# Core Modules
################################################################################
add_subdirectory(Modules/IDMTemplates)
add_subdirectory(Modules/IDMCore)

################################################################################
# Data Modules (Regni)
################################################################################


add_subdirectory(Modules/Universe)
add_subdirectory(Modules/World)
add_subdirectory(Modules/Region)
add_subdirectory(Modules/Place)

add_subdirectory(Modules/Character)
add_subdirectory(Modules/Object)
add_subdirectory(Modules/Item)


################################################################################
# Game Instance/Binding Layer
################################################################################

add_subdirectory(Modules/RegniByte)
add_subdirectory(Modules/Regnum)


################################################################################
# LuxRegni Core Library (bundles everything)
################################################################################

add_library(LuxRegni STATIC
    $<TARGET_OBJECTS:IDMTemplates>
    $<TARGET_OBJECTS:IDMCore>
    $<TARGET_OBJECTS:Universe>
    $<TARGET_OBJECTS:World>
    $<TARGET_OBJECTS:Region>
    $<TARGET_OBJECTS:Place>
    $<TARGET_OBJECTS:Character>
    $<TARGET_OBJECTS:Object>
    $<TARGET_OBJECTS:Item>
    $<TARGET_OBJECTS:Regnum>
    $<TARGET_OBJECTS:RegniByte>
)

target_include_directories(LuxRegni PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/sqlite3
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/nlohmann
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/wren

    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/IDMCore/Public

    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/IDMTemplates/Public
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Universe/Public
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/World/Public
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Region/Public
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Place/Public
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Character/Public
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Object/Public
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Item/Public
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Regnum/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Regnum/Commands

    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/RegniByte/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/Modules/RegniByte/Editors
)

target_link_libraries(LuxRegni PUBLIC sqlite3 wren_cpp JSON m)

if(EMSCRIPTEN)
    target_compile_options(LuxRegni PUBLIC "SHELL:--bind")
    target_link_options(LuxRegni PUBLIC "SHELL:--bind")
endif()

################################################################################
# Targets (Temporalis)
################################################################################

if(BUILD_WASM_CLIENT OR EMSCRIPTEN)
    add_subdirectory(Targets/wasm_client)
endif()

if(BUILD_WASM_SERVER OR EMSCRIPTEN)
    add_subdirectory(Targets/wasm_server)
endif()

if(BUILD_UE5_PLUGIN)
    add_subdirectory(Targets/UE5)
endif()

if(BUILD_GODOT_PLUGIN)
    add_subdirectory(Targets/Godot)
endif()

if(BUILD_ASCII_ADVENTURE)
    add_subdirectory(Targets/AsciiAdventure)
endif()
message(STATUS "")
message(STATUS "=== LuxRegni Build Configuration ===")
message(STATUS "WASM Client:      ${BUILD_WASM_CLIENT}")
message(STATUS "WASM Server:      ${BUILD_WASM_SERVER}")
message(STATUS "UE5 Plugin:       ${BUILD_UE5_PLUGIN}")
message(STATUS "Godot Plugin:     ${BUILD_GODOT_PLUGIN}")
message(STATUS "ASCII Adventure:  ${BUILD_ASCII_ADVENTURE}")
message(STATUS "=====================================")
message(STATUS "")
