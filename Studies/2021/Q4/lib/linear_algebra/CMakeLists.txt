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

# Library tests
set(TEST_DIR ${DIR}/test)
enable_testing()
find_package(GTest REQUIRED)

set(TEST_TARGET_NAME ${LIB_NAME}tests)
set(TEST_SOURCE_FILES
    ${TEST_DIR}/power_unittest.cc
    ${TEST_DIR}/util_unittest.cc
)
add_executable(${TEST_TARGET_NAME} ${TEST_SOURCE_FILES})
target_include_directories(${TEST_TARGET_NAME} PRIVATE ${INC_DIR})
target_link_libraries(${TEST_TARGET_NAME} GTest::GTest GTest::Main ${LIB_NAME})