
cmake_minimum_required(VERSION 3.21)
project(UdeAStay VERSION 0.001 LANGUAGES CXX)

# Set the build type to Release by default
include(CTest)
enable_testing()


# Add the executable
add_executable(UdeAStay src/main.cpp src/Utils/ConUtils.cpp src/Actors/accommodation.cpp src/Actors/reservation.cpp src/Actors/guest.cpp src/Actors/host.cpp)

# Set the C++ standard to C++20
set_property(TARGET UdeAStay PROPERTY CXX_STANDARD 20)
