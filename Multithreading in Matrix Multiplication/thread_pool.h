#ifndef TS_STACK_H
#define TS_STACK_H

#include <boost/thread/mutex.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>

//#define DEBUG

class ThreadPool
{
    std::mutex lock_;
    std::condition_variable condVar_;
    bool shutdown_;
    std::queue <std::function <void (void)>> jobs_;
    std::vector <std::thread> threads_;
public:
    ThreadPool (int threads) : shutdown_ (false) {
        threads_.reserve (threads); // Create the specified number of threads
        for (int i = 0; i < threads; ++i)
            threads_.emplace_back (std::bind (&ThreadPool::threadEntry, this, i));  
            /*
            // To bind to a member function we have to:
                Foo foo;
                auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
                f3(5);
            */
    }

    ~ThreadPool () {
        {
            std::unique_lock <std::mutex> l (lock_); // Unblock any threads and tell them to stop
            shutdown_ = true;
            condVar_.notify_all(); // Release all threads from while loop.
        }

        #ifdef DEBUG
        std::cerr << "Joining threads" << std::endl;
        #endif

        for (auto& thread : threads_)
            thread.join(); // Wait for all threads to stop
    }

    void doJob (std::function <void (void)> func) {
        std::unique_lock <std::mutex> l (lock_); // Place a job on the queue and unblock a random thread
        jobs_.emplace (std::move(func));
        condVar_.notify_one();
    }
protected:
    void threadEntry (int i) {
        std::function <void (void)> job; 
        while (1) {
            {
                std::unique_lock <std::mutex> l (lock_); // condition variable locks this std::unique_lock.

                while (!shutdown_ && jobs_.empty()) // if no jobs or shutdown is not requested the loop goes on
                    condVar_.wait (l); // waits till notified: unlocks 'l' waits till notified, when locks 'l' and returns

                if (jobs_.empty ()) {
                    // No jobs to do and we are shutting down
                    #ifdef DEBUG
                    std::cerr << "Thread " << i << " terminates" << std::endl;
                    #endif
                    return;
                }

                #ifdef DEBUG
                std::cerr << "Thread " << i << " does the job" << std::endl;
                #endif
                job = std::move (jobs_.front());
                jobs_.pop();
            }
            // Do the job without holding any locks
            job ();
        }
    }
};

#endif