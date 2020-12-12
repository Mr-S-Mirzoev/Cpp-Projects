#include "exceptions.hpp"

DeutschTypeAssertException::DeutschTypeAssertException(const std::string &type, std::string where):
    DeutschBaseException("[DeutschTypeAssertException] Type assertion failed for type " + type + ((!where.empty()) ? "in " + where : "")) {}
