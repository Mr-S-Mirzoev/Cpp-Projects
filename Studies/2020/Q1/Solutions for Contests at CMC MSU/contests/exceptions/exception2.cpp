#include <iostream>
// Название функции - гипероператор.
struct Result {
    long long res;
    Result(long long a): res(a) {}
    ~Result() {}
};

void func (long long a, long long b, unsigned long k) {
    if (k == 0) {
        Result x(a + b);
        throw x;
    } else if (k > 0 && b == 1) {
        Result x(a);
        throw x;
    } else {
        try {
            func(a, b - 1, k);
        }
        catch (const Result &p) {
            func(a, p.res, k - 1);
        }
    }
}

int main () 
{
    long long a, b;
    unsigned long k;
    while (std::cin >> a >> b >> k) {
        try {
            func(a, b, k);
        }
        catch (const Result &p) {
            std::cout << p.res<<std::endl;
        }
    }
}
