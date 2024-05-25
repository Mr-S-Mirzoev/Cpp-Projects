# CMakeLists that compiles g.cpp into an executable g.
# It must show all the compilation warnings and errors possible, and it must be compiled under C++20.
# The executable must be placed in the bin directory.

cmake_minimum_required(VERSION 3.20)

project(ydas24 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function (add_executable_custom target)
    add_executable(${target} ${target}.cpp)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Werror)
    # build in debug mode
    target_compile_options(${target} PRIVATE -g)
endfunction(add_executable_custom)

add_executable_custom(g)
add_executable_custom(h)
