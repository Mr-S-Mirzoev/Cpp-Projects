#include <gtest/gtest.h>

#include "trade_event_utils.h"

// Test fixture class, if needed
class TradeEventTest : public ::testing::Test
{
protected:
    TradeLog trade_events;

    // You can define setup logic if necessary
    void SetUp() override
    {
        // Populate trade_events with initial data
    }

    // Tear down logic if necessary
    void TearDown() override
    {
        // Clean up if any
    }
};

// Test case for no trades
TEST(TradeEventTest, NoTrades)
{
    TradeLog events;
    auto top_trades = get_top_trade_events_by_notional(events, 5);
    EXPECT_TRUE(top_trades.empty());
}

// Test case for fewer trades than N
TEST(TradeEventTest, FewerTradesThanN)
{
    TradeLog events{
        {100, "AAPL", 200, 50}, // Notional: 10000
        {200, "GOOG", 800, 20}  // Notional: 16000
    };
    auto top_trades = get_top_trade_events_by_notional(events, 5);
    ASSERT_EQ(top_trades.size(), 2);
    EXPECT_EQ(top_trades[0].ticker, "AAPL");
    EXPECT_EQ(top_trades[1].ticker, "GOOG");
}

// Test case for exactly N trades
TEST(TradeEventTest, ExactlyNTrades)
{
    TradeLog events{
        {100, "AAPL", 200, 50}, // Notional: 10000
        {200, "GOOG", 800, 20}, // Notional: 16000
        {300, "MSFT", 100, 10}  // Notional: 1000
    };
    auto top_trades = get_top_trade_events_by_notional(events, 3);
    ASSERT_EQ(top_trades.size(), 3);

    // Expect the trades to be sorted by notional in ascending order
    EXPECT_EQ(top_trades[0].ticker, "MSFT");
    EXPECT_EQ(top_trades[0].price, 100);
    EXPECT_EQ(top_trades[0].volume, 10);
    EXPECT_EQ(top_trades[1].ticker, "AAPL");
    EXPECT_EQ(top_trades[1].price, 200);
    EXPECT_EQ(top_trades[1].volume, 50);
    EXPECT_EQ(top_trades[2].ticker, "GOOG");
    EXPECT_EQ(top_trades[2].price, 800);
    EXPECT_EQ(top_trades[2].volume, 20);
}

// Test case for more trades than N
TEST(TradeEventTest, MoreTradesThanN)
{
    std::vector<TradeEvent> events{
        {100, "AAPL", 200, 50}, // Notional: 10000
        {200, "GOOG", 800, 20}, // Notional: 16000
        {300, "MSFT", 100, 10}, // Notional: 1000
        {400, "TSLA", 300, 30}  // Notional: 9000
    };
    auto top_trades = get_top_trade_events_by_notional(events, 2);
    ASSERT_EQ(top_trades.size(), 2);

    // Expect the trades to be sorted by notional in ascending order
    EXPECT_EQ(top_trades[0].ticker, "AAPL");
    EXPECT_EQ(top_trades[0].price, 200);
    EXPECT_EQ(top_trades[0].volume, 50);
    EXPECT_EQ(top_trades[1].ticker, "GOOG");
    EXPECT_EQ(top_trades[1].price, 800);
    EXPECT_EQ(top_trades[1].volume, 20);
}

// Test case for multiple trades for the same stock
TEST(TradeEventTest, MultipleTradesSameStock)
{
    std::vector<TradeEvent> events{
        {100, "AAPL", 200, 50},
        {150, "AAPL", 210, 55}, // Higher notional than previous AAPL trade (10000 vs 11550)
        {200, "GOOG", 800, 20}  // Notional: 16000
    };
    auto top_trades = get_top_trade_events_by_notional(events, 2);
    ASSERT_EQ(top_trades.size(), 2);

    // The AAPL trade with the higher notional should be in top_trades
    EXPECT_EQ(top_trades[0].ticker, "AAPL");
    EXPECT_EQ(top_trades[0].price, 210);
    EXPECT_EQ(top_trades[0].volume, 55);

    EXPECT_EQ(top_trades[1].ticker, "GOOG");
    EXPECT_EQ(top_trades[1].price, 800);
    EXPECT_EQ(top_trades[1].volume, 20);
}
