#ifndef CLASSIC_TRAINING_H
#define CLASSIC_TRAINING_H

#include "training.hpp"

constexpr double PROBABILITY_OF_GERMAN = 0.66;

class ClassicTraining: public Training
{
public:
    ClassicTraining(DataBase &db);
    void spin () override;
    ~ClassicTraining() = default;
};

#endif //CLASSIC_TRAINING_H