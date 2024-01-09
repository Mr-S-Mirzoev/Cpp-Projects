#include "trade_event.h"

#include <iostream>
#include <set>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <vector>

struct TradeEventWithNotional
{
    TradeEvent event;
    int64_t notional;
};

struct TradeEventWithNotionalCmp
{
    bool operator()(const TradeEventWithNotional& lhs, const TradeEventWithNotional& rhs) const
    {
        return lhs.notional < rhs.notional;
    }
};

TradeLog get_top_trade_events_by_notional(const TradeLog& trade_events, const size_t N)
{
    std::unordered_map<std::string_view, int64_t> used_tickers;
    std::set<TradeEventWithNotional, TradeEventWithNotionalCmp> trades_with_max_notional;

    for (const auto& trade_event : trade_events)
    {
        const int64_t te_notional = int64_t(trade_event.price) * trade_event.volume;
        auto it = used_tickers.find(trade_event.ticker);
        if (it != used_tickers.end())
        {
            if (it->second < te_notional)
            {
                auto container_it = trades_with_max_notional.lower_bound(
                    TradeEventWithNotional{TradeEvent{}, it->second});

                if (container_it == trades_with_max_notional.end())
                    throw std::runtime_error(
                        "Trade we look for is in ticker map but isn't in the container");

                auto place_to_insert_it = trades_with_max_notional.erase(container_it);
                trades_with_max_notional.emplace_hint(place_to_insert_it, trade_event, te_notional);

                it->second = te_notional;
            }

            continue;
        }

        if (trades_with_max_notional.size() < N)
        {
            trades_with_max_notional.emplace(trade_event, te_notional);
            used_tickers.emplace(trade_event.ticker, te_notional);
            continue;
        }

        auto smallest_max_it = trades_with_max_notional.begin();
        if (smallest_max_it->notional >= te_notional)
        {
            continue;
        }

        used_tickers.erase(smallest_max_it->event.ticker);
        trades_with_max_notional.erase(smallest_max_it);

        used_tickers.emplace(trade_event.ticker, te_notional);
        trades_with_max_notional.emplace_hint(trades_with_max_notional.begin(), trade_event,
                                              te_notional);
    }

    TradeLog result;
    result.reserve(N);
    for (const auto& event_augmented : trades_with_max_notional)
    {
        result.emplace_back(event_augmented.event);
    }

    return result;
}
