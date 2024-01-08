#include "request.h"

#include "account.h"
// the need for a custom implementation occured due to the fact that std::from_chars wasn't
// available in codesignal
#include "string_conv.h"

#include <array>

#if USE_HASH_TABLE_FOR_REQUEST_TYPE
#include <unordered_map>
#endif

static constexpr int MAX_TOKENS_COUNT = 4;

#if USE_HASH_TABLE_FOR_REQUEST_TYPE
RequestType get_request_type(std::string_view request)
{
    static const std::unordered_map<std::string_view, RequestType> requestTypeMap = {
        {"deposit", RequestType::Deposit},
        {"withdraw", RequestType::Withdrawal},
        {"transfer", RequestType::Transfer}};

    auto it = requestTypeMap.find(request);
    return (it != requestTypeMap.end()) ? it->second : RequestType::Invalid;
}
#else
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
#endif

void parse_request(std::string_view request, std::array<std::string_view, MAX_TOKENS_COUNT>& tokens,
                   std::size_t& tokens_count)
{
    std::size_t pos = 0;
    while (pos != std::string_view::npos && tokens_count < MAX_TOKENS_COUNT)
    {
        std::size_t new_pos = request.find(' ', pos);
        tokens[tokens_count++] = request.substr(pos, new_pos - pos);

        pos = (new_pos == std::string_view::npos) ? new_pos : new_pos + 1;
    }
}

bool handle_parsed_request(std::vector<int>& balances,
                           const std::array<std::string_view, MAX_TOKENS_COUNT>& tokens,
                           std::size_t tokens_count)
{
    int account, account_to, amount;
    if (!int_from_chars(tokens[1], account))
        return false;

    RequestType req_type = get_request_type(tokens[0]);
    if (req_type == RequestType::Invalid)
        return false;

    // if there are 4 tokens, but request type isn't transfer
    if ((tokens_count == MAX_TOKENS_COUNT) ^ (req_type == RequestType::Transfer))
        return false;

    switch (req_type)
    {
    case RequestType::Deposit:
    {
        if (!int_from_chars(tokens[2], amount))
            return false;

        if (!handle_deposit(balances, account, amount))
            return false;

        break;
    }

    case RequestType::Transfer:
    {
        if (!int_from_chars(tokens[2], account_to))
            return false;

        if (!int_from_chars(tokens[3], amount))
            return false;

        if (!handle_transfer(balances, account, account_to, amount))
            return false;

        break;
    }

    case RequestType::Withdrawal:
    {
        if (!int_from_chars(tokens[2], amount))
            return false;

        if (!handle_withdraw(balances, account, amount))
            return false;

        break;
    }

    default:
        return false;
    }

    return true;
}

bool handle_request(std::vector<int>& balances, std::string_view request)
{
    // process request string
    std::array<std::string_view, MAX_TOKENS_COUNT> tokens;
    std::size_t tokens_count = 0;
    parse_request(request, tokens, tokens_count);

    // minimal count of tokens in a string is 3
    if (tokens_count < 3)
        return false;

    RequestType req_type = get_request_type(tokens[0]);
    if (req_type == RequestType::Invalid)
        return false;

    // if there are 4 tokens, but request type isn't transfer
    if ((tokens_count == MAX_TOKENS_COUNT) ^ (req_type == RequestType::Transfer))
        return false;

    return handle_parsed_request(balances, tokens, tokens_count);
}