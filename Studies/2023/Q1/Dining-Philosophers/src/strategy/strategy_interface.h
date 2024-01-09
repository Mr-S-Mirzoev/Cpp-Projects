#pragma once

template <typename Implementation>
class StrategyInterface
{
public:
    void pickLeftFork(int philosopherId)
    {
        static_cast<Implementation*>(this)->pickLeftForkImpl(philosopherId);
    }

    void pickRightFork(int philosopherId)
    {
        static_cast<Implementation*>(this)->pickRightForkImpl(philosopherId);
    }

    void eat(int philosopherId) { static_cast<Implementation*>(this)->eatImpl(philosopherId); }

    void putLeftFork(int philosopherId)
    {
        static_cast<Implementation*>(this)->putLeftForkImpl(philosopherId);
    }

    void putRightFork(int philosopherId)
    {
        static_cast<Implementation*>(this)->putRightForkImpl(philosopherId);
    }
};
