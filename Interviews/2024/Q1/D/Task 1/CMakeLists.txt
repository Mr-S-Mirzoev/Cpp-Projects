# Define the test executable
add_executable(sparse_vector_test unittest.cpp)

# Link the test executable against the Google Test library
target_link_libraries(sparse_vector_test gtest_main)

# Add the solution include directory to the test executable
target_include_directories(sparse_vector_test PRIVATE ${CMAKE_SOURCE_DIR})

# Define a test for CTest to run
add_test(
    NAME GoogleTestBasedTest
    COMMAND sparse_vector_test
)
