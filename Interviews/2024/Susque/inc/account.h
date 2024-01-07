#pragma once

#include <vector>

constexpr inline bool is_valid_account(const std::vector<int>& balances, int account_id)
{
    return account_id >= 1 && account_id <= balances.size();
}

bool handle_deposit(std::vector<int>& balances, int account_id, int sum);
bool handle_withdraw(std::vector<int>& balances, int account_id, int sum);
bool handle_transfer(std::vector<int>& balances, int src_id, int dest_id, int sum);
