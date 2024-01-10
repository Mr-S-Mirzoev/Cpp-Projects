# Define the test executable
add_executable(test_executable unittest.cpp)

# Link the test executable against the Google Test library
target_link_libraries(test_executable gtest_main)

# Add the solution include directory to the test executable
target_include_directories(test_executable PRIVATE ${CMAKE_SOURCE_DIR})

# Define a test for CTest to run
add_test(
    NAME GoogleTestBasedTest
    COMMAND test_executable
)
