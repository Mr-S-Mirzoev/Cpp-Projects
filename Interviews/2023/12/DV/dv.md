# Order Book Log Decoder Class

## Description

The `OrderBookDecoder` class is designed to handle and analyze order book logs provided in a `std::vector<std::string>`. Each line of the log follows a specific format:

```
<time>;<symbol>;<order_id>;<operation>;<side>;<volume>;<price>
```

where:

- `time` is a string in the format `HH:MM:SS.uuuuuu` (hours, minutes, seconds, microseconds)
- `symbol` is a string
- `order_id` is a unique 6-digit number
- `operation` is one of I, A, C (insert, amend, cancel)
- `side` is either BUY or SELL
- `volume` is an integer
- `price` is a double with 2 digits precision

For example:

```txt
15:29:45.630006;DVAM1;2868819;I;SELL;2;35.50
15:29:46.050005;DVAM1;2868819;A;SELL;2;35.50
15:29:46.440006;DVAM1;2868819;A;SELL;2;35.40
15:29:47.040005;DVAM1;2868820;I;SELL;9;35.20
15:29:47.040005;DVAM1;2868821;I;BUY;6;34.50
15:29:48.880005;DVAM1;2868822;I;SELL;9;35.50
15:29:49.530005;TEST2;2868823;I;BUY;2;28.30
15:29:49.820005;DVAM1;2868820;C;SELL;9;35.20
15:29:49.820005;DVAM1;2868824;I;SELL;8;35.40
```

Note that:
- Order ids are expected to be in ascending order.
- Symbols can have arbitrary length.

## Constructor

### `OrderBookDecoder(const std::vector<std::string>& orderBookLog)`

- Initializes an instance of the `OrderBookDecoder` class with the provided order book log.

## Member Functions

### 1. `int maxVolumeOfSellsTillTime(const std::string& time) const`

- Returns the maximum volume of sell orders until the specified time.

### 2. `double highestBuyOrderBySymbol(const std::string& symbol) const`

- Returns the highest buy order price for a given symbol at the end of the order book log.

### 3. `int countOrdersInEndBySymbol(const std::string& symbol) const`

- Returns the count of orders for a given symbol at the end of the order book log.

## Example Usage

```cpp
#include "OrderBookDecoder.h"

// Assuming orderBookLog is a std::vector<std::string> containing order book logs
OrderBookDecoder orderBookDecoder(orderBookLog);

int maxVolume = orderBookDecoder.maxVolumeOfSellsTillTime("14:00:15.034456");
double highestPrice = orderBookDecoder.highestBuyOrderBySymbol("APPL");
int orderCount = orderBookDecoder.countOrdersInEndBySymbol("APPL");
```
