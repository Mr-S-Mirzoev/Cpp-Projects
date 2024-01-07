#pragma once

#include <string_view>
#include <vector>

enum class RequestType : int
{
    Deposit,
    Withdrawal,
    Transfer,
    Invalid
};

bool handle_request(std::vector<int>& balances, std::string_view request);
