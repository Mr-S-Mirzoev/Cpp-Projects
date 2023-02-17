#pragma once

#include <exception>
#include <iostream>

using TestException = std::runtime_error;

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

int count = 0;
int asserted = 0;

#define RAISE(err_str)                                                        \
    TestException(std::string( STRINGIZE(err_str) ))

#define ASSERT_EQ(arg1, arg2)                                                 \
    ++count;                                                                  \
    if (arg1 != arg2)                                                         \
        throw RAISE("Test error occured at " __FILE__ ":" LINE_STRING " (" #arg1 " is not equal to " #arg2 ")");

#define ASSERT_TRUE(arg)                                                      \
    ASSERT_EQ(arg, true);

#define ASSERT_FALSE(arg)                                                     \
    ASSERT_EQ(arg, false);

#define EXPECT_EQ(arg1, arg2)                                                 \
    ++count;                                                                  \
    if (arg1 != arg2)                                                         \
    {                                                                         \
        std::cout << "Test error occured at " __FILE__ ":" LINE_STRING " (" #arg1 " is not equal to " #arg2 "):" << std::endl; \
        std::cout << "\"" << (arg1) << "\"" << " != " << "\"" << (arg2) << "\"" << std::endl;                                  \
        ++asserted;                                                           \
    }

#define UNIT_TEST_BEGIN(test_suite, test_name)                                \
    std::cout << "[ RUN      ] " #test_suite "." #test_name << std::endl;     \
    try                                                                       \
    {

#define UNIT_TEST_END(test_suite, test_name)                                  \
        std::cout << "[       OK ] " #test_suite "." #test_name << std::endl; \
    }                                                                         \
    catch (TestException e)                                                   \
    {                                                                         \
        std::cout << "[  FAILED  ] " #test_suite "." #test_name << std::endl; \
    }

#define EXPECT_TRUE(arg)                                                      \
    EXPECT_EQ(arg, true);

#define EXPECT_FALSE(arg)                                                     \
    EXPECT_EQ(arg, false);

#define TEST_MAIN_BEGIN()                                                     \
    int main(int argc, char const *argv[])                                    \
    {                                                                         \
        try                                                                   \
        {

#define TEST_MAIN_END()                                                       \
            std::cout << count - asserted << " checks SUCCEED out of " << count << std::endl; \
        }                                                                     \
        catch (TestException e)                                               \
        {                                                                     \
            std::cout << e.what() << std::endl;                               \
        }                                                                     \
    }