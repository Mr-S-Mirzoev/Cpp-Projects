#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void first() { std::cout << "It's first!" << std::endl; }

void second() { std::cout << "It's second!" << std::endl; }

void third() { std::cout << "It's third!" << std::endl; }

class Solution
{
    std::atomic<int> cur;
    std::mutex mtx;
    std::condition_variable cv;

protected:
    void do_work(std::function<void()> printS, std::function<bool()> check)
    {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [&] { return check(); });

        cur = (cur + 1) % 4;
        printS();
        cv.notify_all();
    }

public:
    Solution() { this->cur = 1; }

    void first(std::function<void()> printFirst)
    {
        // printFirst() outputs "first". Do not change or remove this line.
        do_work(printFirst, [&] { return cur == 1; });
    }

    void second(std::function<void()> printSecond)
    {
        // printSecond() outputs "second". Do not change or remove this line.
        do_work(printSecond, [&] { return cur == 2; });
    }

    void third(std::function<void()> printThird)
    {

        // printThird() outputs "third". Do not change or remove this line.
        do_work(printThird, [&] { return this->cur == 3; });
    }
};

int main(int argc, char const* argv[])
{
    Solution s;
    std::vector<std::thread> threads;

    std::function<void()> f1 = first;
    std::function<void()> f2 = second;
    std::function<void()> f3 = third;

    std::cout << "Starting threads in order: [2, 1, 3]" << std::endl;
    std::cout << "Output of their work:" << std::endl;

    threads.push_back(std::thread(&Solution::second, &s, f2));
    threads.push_back(std::thread(&Solution::first, &s, f1));
    threads.push_back(std::thread(&Solution::third, &s, f3));

    for (auto& th : threads)
    {
        th.join();
    }

    return 0;
}
