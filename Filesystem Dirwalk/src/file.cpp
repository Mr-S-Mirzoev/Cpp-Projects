#include "file.hpp"

file::file (const std::filesystem::path &p, const int& d): path(p), depth(d) {
    directory = std::filesystem::is_directory(p);
    walked = !(depth > 0);
}

bool file::dir() const {
    return directory;
}

bool file::ifwalk() const {
    return walked;
}

bool file::empty () const {
    return files.empty();
}

std::filesystem::path file::p() const {
    return path;
}

std::forward_list <std::filesystem::path> file::fs() const {
    return files;
}

void file::directory_containts (std::forward_list <file> &fl) {
    walked = true;
    for (auto& entry : boost::make_iterator_range(std::filesystem::directory_iterator(path), {})) {
        if (std::filesystem::is_directory(entry.path())) {
            if (depth)
                fl.push_front(file(entry.path(), depth - 1));
        } else {
            files.push_front(entry.path());
        }
    }
}