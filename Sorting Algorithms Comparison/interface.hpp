#ifndef INTERFACE_H
#define INTERFACE_H

#include "test.hpp"
#include <string>

std::vector <std::string> split(const std::string &str) 
{ 
    std::vector <std::string> result;
    // Used to split string around spaces. 
    std::istringstream ss(str); 
  
    // Traverse through all words 
    do { 
        // Read a word 
        std::string word; 
        ss >> word; 

        result.push_back(word); 
        // While there is more to read 
    } while (ss); 
    return result;
} 

void act (const std::string &s) {
    auto splitWords = split(s);
    switch (splitWords.size()) {
        case 1:
            if (splitWords[0] == "help") {
                std::cout << "1. If you want to test sort correctness:" << std::endl;
                std::cout << "\tStart with \"correct\" to define algo." << std::endl;
                std::cout << "\tThe second argument should be \"shell\" or \"quick\" to define algo." << std::endl;
                std::cout << "\tAfter you should pass \"ascending\", \"descending\" or \"random\"." << std::endl;
                std::cout << "\tThe fourth parameter is whether compare function is:" << std::endl;
                std::cout << "\t\ta) x - y; b) y - x" << std::endl;
                std::cout << "\t\tThe last parameter is optional: \"manual\"" << std::endl;
                std::cout << "2. If you want to test sort correctness:" << std::endl;
                std::cout << "\tStart with \"time\" to define algo." << std::endl;
                std::cout << "\tThe second argument should be \"shell\" or \"quick\" to define algo." << std::endl;
                std::cout << "\tAfter you should pass \"ascending\", \"descending\" or \"random\"." << std::endl;
                std::cout << "\tThe fourth parameter is whether compare function is:" << std::endl;
                std::cout << "\t\ta) x - y; b) y - x" << std::endl;
                std::cout << "3. If you want to check how fast algorithms wor:" << std::endl;
                std::cout << "\tStart with \"time\" to define algo." << std::endl;
                std::cout << "\tThe second argument should be \"shell\" or \"quick\" to define algo." << std::endl;
                std::cout << "\tAfter you should pass \"ascending\", \"descending\" or \"random\"." << std::endl;
                std::cout << "\tThe fourth parameter is whether compare function is:" << std::endl;
                std::cout << "\t\ta) x - y; b) y - x" << std::endl;
                std::cout << "" << std::endl;
                std::cout << "" << std::endl;
            } 
    }
}

#endif