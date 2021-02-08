cmake_minimum_required(VERSION 3.8)

project(leetcode VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${DIR}/algorithms)
add_subdirectory(${DIR}/concurency)
