#include <array>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "string_conv.h" // Assuming the int_from_chars function is declared in this header

enum class RequestType : int
{
    Deposit,
    Withdrawal,
    Transfer,
    Invalid
};

// Consider matching programmatically
RequestType get_request_type(std::string_view request)
{
    if (request == "deposit")
        return RequestType::Deposit;

    if (request == "withdraw")
        return RequestType::Withdrawal;

    if (request == "transfer")
        return RequestType::Transfer;

    return RequestType::Invalid;
}

bool is_valid_account(std::vector<int>& balances, int account_id)
{
    return account_id >= 1 && account_id <= balances.size();
}

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

std::vector<int> solution(std::vector<int> balances, std::vector<std::string> requests)
{
    // Max number of tokens in request string
    constexpr int MAX_TOKENS_COUNT = 4;

    for (int request_id = 1; request_id <= requests.size(); ++request_id)
    {
        std::string_view request = requests[request_id - 1];

        // process request string
        std::array<std::string_view, MAX_TOKENS_COUNT> tokens;
        std::size_t tokens_count = 0;
        std::size_t pos = 0;
        while (pos != std::string_view::npos && tokens_count < MAX_TOKENS_COUNT)
        {
            std::size_t new_pos = request.find(' ', pos);
            tokens[tokens_count++] = request.substr(pos, new_pos - pos);

            pos = (new_pos == std::string_view::npos) ? new_pos : new_pos + 1;
        }

        // minimal count of tokens in a string is 3
        if (tokens_count < 3)
            return {-request_id};

        RequestType req_type = get_request_type(tokens[0]);
        if (req_type == RequestType::Invalid)
            return {-request_id};

        // if there are 4 tokens, but request type isn't transfer
        if ((tokens_count == MAX_TOKENS_COUNT) ^ (req_type == RequestType::Transfer))
            return {-request_id};

        int account, account_to, amount;
        // since std::from_chars wasn't available in codesignal
        if (!int_from_chars(tokens[1], account))
            return {-request_id};

        switch (req_type)
        {
        case RequestType::Deposit:
        {
            if (!int_from_chars(tokens[2], amount))
                return {-request_id};

            if (!handle_deposit(balances, account, amount))
                return {-request_id};

            break;
        }

        case RequestType::Transfer:
        {
            if (!int_from_chars(tokens[2], account_to))
                return {-request_id};

            if (!int_from_chars(tokens[3], amount))
                return {-request_id};

            if (!handle_transfer(balances, account, account_to, amount))
                return {-request_id};

            break;
        }

        case RequestType::Withdrawal:
        {
            if (!int_from_chars(tokens[2], amount))
                return {-request_id};

            if (!handle_withdraw(balances, account, amount))
                return {-request_id};

            break;
        }
        }
    }

    return balances;
}
