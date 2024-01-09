cmake_minimum_required(VERSION 3.14)
project(DiningPhilosophers)

set(CMAKE_CXX_STANDARD 20)

# Create a library 'philosophers_lib'
add_library(philosophers_lib STATIC
    src/philosopher/philosopher.cpp
    src/strategy/mutex_strategy.cpp
    src/table/table.cpp
)

# Include directories for the library
target_include_directories(philosophers_lib PUBLIC src)

# Create executable 'dinner'
add_executable(dinner src/main.cpp)

# Link 'dinner' with 'philosophers_lib'
target_link_libraries(dinner PRIVATE philosophers_lib)

# Build tests
add_subdirectory(tests)
