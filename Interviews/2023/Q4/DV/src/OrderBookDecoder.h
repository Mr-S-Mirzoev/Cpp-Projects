#pragma once

#include <string>
#include <vector>

struct OrderVolume
{
    int volume;
    double price;
};

class OrderBookDecoder
{
public:
    OrderBookDecoder(const std::vector<std::string>& orderBookLog);

    int maxVolumeOfSellsTillTime(const std::string& time) const;
    double highestBuyOrderBySymbol(const std::string& symbol) const;
    int countOrdersInEndBySymbol(const std::string& symbol) const;
};
