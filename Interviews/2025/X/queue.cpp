#include <cassert>

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <iostream>
#include <queue>
#include <vector>

template<typename T>
class SPMCQueue
{
public:
    template<typename... Args>
    void emplace(Args&&... args)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.emplace(std::forward<Args>(args)...);
        }
        m_cv.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] { return !m_queue.empty(); });

        T val = std::move(m_queue.front());
        m_queue.pop();
        return val;
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};


void test_basic_functionality()
{
    SPMCQueue<int> q;

    std::thread producer([&q] {
        for (int i = 0; i < 10; ++i) {
            q.emplace(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });

    std::vector<std::thread> consumers;
    std::mutex output_mutex;
    int total_sum = 0;
    std::mutex sum_mutex;

    for (int i = 0; i < 2; ++i) {
        consumers.emplace_back([&q, &output_mutex, &total_sum, &sum_mutex] {
            for (int j = 0; j < 5; ++j) {
                int val = q.pop();
                {
                    std::lock_guard<std::mutex> out_lock(output_mutex);
                    std::cout << "Consumer " << std::this_thread::get_id()
                              << " got value: " << val << std::endl;
                }
                {
                    std::lock_guard<std::mutex> sum_lock(sum_mutex);
                    total_sum += val;
                }
            }
        });
    }

    producer.join();
    for (auto& c : consumers)
        c.join();

    assert(total_sum == 45);
    std::cout << "Test passed: total sum is " << total_sum << std::endl;
}

void test_blocking_behavior()
{
    SPMCQueue<int> q;
    std::atomic<bool> consumer_started = false;
    std::atomic<bool> consumer_received = false;

    std::thread consumer([&q, &consumer_started, &consumer_received] {
        consumer_started = true;
        // should block until producer emplaces a value
        int value = q.pop();
        assert(value == 42);
        consumer_received = true;
    });

    // Wait for consumer to start and block
    while (!consumer_started) {
        std::this_thread::yield();
    }

    // Mock blocking behavior
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Consumer should still be waiting
    assert(!consumer_received);

    // Producer emplaces a value, waking the consumer
    q.emplace(42);

    consumer.join();
    assert(consumer_received);
    std::cout << "Blocking behavior test passed." << std::endl;
}

int main()
{
    test_basic_functionality();
    test_blocking_behavior();

    return 0;
}
