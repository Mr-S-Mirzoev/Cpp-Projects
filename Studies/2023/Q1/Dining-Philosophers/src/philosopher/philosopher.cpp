#include "philosopher/philosopher.h"

#include "philosopher.h"
#include <chrono>
#include <thread>

Philosopher::Philosopher(int id) : id_(id) {}

void Philosopher::dine(std::function<void()> pickLeftFork, std::function<void()> pickRightFork,
                       std::function<void()> eat, std::function<void()> putLeftFork,
                       std::function<void()> putRightFork)
{
    while (100)
    {
        // Example implementation
        pickLeftFork();
        pickRightFork();

        eat();
        if (eat_callback_)
        {
            eat_callback_(id_);
        }

        putLeftFork();
        putRightFork();

        // Simulate thinking
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Philosopher::setEatCallback(std::function<void(int)> eat_callback)
{
    eat_callback_ = std::move(eat_callback);
}
