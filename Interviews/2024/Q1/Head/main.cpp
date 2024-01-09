#include "trade_event_utils.h"

#include <iostream>

int main()
{
    std::vector<TradeEvent> events{{0, "MSFT", 10, 10}, {1, "MSFT", 9, 12}};
    auto res = get_top_trade_events_by_notional(events, 1);

    std::cout << "Size: " << res.size() << std::endl;
    for (auto& event : res)
    {
        std::cout << event.ticker << event.price << std::endl;
    }
    return 0;
}