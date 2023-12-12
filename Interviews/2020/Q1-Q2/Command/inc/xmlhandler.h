#pragma once

#include "company.h"
#include "stringmanip.h"
#include <fstream>
#include <iostream>
#include <string>
class XML_reader
{
    Company::Company comp;

public:
    XML_reader(const std::string& filename);
    Company::Company get_comp() const;
    Company::Company& get_comp_lnk();
    void show() const;
};

class XML_writer
{
public:
    XML_writer(const std::string& filename, const Company::Company& c);
};
