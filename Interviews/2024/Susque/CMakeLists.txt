cmake_minimum_required(VERSION 3.14)

# Set the project name and version
project(BankBotTests VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add the executable for the test
add_executable(
  bank_bot_test
  test.cc
)

# Link against gtest_main
target_link_libraries(
  bank_bot_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(bank_bot_test)
