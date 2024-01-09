#include "strategy/mutex_strategy.h"

#include <iostream>

template <size_t COUNT>
void MutexStrategy<COUNT>::pickLeftForkImpl(int philosopherId)
{
    forks_[(philosopherId + COUNT - 1) % COUNT].lock();
}

template <size_t COUNT>
void MutexStrategy<COUNT>::pickRightForkImpl(int philosopherId)
{
    forks_[philosopherId % COUNT].lock();
}

template <size_t COUNT>
void MutexStrategy<COUNT>::eatImpl(int philosopherId)
{
    // Eating - This function can be used for logging or implementing eat duration.
    std::cout << "Philosopher " << philosopherId << " is eating." << std::endl;
}

template <size_t COUNT>
void MutexStrategy<COUNT>::putLeftForkImpl(int philosopherId)
{
    forks_[(philosopherId + COUNT - 1) % COUNT].unlock();
}

template <size_t COUNT>
void MutexStrategy<COUNT>::putRightForkImpl(int philosopherId)
{
    forks_[philosopherId % COUNT].unlock();
}

// Explicit template instantiation for the used strategy
template class MutexStrategy<5>;
