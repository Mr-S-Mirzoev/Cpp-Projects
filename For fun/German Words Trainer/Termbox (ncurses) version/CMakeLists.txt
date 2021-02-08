cmake_minimum_required(VERSION 3.8)

project(languager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Directory settings
set(INC_DIR ${DIR}/inc)
set(GEOMETRY_INC_DIR ${DIR}/inc/geometry)
set(SRC_DIR ${DIR}/src)
set(DEP_DIR ${DIR}/lib/usr/include)

# Executable name
set(TARGET_NAME deutsch)

# All the sources to be linked
set(SOURCE_FILES ${SRC_DIR}/main.cpp
                 ${SRC_DIR}/button.cpp
                 ${SRC_DIR}/geometry/point.cpp
                 ${SRC_DIR}/geometry/rectangle.cpp
                 ${SRC_DIR}/geometry/text_rectangle.cpp)

add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Link with pthreads (required by dep/csv_parser.hpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Threads::Threads)

list(APPEND CMAKE_PREFIX_PATH "lib/usr/lib")
find_library(TERMBOX_LIB termbox)
target_link_libraries(${TARGET_NAME} PRIVATE "${TERMBOX_LIB}")

# Include headers and dependencies.
target_include_directories(${TARGET_NAME} PUBLIC ${INC_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${GEOMETRY_INC_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${DEP_DIR})