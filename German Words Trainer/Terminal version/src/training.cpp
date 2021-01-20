#include "training.hpp"

extern Training *current_training;

Training::Training(DataBase &db): _database(db) {}

void Training::interrupt() {
    _running = false;
    current_training = nullptr;
}

void sig_handler(int signum) {
    if (current_training)
        current_training->interrupt();
}