# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(TestMultithreaded VERSION 1.0.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an option to run tests with test_runner.py
option(RUN_TESTS "Run tests with test_runner.py" OFF)

# Find all the test source files
file(GLOB TEST_SOURCES "*.tests.cpp")

# Create a target for each test source file
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Get the base name of the test source file
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    # Create the test target
    add_executable(${TEST_NAME}_test ${TEST_SOURCE})

    # Add the test target to the tests target
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME}_test)

    # Optionally run the tests with test_runner.py
    if(RUN_TESTS)
        add_custom_target(run_${TEST_NAME}_test
            COMMAND python test_runner.py -t ${TEST_NAME} -d ${CMAKE_BINARY_DIR} -n 1000
            DEPENDS ${TEST_NAME}_test
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()
endforeach()
