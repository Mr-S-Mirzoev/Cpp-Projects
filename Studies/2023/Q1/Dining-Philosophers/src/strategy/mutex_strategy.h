#pragma once

#include "strategy/strategy_interface.h"

#include <array>
#include <mutex>

template <size_t COUNT>
class MutexStrategy : public StrategyInterface<MutexStrategy<COUNT>>
{
    friend class StrategyInterface<MutexStrategy<COUNT>>;

private:
    std::array<std::mutex, COUNT> forks_;

    void pickLeftForkImpl(int philosopherId);
    void pickRightForkImpl(int philosopherId);
    void eatImpl(int philosopherId);
    void putLeftForkImpl(int philosopherId);
    void putRightForkImpl(int philosopherId);
};
