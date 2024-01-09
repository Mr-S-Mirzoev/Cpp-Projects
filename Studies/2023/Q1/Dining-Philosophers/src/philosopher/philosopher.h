#pragma once

#include <functional>

class Philosopher
{
    std::function<void(int)> eat_callback_;

public:
    Philosopher(int id);

    void dine(std::function<void()> pickLeftFork, std::function<void()> pickRightFork,
              std::function<void()> eat, std::function<void()> putLeftFork,
              std::function<void()> putRightFork);

    void setEatCallback(std::function<void(int)> eat_callback);

private:
    int id_;
};
