cmake_minimum_required(VERSION 3.14)

# Set the project name and specify the C++ standard
project(MyProject VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing with CTest
enable_testing()

# Include FetchContent module to fetch external dependencies
include(FetchContent)

# Fetch GoogleTest from GitHub
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# Set the build options for GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# Fetch the content declared above
FetchContent_MakeAvailable(googletest)

# Define the solving library
add_library(solving_library trade_event_utils.cpp)

# Define the main executable
add_executable(main_executable main.cpp)

# Link the main executable with the solving library
target_link_libraries(main_executable solving_library)

# Define the test executable
add_executable(test_executable test.cpp)

# Link the test executable with GoogleTest and the solving library
target_link_libraries(test_executable gtest_main solving_library)

# Define a test for CTest to run
add_test(
    NAME GoogleTestBasedTest
    COMMAND test_executable
)
