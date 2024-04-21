cmake_minimum_required(VERSION 3.10)
project(Spotigator)

# Add C++11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2 # if you run into issues, try updating your editor or downgrading to a lower version of catch v3
)
FetchContent_MakeAvailable(Catch2)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Add your source files
file(GLOB SOURCES src/*.cpp)

# Create executable
add_executable(Spotigator ${SOURCES})
target_link_libraries(Spotigator PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_compile_features(Spotigator PRIVATE cxx_std_17)

add_executable(Tests
        test/test.cpp # your test file
    )

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)




include(CTest)
include(Catch)
catch_discover_tests(Tests)