cmake_minimum_required(VERSION 3.9)

# Project setup
set(LIB_NAME linalg)
project(
    ${LIB_NAME} 
    VERSION 1.0.1 
    DESCRIPTION "Linear Algebra support" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Directory settings
set(INC_DIR ${DIR}/inc)
set(SRC_DIR ${DIR}/src)

# All the sources to be linked
set(SOURCE_FILES 
    ${SRC_DIR}/matrix.cpp
)

add_library(${LIB_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${LIB_NAME} PUBLIC ${INC_DIR})