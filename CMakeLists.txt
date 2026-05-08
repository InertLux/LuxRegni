cmake_minimum_required(VERSION 3.20)
project(GameBackend VERSION 1.0.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")

# Platform detection
if(WIN32)
    message(STATUS "Platform: Windows")
elseif(APPLE)
    message(STATUS "Platform: macOS")
elseif(ANDROID)
    message(STATUS "Platform: Android")
elseif(UNIX)
    message(STATUS "Platform: Linux")
endif()

# Add source directory
add_subdirectory(src)
