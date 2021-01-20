#ifndef TRAINING_H
#define TRAINING_H

#include "database.hpp"

class Training
{
protected:
    DataBase &_database;
    bool _running = false;
public:
    Training(DataBase &db);

    virtual void spin () = 0;
    void interrupt();

    virtual ~Training() = default;
};

void sig_handler (int signum);

#endif //TRAINING_H