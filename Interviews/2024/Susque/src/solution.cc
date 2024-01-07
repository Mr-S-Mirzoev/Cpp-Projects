#include "solution.h"

#include "request.h"

std::vector<int> solution(std::vector<int> balances, std::vector<std::string> requests)
{
    // Max number of tokens in request string
    constexpr int MAX_TOKENS_COUNT = 4;

    for (int request_id = 1; request_id <= requests.size(); ++request_id)
    {
        std::string_view request = requests[request_id - 1];

        if (!handle_request(balances, request))
            return std::vector<int>({-request_id});
    }

    return balances;
}
