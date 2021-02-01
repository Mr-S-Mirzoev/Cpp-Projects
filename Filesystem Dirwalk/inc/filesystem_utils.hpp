#ifndef FS_UTILS_H
#define FS_UTILS_H

#include <boost/range/iterator_range.hpp>
#include <filesystem>
#include <forward_list>
#include <iostream>
#include <vector>

#include "clean_file.hpp"
#include "utilities.hpp"

#define indent_with_t(c) for (int i = 0; i < c; ++i) std::cout << "    "

/* 
 * \brief Returns if `path` is current directory
*/
bool filename_is_dot(const std::filesystem::path &p);

/* 
 * \brief Returns if `path` is parent directory
*/
bool filename_is_dot_dot(const std::filesystem::path &p);

/* 
 * \brief Returns last name in the absolute path (i.e. bar in /foo/bar)
*/
std::string readable_name(const std::filesystem::path& p);

/* 
 * \brief Recursive dirwalk
*/
void recursive_dirwalk (const std::filesystem::path &p, const int &c, const int& depth);

/* 
 * \brief Dirwalk implemented as loop
*/
void looped_dirwalk (const std::filesystem::path &p, const int& depth);

#endif // FS_UTILS_H