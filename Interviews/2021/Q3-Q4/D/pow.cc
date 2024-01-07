#include <iostream>

constexpr int power(int base, int exp)
{
    if (exp == 0)
        return 1;

    int square = power(base * base, exp / 2);
    return (exp % 2) ? base * square : square;
}

int main()
{
    static_assert(power(2, 0) == 1);
    static_assert(power(2, 6) == 64);
    static_assert(power(3, 7) == 2187);
    static_assert(power(1, 10) == 1);
    static_assert(power(9, 0) == 1);
    static_assert(power(10, 1) == 10);
    static_assert(power(3, 11) == 177147);
    return 0;
}