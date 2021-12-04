#include <iostream>
#include <iterator>
#include <string>
#include <list>

namespace char_manipulations
{
    char safe_inc(char c, bool change_case = true) {
        if (c == 'Z')
            return (change_case ? 'a' : 'A');
        
        if (c == 'z')
            return (change_case ? 'A' : 'a');
        
        ++c;
        if (change_case) {
            if (isupper(c)) {
                tolower(c);
            } else {
                toupper(c);
            }
        }
        return c;
    }

    char permute(char prev, char next) {
        if (!prev)
            return safe_inc(next);
        
        if (!next)
            return safe_inc(prev);
        
        if (next == safe_inc(prev))
            return safe_inc(prev, false);
    }
} // namespace char_manipulations

template<typename X, typename Y>
std::ostream & operator<<(std::ostream & os, std::pair<X, Y> pair) {
    os << "(" << pair.first << ", " << pair.second << ")";
    return os;
}

template<typename X, typename Y>
std::ostream & operator<<(std::ostream & os, std::list< std::pair<X, Y> > vec) {
    os<<"{ ";
    for (auto el : vec) 
        os << el << " ";
    os<<"}";
    return os;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, std::list<T> vec) {
    os<<"{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os<<"}";
    return os;
}

class RepeatedString {
    std::list <std::pair <char, unsigned>> data_;
    using DataIter = std::list <std::pair <char, unsigned>>::iterator;

    bool has_upper_ = false, has_lower_ = false;
    bool has_three_ = false;
    unsigned overall_size_;
public:
    RepeatedString(std::string const& s): overall_size_(s.size()) {
        if (!overall_size_)
            return;
        
        char prev = 0;
        for (unsigned i = 0; i < s.size(); ++i) {
            if (s[i] != prev) {
                data_.push_back({s[i], 1});
                prev = s[i];
            } else {
                if (++(data_.rbegin()->second) > 2)
                    has_three_ = true;
            }

            if (islower(s[i]))
                has_lower_ = true;
            else if (isupper(s[i]))
                has_upper_ = true;
        }
    }

    void print() const {
        std::cout << data_ << std::endl;
    }

    unsigned fix_pass() {
        unsigned actions = 0;
        if (overall_size_ < 6) {
            char to_insert[2] = {0, 0};
            if (has_three_) {
                for (auto it = data_.begin(); it != data_.end(); ++it) {
                    if (it->second > 2) {
                        char prev = 0;
                        char next = 0;
                        auto tmp = it;
                        if (it != data_.begin()) {
                            prev = (--tmp)->first;
                        }
                        tmp = it;
                        if ((++tmp) != data_.end()) {
                            next = tmp->first;
                        }

                        if (!has_upper_) {
                            to_insert[0] = char_manipulations::permute(
                                prev,
                                next
                            );

                            if (islower(to_insert[0]))
                                to_insert[0] = 0;
                            else {
                                
                            }
                        }
                    }
                }
            }
        }

        return actions;
    }
};

int main(int argc, char const *argv[])
{
    std::string s;
    std::cin >> s;
    RepeatedString rs(s);
    rs.print();
    return 0;
}


