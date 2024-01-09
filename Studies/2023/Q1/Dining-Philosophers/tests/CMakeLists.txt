# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Enable testing and add unit tests
enable_testing()
add_executable(unit_tests unittest/unittest.cpp)
target_link_libraries(unit_tests gtest_main philosophers_lib)
include(GoogleTest)
gtest_discover_tests(unit_tests)
