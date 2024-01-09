# Top Trade Events by Notional Value

## Task Description

You are required to write a function that processes a list of trade events and returns the top N trade events with the highest notional value, unique w.r.t. ticker. The notional value is defined as the product of the trade's price and volume.

Each trade event has the following attributes:

- `timestamp`: The time at which the trade occurred, represented as a 32-bit unsigned integer.
- `ticker`: A string identifier for the stock.
- `price`: The price at which the trade occurred, represented as a 32-bit signed integer.
- `volume`: The number of shares traded, represented as a 32-bit signed integer.

A notional value is calculated for each trade event by multiplying the price by the volume.

## Function Signature

```cpp
vector<TradeEvent> get_top_trade_events_by_notional(const vector<TradeEvent>& trade_events,
                                                    size_t N);
```

## Parameters

- `trade_events`: A vector of `TradeEvent` objects representing the list of trades.
- `N`: A size_t value representing the number of top trades to return based on notional value.

## Returns

- A vector of `TradeEvent` objects representing the top N trades with the highest notional value, sorted in the ascending order of their notional value.

## Constraints

- If multiple trades for the same stock (`ticker`) occur, only the trade with the highest notional value should be considered for that stock.
- The resulting vector should contain up to N unique stocks, sorted in descending order by their notional value.
- If fewer than N unique stocks are available, the resulting vector should contain as many trades as available.
- If a trade event has a notional value that is not greater than the smallest notional value in the current top N, it should not be included in the result.

## Examples

Given the following trade events:

```cpp
std::vector<TradeEvent> events{
    {0, "MSFT", 10, 10},  // Notional value: 100
    {1, "MSFT", 9, 12},   // Notional value: 108
    {2, "AAPL", 8, 15}    // Notional value: 120
};
```

And `N = 1`, the function should return a vector with the single event:

```cpp
{{1, "MSFT", 9, 12}}  // As this event has the highest notional value for "MSFT"
```

If `N = 2`, the function should return the events for "MSFT" and "AAPL", as they have the highest notional values for their respective stocks:

```cpp
{{2, "AAPL", 8, 15}, {1, "MSFT", 9, 12}}
```

## Note

- Focus on writing an efficient algorithm that minimizes unnecessary computations and memory usage.
- The function should handle the case where multiple trades for the same ticker occur, ensuring only the trade with the highest notional value is considered for each ticker.
