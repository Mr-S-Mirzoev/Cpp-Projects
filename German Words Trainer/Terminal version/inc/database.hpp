#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

#include "word.hpp"

class DataBase
{
private:
    std::vector <Word> _data;
    std::string _in_file, _out_file;
    bool _changed = false;

    void changed();
public:
    DataBase(const std::string &in_name);
    DataBase(const std::string &in_name, const std::string &out_name);

    using container_type = std::vector<Word>;
    using iterator = container_type::iterator;
    using const_iterator = container_type::const_iterator;

    inline iterator begin() noexcept { _changed = true; return _data.begin(); }
    inline const_iterator cbegin() const noexcept { return _data.cbegin(); }
    inline iterator end() noexcept { return _data.end(); }
    inline const_iterator cend() const noexcept { return _data.cend(); }

    void shuffle ();
    
    void sort_by_german();
    void sort_by_russian();
    void sort_by_accuracy();

    ~DataBase();
};

#endif //DATABASE_H