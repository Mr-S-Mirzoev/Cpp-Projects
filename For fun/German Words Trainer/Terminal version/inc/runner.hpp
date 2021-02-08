#ifndef RUNNER_H
#define RUNNER_H

#include "training.hpp"

class Runner
{
protected:
    DataBase _database;
public:
    Runner(DataBase &db);

    ~Runner() = default;
};

void sig_handler (int signum);

#endif //RUNNER_H