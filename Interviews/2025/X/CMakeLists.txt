cmake_minimum_required(VERSION 3.10)
project(XantiumTask LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(queue queue.cpp)

add_executable(encoder encoding.cpp)

target_link_libraries(queue PRIVATE pthread)
