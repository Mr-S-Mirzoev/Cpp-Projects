cmake_minimum_required(VERSION 3.8)

project(external_sort VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

set(INCLUDE_DIR ${DIR}/inc)
set(SOURCE_DIR ${DIR}/src)

set(SOURCE_FILES
    ${SOURCE_DIR}/external_sort.cc
    ${SOURCE_DIR}/sort.cc
    ${SOURCE_DIR}/c_file.cc
)

set(TARGET_NAME ${CMAKE_PROJECT_NAME})

# Create an executable from the source files
add_executable(${TARGET_NAME} ${SOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDE_DIR})

