cmake_minimum_required(VERSION 3.8)

project(beautiful_numbers VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Directory settings
set(INC_DIR ${DIR}/inc)
set(SRC_DIR ${DIR}/src)
set(TEST_DIR ${DIR}/tests)

# Executable name
set(LIBRARY_NAME beautynumbers_support)

# All the sources to be linked
set(SOURCE_FILES
    ${SRC_DIR}/digit.cpp
    ${SRC_DIR}/factorial.cpp
    ${SRC_DIR}/permutations.cpp
    ${SRC_DIR}/quantity_by_sum.cpp
)

# Create a library from the source files
add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES})

# Include headers and dependencies with library.
target_include_directories(${LIBRARY_NAME} PUBLIC ${INC_DIR})

# Executable name
set(TARGET_NAME ${CMAKE_PROJECT_NAME})

set(SOURCE_FILES
    ${SRC_DIR}/solution.cpp
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Link executable with library
target_link_libraries(${TARGET_NAME} ${LIBRARY_NAME})

add_subdirectory(${TEST_DIR})