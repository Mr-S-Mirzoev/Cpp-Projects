cmake_minimum_required(VERSION 3.8)

project(leetcode VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(SRC_DIR ${DIR}/src)
set(INC_DIR ${DIR}/inc)

# Find threads package to link with -pthread
find_package(Threads)

set(TARGET_NAME task1)

set(SOURCE_FILES 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/reader.cpp
    ${SRC_DIR}/writer.cpp
    ${SRC_DIR}/utils.cpp
)

add_executable(${TARGET_NAME} ${SOURCE_FILES})

target_include_directories(${TARGET_NAME} PRIVATE ${INC_DIR})

# Link with pthread
target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})