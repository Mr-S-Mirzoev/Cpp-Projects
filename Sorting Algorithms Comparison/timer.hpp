#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

class Timer
{
    int64_t _count = 0;
    std::chrono::time_point<Clock> _lastStart;
    bool _paused = false;
public:
    Timer(): _lastStart(Clock::now()) {};
    int64_t getTime () {
        return _count;
    }
    int64_t pause() {
        if (_paused)
            throw std::logic_error("Trying to pause timer while it is paused already");
        
        auto now = Clock::now();
        _count += std::chrono::duration_cast<std::chrono::nanoseconds>(now - _lastStart).count();
        _paused = true;
        return _count;
    }
    void resume() {
        if (!_paused)
            throw std::logic_error("Trying to pause timer while it is paused already");
        
        _lastStart = Clock::now();
        _paused = false;
    }
    void reset() {
        _paused = false;
        _lastStart = Clock::now();
    }
};

#endif