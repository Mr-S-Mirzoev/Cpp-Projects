#include "classic_training.hpp"

#include <iostream>
#include <random>

extern Training *current_training;

ClassicTraining::ClassicTraining(DataBase &db): Training(db) {}

void ClassicTraining::spin() {
    std::cout << "Classic training started." << std::endl;
    current_training = this;
    
    _running = true;

    _database.shuffle();

    for (auto &word : _database) {
        double lower_bound = 0.0;
        double upper_bound = 1.0;
        std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        std::default_random_engine re;
        double a_random_double = unif(re);
        std::string input;
        if (a_random_double <= PROBABILITY_OF_GERMAN) {
            std::cout << "What is the equivalent for a german word \"" << word.get_deutsch();
            std::cout << "\"?" << std::endl;

            if (std::getline (std::cin, input) && !input.empty()) {
                if (input == word.get_russian()) {
                    word.update(true);
                    std::cout << "You're correct! New accuracy rate for this word is ";
                    std::cout << word.get_accuracy() << std::endl;
                } else if (input == "finish TRAINING::CLASSIC") {
                    std::cout << "Training finished." << std::endl;
                    break;
                } else {
                    word.update(false);
                    std::cout << "You've mistaken! The correct answer is \"" << word.get_russian() << "\"";
                    std::cout << " New accuracy rate for this word is " << word.get_accuracy() << std::endl;
                }
            } else {
                std::cout << "Training finished by EOF perception." << std::endl;
                break;
            }
        } else {
            std::cout << "What is the equivalent for a russian word \"" << word.get_russian();
            std::cout << "\"?" << std::endl;
            
            if (std::getline (std::cin, input) && !input.empty()) {
                if (input == word.get_deutsch()) {
                    word.update(true);
                    std::cout << "You're correct! New accuracy rate for this word is ";
                    std::cout << word.get_accuracy() << std::endl;
                } else if (input == "finish TRAINING::CLASSIC") {
                    std::cout << "Training finished." << std::endl;
                    break;
                } else {
                    word.update(false);
                    std::cout << "You've mistaken! The correct answer is \"" << word.get_deutsch() << "\"";
                    std::cout << " New accuracy rate for this word is " << word.get_accuracy() << std::endl;
                }
            } else {
                std::cout << "Training finished by EOF perception." << std::endl;
                break;
            }
        }
        if (!_running) {
            std::cout << "Training finished by SIGINT perception." << std::endl;
            return;
        }
    }

    _running = false;

    std::cout << "Training ended as set finished. Well done." << std::endl;
}