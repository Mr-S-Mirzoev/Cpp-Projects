#pragma once

#include "trade_event.h"

TradeLog get_top_trade_events_by_notional(const TradeLog& trade_events, const size_t N);
