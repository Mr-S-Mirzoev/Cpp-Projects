cmake_minimum_required(VERSION 3.8)

project(deutsch VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Directory settings
set(INC_DIR ${DIR}/inc)
set(SRC_DIR ${DIR}/src)
set(DEP_DIR ${DIR}/dep)

# Executable name
set(TARGET_NAME deutsch)

# All the sources to be linked
set(SOURCE_FILES ${SRC_DIR}/deutsch.cpp
                 ${SRC_DIR}/database.cpp
		 ${SRC_DIR}/exceptions.cpp
		 ${SRC_DIR}/utilities.cpp
                 ${SRC_DIR}/training.cpp
                 ${SRC_DIR}/classic_training.cpp
                 ${SRC_DIR}/runner.cpp
                 ${SRC_DIR}/word.cpp)

add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Link with pthreads (required by dep/csv_parser.hpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Threads::Threads)

# Include headers and dependencies.
target_include_directories(${TARGET_NAME} PUBLIC ${INC_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${DEP_DIR})
