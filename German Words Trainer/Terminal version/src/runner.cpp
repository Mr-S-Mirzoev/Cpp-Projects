#include "runner.hpp"
#include "classic_training.hpp"
#include <iostream>

Runner::Runner(DataBase &db): _database(db) {
    std::string input;
    std::cout << "Started the line-by-line runner. To interrupt send SIGINT" << std::endl;
    while (std::getline (std::cin, input)) {
        if (input == "start TRAINING::CLASSIC") {
            ClassicTraining classic(db);
            classic.spin();
        } else if (input == "end") {
            std::cout << "Finishing" << std::endl;
            break;
        } else {
            std::cout << "Type commands line by line." << std::endl;
            std::cout << "start TRAINING::CLASSIC = starts simple training." << std::endl;
            std::cout << "send SIGINT to finish running programm." << std::endl;
            std::cout << "end = finish running the programm softly." << std::endl;
        }
    }
}