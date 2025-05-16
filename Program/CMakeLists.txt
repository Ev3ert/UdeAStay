
cmake_minimum_required(VERSION 3.21)
project(UdeAStay VERSION 0.001 LANGUAGES CXX)

# Set the build type to Release by default
include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion")

# Add the executable
add_executable(UdeAStay src/main.cpp)

# Set the C++ standard to C++20
set_property(TARGET UdeAStay PROPERTY CXX_STANDARD 20)
