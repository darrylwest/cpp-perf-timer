# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name
project(PerfTimer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(perf-time src/main.cpp)

# Optionally, you can set the output directory for the executable
set_target_properties(perf-time PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/
)
