#include "utilities.hpp"

std::ostream& rst(std::ostream& os)
{
    return os << "\x1B[0m";
}