#include "filesystem_utils.hpp"

bool filename_is_dot(const std::filesystem::path &p) {
    return p.native() == ".";
}

bool filename_is_dot_dot(const std::filesystem::path &p) {
    return p.native() == "..";
}

std::string readable_name(const std::filesystem::path& p) {
    std::string s = canonicalize_file_name(p.native().c_str());
    auto val = s.rfind('/');
    if (val != std::string::npos) {
        return s.substr(val + 1);
    } else {
        return s;
    }
}

void recursive_dirwalk (const std::filesystem::path &p, const int &c, const int& depth) {
    bool empty = true;
    for (auto& entry : boost::make_iterator_range(std::filesystem::directory_iterator(p), {})) {
        if (empty) {
            empty = false;
            //std::cout << c - 1 << std::endl;
            indent_with_t(c - 1);
            if (filename_is_dot(p) || filename_is_dot_dot(p)) {
                auto s = "\"" + readable_name(p) + "\"";
                std::cout << bold_red(s) << " a.k.a. "<< bold_red(p);
                if (depth)
                    std::cout << " - a directory containing:";
                std::cout << std::endl;
            } else {
                std::cout << bold_red(readable_name(p));
                if (depth)
                    std::cout << " - a directory containing:";
                std::cout << std::endl;
            }
        }
        if (std::filesystem::is_directory(entry.path())) {
            if (depth)
                recursive_dirwalk(entry.path(), c + 1, depth - 1);
        } else {
            //std::cout << c << std::endl;
            indent_with_t(c);
            std::cout << "\x1B[1;34m" << readable_name(entry.path()) << rst << "\n";
        }
    }
    if (empty) {
        //std::cout << c - 1 << std::endl;
        indent_with_t(c - 1);
        std::cout << bold_red(readable_name(p));
        if (depth)
            std::cout << " - an empty folder.";
        std::cout << std::endl;
    }
}

void looped_dirwalk (const std::filesystem::path &p, const int& depth) {
    file f(p, depth);
    std::forward_list <file> fl;
    fl.push_front(f);
    bool all_walked = false;
    while (!all_walked) {
        all_walked = true;
        for (auto &f : fl) {
            if (!f.ifwalk()) {
                all_walked = false;
                f.directory_containts(fl);
            }
        }
    }
    std::vector <clean_file> fs;
    for (auto &f : fl) {
        fs.push_back(f);
        for (auto &files : f.fs()) {
            fs.push_back(files);
        }
    }
    std::sort(fs.begin(), fs.end());
    for (auto &f : fs) {
        f.out();
    }
}
