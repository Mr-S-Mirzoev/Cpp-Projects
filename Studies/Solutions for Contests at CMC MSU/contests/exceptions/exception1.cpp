#include <iostream>

class rec {
    std::string my_s;
public:
    rec (const std::string &s): my_s (s) {}
    ~rec () {
        std::cout << my_s << std::endl;
    }
};

void f () {
    std::string x;
    try {
        if (std::cin >> x) {
            rec y(x);
            f();
        } else {
            throw 1;
        }
    }
}

int main () 
{
    try {
        f();
    }
    catch (const int &) {}
}
