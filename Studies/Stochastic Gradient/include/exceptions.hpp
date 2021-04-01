#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

namespace utils {

    class MLException: public std::runtime_error
    {
    public:
        MLException(const std::string &s): std::runtime_error("An ML Exception has occured: " + s) {}
    };

    class NotImplementedFunctionException: public MLException
    {
    public:
        NotImplementedFunctionException(const std::string &function_name): MLException("Function \"" + function_name + "\" not implemented.") {}
    };
}

#endif // EXCEPTIONS_HPP  