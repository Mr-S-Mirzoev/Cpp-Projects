#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <string>
#include <fstream>

/*
 * Get current date/time, format is YYYY-MM-DD HH:mm:ss
 */ 
std::string currentDateTime();

/*
 * Get random int in [min, max] range
 */ 
int intRand(const int & min, const int & max);

inline bool is_empty(std::ifstream &pFile) {
    return (pFile.peek() == std::ifstream::traits_type::eof());
}

#endif // UTILS_H