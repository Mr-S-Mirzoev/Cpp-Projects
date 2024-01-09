#pragma once

#include "philosopher/philosopher.h"
#include <thread>
#include <vector>

template <typename Strategy>
class Table
{
public:
    Table();
    void runDinner();

private:
    std::vector<Philosopher> philosophers_;
    Strategy strategy_;
    std::vector<std::thread> threads_;
};
