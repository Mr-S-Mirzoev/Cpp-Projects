cmake_minimum_required(VERSION 3.8)

project(filesystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Directory settings
set(INC_DIR ${DIR}/inc)
set(SRC_DIR ${DIR}/src)

# Executable name
set(TARGET_NAME filesystem)

# All the sources to be linked
set(SOURCE_FILES 
    ${SRC_DIR}/filesystem.cpp
    ${SRC_DIR}/file.cpp 
    ${SRC_DIR}/clean_file.cpp 
    ${SRC_DIR}/int128_support.cpp 
    ${SRC_DIR}/utilities.cpp 
    ${SRC_DIR}/filesystem_utils.cpp 
)

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Include headers and dependencies.
target_include_directories(${TARGET_NAME} PUBLIC ${INC_DIR})
