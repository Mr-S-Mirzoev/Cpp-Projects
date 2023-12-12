#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Solution
{
private:
    int n;
    std::atomic<bool> flag;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Solution(int n)
    {
        this->n = n;
        flag = true;
    }

    void foo(std::function<void()> printFoo)
    {

        for (int i = 0; i < n; i++)
        {
            std::unique_lock<std::mutex> lck(mtx);

            cv.wait(lck, [&] { return flag == true; });
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();

            flag = false;
            cv.notify_all();
        }
    }

    void bar(std::function<void()> printBar)
    {

        for (int i = 0; i < n; i++)
        {

            // printBar() outputs "bar". Do not change or remove this line.
            std::unique_lock<std::mutex> lck(mtx);

            cv.wait(lck, [&] { return flag == false; });
            // printFoo() outputs "foo". Do not change or remove this line.
            printBar();

            flag = true;
            cv.notify_all();
        }
    }
};

int main(int argc, char const* argv[])
{
    srand((unsigned)time(0));

    int n = 2;
    Solution s{n};
    std::vector<std::thread> threads;

    std::function<void()> foo = [] { std::cout << "foo"; };
    std::function<void()> bar = [] { std::cout << "bar"; };

    std::cout << "Starting threads in random order" << std::endl;
    std::cout << "Output of their work:" << std::endl;

    int foo_count = n, bar_count = n;

    for (int i = 0; i < 2 * n; ++i)
    {
        if (rand() % 2)
        {
            if (foo_count > 0)
            {
                threads.push_back(std::thread(&Solution::foo, &s, foo));
                --foo_count;
            }
            else
            {
                threads.push_back(std::thread(&Solution::bar, &s, bar));
                --bar_count;
            }
        }
        else
        {
            if (bar_count > 0)
            {
                threads.push_back(std::thread(&Solution::bar, &s, bar));
                --bar_count;
            }
            else
            {
                threads.push_back(std::thread(&Solution::foo, &s, foo));
                --foo_count;
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