#ifndef FILE_H
#define FILE_H

#include <boost/range/iterator_range.hpp>
#include <filesystem>
#include <forward_list>

/* 
 * \brief Class representation of file (both directory and regular file)
*/
class file {
    std::filesystem::path path;
    bool walked;
    std::forward_list <std::filesystem::path> files;
    bool directory;
    int depth;
public:
    file (const std::filesystem::path &p, const int& d);
    bool dir() const;
    bool ifwalk() const;
    bool empty () const;
    std::filesystem::path p() const;
    std::forward_list <std::filesystem::path> fs() const;
    void directory_containts (std::forward_list <file> &fl);
};

#endif // FILE_H