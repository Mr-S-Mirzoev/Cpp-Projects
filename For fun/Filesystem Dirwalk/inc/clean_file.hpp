#ifndef CLEANFILE_H
#define CLEANFILE_H

#include "filesystem_utils.hpp"
#include "file.hpp"
#include "utilities.hpp"

/* 
 * \brief Class representation of file regardless of the path with which it was constructed
*/
class clean_file {
    std::string name;
    std::filesystem::path p;
    std::string synonim;
    bool has_synonims;
    int indent;
    bool dir;
public:
    clean_file (const std::filesystem::path &path, bool d = false);
    clean_file (const file &f);
    void out () const;
    bool operator < (const clean_file &other);
};

#endif // CLEANFILE_H