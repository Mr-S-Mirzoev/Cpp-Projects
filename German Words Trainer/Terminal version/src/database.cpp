#include "database.hpp"
#include "csv_parser.hpp"
#include "classic_training.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>

DataBase::DataBase(const std::string &name): _in_file(name), _out_file(name)
{
    io::CSVReader<4> in(name);
    in.read_header(io::ignore_extra_column, "deutsch", "russian", "correct", "incorrect");
    std::string deutsch, russian;
    unsigned correct, incorrect;
    while(in.read_row(deutsch, russian, correct, incorrect)){
        _data.push_back({deutsch, russian, correct, incorrect});
        // _data.back().prettyprint();
    }
}

DataBase::DataBase(const std::string &in_name, const std::string &out_name):
    DataBase(in_name) 
{
    _out_file = out_name;
}

void DataBase::changed() {
    _changed = true;
}

void DataBase::shuffle() {
    changed();

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(_data.begin(), _data.end(), g);
}

void DataBase::sort_by_accuracy() {
    changed();

    std::sort(_data.begin(), 
              _data.end(), 
            [](const Word& left, const Word& right) -> bool {
                return left.get_accuracy() < right.get_accuracy();
            });
}

void DataBase::sort_by_german() {
    changed();
    
    std::sort(_data.begin(), 
              _data.end(), 
            [](const Word& left, const Word& right) -> bool {
                return left.get_deutsch() < right.get_deutsch();
            });
}

void DataBase::sort_by_russian() {
    changed();
    
    std::sort(_data.begin(), 
              _data.end(), 
            [](const Word& left, const Word& right) -> bool {
                return left.get_russian() < right.get_russian();
            });
}

DataBase::~DataBase () {
    if (_changed) {
        std::cout << "File changed." << std::endl;
        std::ofstream f(_out_file);
        f << "deutsch, russian, correct, incorrect" << std::endl;
        for (Word& word : _data) {
            f << word << std::endl;
        }
    } else {
        std::cout << "File not changed." << std::endl;
    }
}