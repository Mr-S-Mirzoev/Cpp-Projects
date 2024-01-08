#include "solution.h"
#include "string_conv.h"
#include <gtest/gtest.h>

// Test fixture for bank bot tests
class BankBotTest : public ::testing::Test
{
protected:
    std::vector<int> balances;
    std::vector<std::string> requests;

    // Reset the bank balances and requests before each test
    void SetUp() override
    {
        balances.clear();
        requests.clear();
    }
};

TEST_F(BankBotTest, HandlesEmptyRequests)
{
    balances = {100, 200, 300};

    auto result = solution(balances, requests);
    auto expected = std::vector<int>({100, 200, 300});

    EXPECT_EQ(result, balances);
}

TEST_F(BankBotTest, ProcessesSingleDeposit)
{
    balances = {100, 200, 300};
    requests = {"deposit 1 50"};

    auto result = solution(balances, requests);
    auto expected = std::vector<int>({150, 200, 300});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, ProcessesSingleWithdrawal)
{
    balances = {100, 200, 300};
    requests = {"withdraw 2 50"};

    auto result = solution(balances, requests);
    auto expected = std::vector<int>({100, 150, 300});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, ProcessesSingleTransfer)
{
    balances = {100, 200, 300};
    requests = {"transfer 1 3 50"};

    auto result = solution(balances, requests);
    auto expected = std::vector<int>({50, 200, 350});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, HandlesInvalidAccount)
{
    balances = {100, 200, 300};
    requests = {"transfer 4 1 50"};

    auto result = solution(balances, requests);
    const int first_invalid_request_id = 1;
    auto expected = std::vector<int>({-first_invalid_request_id});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, HandlesInsufficientFunds)
{
    balances = {100, 200, 300};
    requests = {"withdraw 1 150"};

    auto result = solution(balances, requests);
    const int first_invalid_request_id = 1;
    auto expected = std::vector<int>({-first_invalid_request_id});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, ProcessesMultipleValidRequests)
{
    balances = {100, 200, 300};
    // clang-format off
    requests = {
        "deposit 1 50",
        "withdraw 2 50",
        "transfer 1 3 50"
    };
    // clang-format on

    auto result = solution(balances, requests);
    auto expected = std::vector<int>({100, 150, 350});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, StopsAtFirstInvalidRequest)
{
    balances = {100, 200, 300};
    // clang-format off
    requests = {
        "deposit 1 50",
        "withdraw 2 250",
        "transfer 1 3 50"
    };
    // clang-format on

    auto result = solution(balances, requests);
    const int first_invalid_request_id = 2;
    auto expected = std::vector<int>({-first_invalid_request_id});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, HandlesWithdrawalToZero)
{
    balances = {50, 200, 300};
    requests = {"withdraw 1 50"};

    auto result = solution(balances, requests);
    auto expected = std::vector<int>({0, 200, 300});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, HandlesAllInvalidRequests)
{
    balances = {10, 20, 30};
    // clang-format off
    requests = {
        "withdraw 1 20",
        "withdraw 2 30",
        "withdraw 3 40"
    };
    // clang-format on

    auto result = solution(balances, requests);
    const int first_invalid_request_id = 1;
    auto expected = std::vector<int>({-first_invalid_request_id});

    EXPECT_EQ(result, expected);
}

TEST_F(BankBotTest, IntFromCharsTest)
{
    int result;
    bool is_input_valid;

    is_input_valid = int_from_chars("123", result);
    EXPECT_TRUE(is_input_valid);
    EXPECT_EQ(result, 123);

    is_input_valid = int_from_chars("-456", result);
    EXPECT_TRUE(is_input_valid);
    EXPECT_EQ(result, -456);

    is_input_valid = int_from_chars("0", result);
    EXPECT_TRUE(is_input_valid);
    EXPECT_EQ(result, 0);

    is_input_valid = int_from_chars("123abc", result);
    EXPECT_FALSE(is_input_valid);
}
