cmake_minimum_required(VERSION 3.9)

# Project setup
set(TARGET_NAME prac2021)
project(
    ${TARGET_NAME} 
    VERSION 1.0.1 
    DESCRIPTION "Practicum 2021" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Directory settings
set(INC_DIR ${DIR}/inc)
set(SRC_DIR ${DIR}/src)
set(LIB_DIR ${DIR}/lib/linear_algebra)

# All the sources to be linked
set(SOURCE_FILES 
    ${SRC_DIR}/main.cc
)

add_subdirectory(${LIB_DIR})
add_executable(${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries(${TARGET_NAME} PUBLIC linalg)
target_include_directories(${TARGET_NAME} PUBLIC ${INC_DIR})