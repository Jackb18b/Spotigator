cmake_minimum_required(VERSION 3.10)
project(Spotigator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Add C++11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include(FetchContent)
# FetchContent_Declare(
#         Catch2
#         GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#         GIT_TAG        v3.5.2 # if you run into issues, try updating your editor or downgrading to a lower version of catch v3
# )
# FetchContent_MakeAvailable(Catch2)

Include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Add your source files
file(GLOB SOURCES src/*.cpp)

# Create executable
add_executable(Spotigator ${SOURCES})
target_link_libraries(Spotigator sfml-graphics)
target_compile_features(Spotigator PRIVATE cxx_std_17)

# add_executable(Tests
#         test/test.cpp # your test file
#     )

# target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)


if(WIN32)
    add_custom_command(
        TARGET Spotigator
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Spotigator>
        VERBATIM)
endif()




# include(CTest)
# include(Catch)
# catch_discover_tests(Tests)