#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
#include <string>

class OptimizationException: public std::logic_error {
public:
    OptimizationException(const std::string &s): std::logic_error (s) {}
}; // class OptimizationException

class NotAVectorException: public OptimizationException {
public:
    NotAVectorException(std::size_t n, std::size_t m): 
        OptimizationException("Expected a vector, not a matrix of size " + 
                            std::to_string(n) + "x" + std::to_string(m)) {}
}

#endif // EXCEPTION_HPP