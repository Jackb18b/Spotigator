cmake_minimum_required(VERSION 3.10)
project(Spotigator)

# Add C++11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add your source files
file(GLOB SOURCES src/main.cpp src/Song.cpp src/CountryTable.cpp)

# Create executable
add_executable(Spotigator ${SOURCES})
