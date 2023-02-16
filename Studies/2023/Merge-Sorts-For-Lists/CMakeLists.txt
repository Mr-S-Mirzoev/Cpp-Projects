cmake_minimum_required(VERSION 3.1)


project(
    LinkedList
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Adding something we can run - Output name matches target name
add_executable(
    ll_test
    linked_list_impl.hpp linked_list.hpp
    printable_vector.hpp printable.hpp
    algorithms.hpp
    test.cpp)
