#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class DeutschBaseException: public std::runtime_error {
public:
    DeutschBaseException(const std::string &what);
};

class DeutschTypeAssertException: public DeutschBaseException
{
public:
    DeutschTypeAssertException(const std::string &type, std::string where = "");
};

#endif //EXCEPTIONS_H
