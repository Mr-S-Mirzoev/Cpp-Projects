#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class DeutschBaseException: public std::exception {
public:
    DeutschBaseException(const std::string &what) = default;
}

class DeutschTypeAssertException: public DeutschBaseException
{
public:
    DeutschTypeAssertException(const std::string &type, std::string where = "");
};

#endif //EXCEPTIONS_H