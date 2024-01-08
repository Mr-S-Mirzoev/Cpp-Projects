#include "account.h"

bool handle_deposit(std::vector<int>& balances, int account_id, int sum)
{
    if (!is_valid_account(balances, account_id))
        return false;

    balances[account_id - 1] += sum;
    return true;
}

bool handle_withdraw(std::vector<int>& balances, int account_id, int sum)
{
    if (!is_valid_account(balances, account_id))
        return false;

    if (balances[account_id - 1] < sum)
        return false;

    balances[account_id - 1] -= sum;
    return true;
}

bool handle_transfer(std::vector<int>& balances, int src_id, int dest_id, int sum)
{
    return handle_withdraw(balances, src_id, sum) && handle_deposit(balances, dest_id, sum);
}
