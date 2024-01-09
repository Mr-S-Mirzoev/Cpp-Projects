#include "gtest/gtest.h"

#include "philosopher/philosopher.h"
#include "strategy/mutex_strategy.h"

#include "gtest/gtest.h"

#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

class DiningPhilosophersTest : public ::testing::Test
{
protected:
    static constexpr int kNumPhilosophers = 5;
    static constexpr int kDiningRounds = 1000;
    MutexStrategy<kNumPhilosophers> strategy;
    std::vector<Philosopher> philosophers;

    DiningPhilosophersTest()
    {
        for (int i = 0; i < kNumPhilosophers; ++i)
        {
            philosophers.emplace_back(i);
        }
    }

    void SetUp() override
    {
        // Set up can initialize necessary components before each test
    }

    void TearDown() override
    {
        // Clean up any resources after each test
    }

    void runDiningSimulation()
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < kNumPhilosophers; ++i)
        {
            threads.emplace_back(
                [this, i]()
                {
                    for (int j = 0; j < kDiningRounds; ++j)
                    {
                        philosophers[i].dine([this, i]() { strategy.pickLeftFork(i); },
                                             [this, i]() { strategy.pickRightFork(i); },
                                             [this, i]() { strategy.eat(i); },
                                             [this, i]() { strategy.putLeftFork(i); },
                                             [this, i]() { strategy.putRightFork(i); });
                    }
                });
        }

        for (auto& thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }
};

TEST_F(DiningPhilosophersTest, TestNoDeadlock)
{
    // This test checks that the simulation can run to completion without deadlocks.
    // Note: This is not a definitive test for deadlocks, but if there are issues in the
    // strategy implementation, this test might hang or take an unusually long time to complete.

    ASSERT_NO_THROW(runDiningSimulation());
}

TEST_F(DiningPhilosophersTest, TestNoStarvation)
{
    // This test checks that all philosophers get a chance to eat.
    // It's a basic check and won't catch all starvation scenarios, but it's a good start.

    std::atomic<int> eatCount[kNumPhilosophers] = {};

    for (int i = 0; i < kNumPhilosophers; ++i)
    {
        std::function<void(int)> eatCallback = [&eatCount](int id) { eatCount[id]++; };
        philosophers[i].setEatCallback(eatCallback);
    }

    runDiningSimulation();

    for (int i = 0; i < kNumPhilosophers; ++i)
    {
        ASSERT_GT(eatCount[i].load(), 0) << "Philosopher " << i << " did not eat.";
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
