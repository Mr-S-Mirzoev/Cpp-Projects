cmake_minimum_required(VERSION 3.14)

# Set the project name and version
project(LinkedListTests VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
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

# Add the executable for the test
add_executable(
    linked_list_test
    linked_list_impl.hpp linked_list.hpp
    printable_vector.hpp printable.hpp
    algorithms.hpp
    test.cc
)

# Link against gtest_main
target_link_libraries(
    linked_list_test
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(linked_list_test)
