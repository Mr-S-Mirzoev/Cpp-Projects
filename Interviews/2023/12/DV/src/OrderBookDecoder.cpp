#include "OrderBookDecoder.h"

#include <fstream>
#include <string>

int main(int argc, char const* argv[])
{
    std::string fileName = "orderBookLog.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }

    std::ifstream file(fileName);

    // Read order book logs from file
    std::vector<std::string> orderBookLog;
    {
        std::string str;
        while (std::getline(file, str))
        {
            orderBookLog.push_back(str);
        }
    }

    OrderBookDecoder orderBookDecoder(orderBookLog);

    int maxVolume = orderBookDecoder.maxVolumeOfSellsTillTime("14:00:15.034456");
    double highestPrice = orderBookDecoder.highestBuyOrderBySymbol("APPL");
    int orderCount = orderBookDecoder.countOrdersInEndBySymbol("APPL");
    return 0;
}
