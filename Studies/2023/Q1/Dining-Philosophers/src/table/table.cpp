#include "table/table.h"
#include "strategy/mutex_strategy.h"

#include <iostream>

template <typename Strategy>
Table<Strategy>::Table()
{
    for (int i = 0; i < 5; ++i)
    {
        philosophers_.emplace_back(i);
    }
}

template <typename Strategy>
void Table<Strategy>::runDinner()
{
    for (int i = 0; i < 5; ++i)
    {
        threads_.emplace_back(
            [this, i]()
            {
                philosophers_[i].dine([this, i]() { strategy_.pickLeftFork(i); },
                                      [this, i]() { strategy_.pickRightFork(i); },
                                      [this, i]() { strategy_.eat(i); },
                                      [this, i]() { strategy_.putLeftFork(i); },
                                      [this, i]() { strategy_.putRightFork(i); });
            });
    }

    for (auto& t : threads_)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
}

// Explicit template instantiation for the used strategies
template class Table<MutexStrategy<5>>;
