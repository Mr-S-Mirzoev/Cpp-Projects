cmake_minimum_required(VERSION 3.8)

project(command-design-pattern VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Directory settings
set(INC_DIR ${DIR}/inc)
set(SRC_DIR ${DIR}/src)

# Executable name
set(TARGET_NAME command)

# All the sources to be linked
set(SOURCE_FILES 
    ${SRC_DIR}/invoker.cpp
    ${SRC_DIR}/commands.cpp
    ${SRC_DIR}/xmlhandler.cpp
    ${SRC_DIR}/company.cpp
    ${SRC_DIR}/department.cpp
    ${SRC_DIR}/workerinfo.cpp
    ${SRC_DIR}/task2.cpp 
)

add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Include headers and dependencies.
target_include_directories(${TARGET_NAME} PUBLIC ${INC_DIR})
