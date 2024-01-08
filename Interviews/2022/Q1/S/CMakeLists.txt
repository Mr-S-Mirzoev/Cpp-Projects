cmake_minimum_required(VERSION 3.14)

# Set the project name and version
project(OptimalRootTests VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Get all the source files in the `src` directory matching the pattern *.cc
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cc")

# Build the library
add_library(
    root_finder
    ${SOURCES}
)

# Include the headers
target_include_directories(
    root_finder
    PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
)

# Add the executable for the test
add_executable(
    optimal_root_test
    test.cc
)

# Link against gtest_main
target_link_libraries(
    optimal_root_test
    gtest_main
    root_finder
)

include(GoogleTest)
gtest_discover_tests(optimal_root_test)
