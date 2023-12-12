#pragma once

#ifndef DEFINED_NAMEDVAL_14062020
#define XOPEN(str) "<" + str + ">"
#define XCLOS(str) "</" + str + ">"
#define NAMEDVAL(name, val) XOPEN(name) + val + XCLOS(name)
#endif

#include <string>
#include <vector>
namespace Company
{
class WorkerInfo
{
    mutable std::string title;
    mutable unsigned salary;

public:
    // constructors
    WorkerInfo();
    WorkerInfo(const std::string& t, const unsigned& s);
    WorkerInfo(const WorkerInfo& rhs);
    // setters
    void set_title(const std::string& t);
    void set_salary(const unsigned& s);
    // getter
    std::pair<std::string, unsigned> GetData() const;
    // representations
    std::string repr() const;
    std::vector<std::string> xml_repr() const;
};

} // namespace Company
