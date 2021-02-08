#include "clean_file.hpp"

clean_file::clean_file (const std::filesystem::path &path, bool d): p(path), dir(d) {
    if (filename_is_dot(p) || filename_is_dot_dot(p)) {
        name = "\"" + readable_name(p) + "\"";
        has_synonims = true;
        synonim = p.native();
    } else {
        has_synonims = false;
        name = readable_name(p);
    }
    indent = std::count(p.native().begin(), p.native().end(), '/');
}

clean_file::clean_file (const file &f): p(f.p()), dir(f.dir()) {
    if (filename_is_dot(p) || filename_is_dot_dot(p)) {
        name = readable_name(p);
        has_synonims = true;
        synonim = p.native();
    } else {
        has_synonims = false;
        name = readable_name(p);
    }
    indent = std::count(p.native().begin(), p.native().end(), '/');
}

void clean_file::out () const {
    indent_with_t(indent);
    if (dir) {
        if (has_synonims)
            std::cout << bold_red(name) << " a.k.a " << bold_red(synonim) << std::endl;
        else 
            std::cout << bold_red(name) << std::endl;
    } else {
        std::cout << bold_blue(name) << std::endl;
    }
}

bool clean_file::operator < (const clean_file &other) {
    return p.native() < other.p.native();
}