#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class H2O
{
    int h = 0;
    int o = 0;
    std::atomic<bool> flag;
    std::mutex mtx;
    std::condition_variable cv;

public:
    H2O() {}

    void hydrogen(std::function<void()> releaseHydrogen)
    {

        std::unique_lock<std::mutex> lck(mtx);

        cv.wait(lck, [&] { return (h < 2); });

        releaseHydrogen();

        ++h;

        if (o == 1 && h == 2)
        {
            o = 0;
            h = 0;
        }

        cv.notify_all();
        // releaseHydrogen() outputs "H". Do not change or remove this line.
    }

    void oxygen(std::function<void()> releaseOxygen)
    {

        std::unique_lock<std::mutex> lck(mtx);

        cv.wait(lck, [&] { return (o == 0); });

        releaseOxygen();

        ++o;

        if (o == 1 && h == 2)
        {
            o = 0;
            h = 0;
        }

        cv.notify_all();
        // releaseOxygen() outputs "O". Do not change or remove this line.
    }
};

int main(int argc, char const* argv[])
{
    srand((unsigned)time(0));

    int n = 2;
    H2O s{};
    std::vector<std::thread> threads;

    std::function<void()> h = [] { std::cout << "H"; };
    std::function<void()> o = [] { std::cout << "O"; };

    std::cout << "Starting threads in random order" << std::endl;
    std::cout << "Output of their work:" << std::endl;

    int h_count = 2 * n, o_count = n;

    for (int i = 0; i < 3 * n; ++i)
    {
        if (rand() % 2)
        {
            if (h_count > 0)
            {
                threads.push_back(std::thread(&H2O::hydrogen, &s, h));
                --h_count;
            }
            else
            {
                threads.push_back(std::thread(&H2O::oxygen, &s, o));
                --o_count;
            }
        }
        else
        {
            if (o_count > 0)
            {
                threads.push_back(std::thread(&H2O::oxygen, &s, o));
                --o_count;
            }
            else
            {
                threads.push_back(std::thread(&H2O::hydrogen, &s, h));
                --h_count;
            }
        }
    }

    for (auto& th : threads)
    {
        th.join();
    }

    std::cout << std::endl;

    return 0;
}