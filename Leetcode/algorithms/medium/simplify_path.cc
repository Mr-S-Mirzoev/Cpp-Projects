#include <algorithm>
#include <iostream>
#include <string>

class Solution
{
public:
    std::string simplifyPath(std::string path)
    {
        path += "/";
        replace_all_occurencies(path, "//", "/");
        remove_this_dirs(path);
        remove_parent_refs(path);
        remove_trailing_slash(path);

        return path;
    }

    void replace_all_occurencies(std::string& s, const std::string& to_replace,
                                 const std::string& replacement);

    void remove_this_dirs(std::string& s);

    void remove_parent_refs(std::string& s);

    void remove_trailing_slash(std::string& s);
};

void Solution::replace_all_occurencies(std::string& s, const std::string& to_replace,
                                       const std::string& replacement)
{
    std::size_t spos, replacement_size = to_replace.size();
    while ((spos = s.find(to_replace)) != std::string::npos)
    {
        s.replace(spos, replacement_size, replacement);
    }
}

void Solution::remove_this_dirs(std::string& s)
{
    replace_all_occurencies(s, "/./", "/");
    // std::cout << s << std::endl;
}

void Solution::remove_parent_refs(std::string& s)
{
    std::string to_replace = "/../";
    std::size_t spos, replacement_size = to_replace.size();
    while ((spos = s.find(to_replace)) != std::string::npos)
    {
        s.replace(spos, replacement_size, "/");
        if (spos != 0)
        {
            auto lpos = s.rfind('/', spos - 1);
            s.replace(lpos, spos - lpos + 1, "/");
        }
    }
    // std::cout << s << std::endl;
}

void Solution::remove_trailing_slash(std::string& s)
{
    auto sz = s.size();
    if (sz > 1 && s[sz - 1] == '/')
    {
        s.erase(s.end() - 1);
    }
}

int main(int argc, char const* argv[])
{
    std::string input;
    std::cin >> input;
    Solution s;
    std::cout << s.simplifyPath(input) << std::endl;
    return 0;
}
