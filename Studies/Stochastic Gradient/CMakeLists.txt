cmake_minimum_required(VERSION 3.8)

project(leetcode VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(DEP_DIR ${DIR}/dependencies)
set(INC_DIR ${DIR}/include)
set(SRC_DIR ${DIR}/src)

set(BLAZE_DIR ${DEP_DIR}/blaze)

set(LIB_NAME stochastic_gradient)

set(LIB_SOURCES
    src/loss.cpp
    src/optimizer.cpp
    src/set.cpp
)

add_library(${LIB_NAME} SHARED ${LIB_SOURCES})

target_compile_definitions(${LIB_NAME} PUBLIC BLAZE_USE_CPP_THREADS)

target_include_directories(${LIB_NAME} PUBLIC ${BLAZE_DIR})
target_include_directories(${LIB_NAME} PUBLIC ${INC_DIR})

set(TARGET_NAME test)

set(TEST_SOURCE ${DIR}/main.cpp)

add_executable(${TARGET_NAME} ${TEST_SOURCE})

target_include_directories(${TARGET_NAME} PUBLIC ${BLAZE_DIR}) 