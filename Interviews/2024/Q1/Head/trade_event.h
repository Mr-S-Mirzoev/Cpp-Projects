#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct TradeEvent
{
    std::uint32_t timestamp;
    std::string ticker;
    std::int32_t price;
    std::int32_t volume;
};

using TradeLog = std::vector<TradeEvent>;
