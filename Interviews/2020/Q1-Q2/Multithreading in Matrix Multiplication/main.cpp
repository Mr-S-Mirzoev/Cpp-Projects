#include "matrix.h"
#include <ctime>
#include <cstdlib>

int main()
{
    Matrix <int> a(3, 4, true, -20, 20), b(4, 5, true, -20, 20);
    const auto processor_count = std::thread::hardware_concurrency();
    auto c = Matrix<int>::multiply(a, b, processor_count + 1);
    std::cout << a << std::endl << b << std::endl << c << std::endl;
}