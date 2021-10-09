#include <iostream>

/*
using namespace std;
const int N=20;

//Функция для полинома:
double F (double x) {
    return x*x-9*x+14;
}

//Функция поиска корня:
double FindRoot(double (*f)(double), double x0, int n) {
    double x = x0, df, h = 0.00001;
    df = (f(x + h) - f(x)) / h;
    for (int i = 1; i <= n; i++)
        x = x - f(x) / df;
    return x;
}

int main() {
    //Начальное приближение и корень:
    double x0, x;
    cout << "initial x0 = ";
    cin >> x0;
    //Поиск решения:
    x = FindRoot(F, x0, N);
    cout << "x = " << x << endl;
    return 0;
}
*/

#include "linear_algebra/matrix.hpp"
#include <algorithm>
#include <iterator>

int main(int argc, char const *argv[])
{
    /*
    
    */
    auto v = linear_algebra::flatten<int>({
        {0, 1, 2, 3},
        {4, 5, 6, 7}
    });

    std::copy(
        v.begin(),
        v.end(),
        std::ostream_iterator <int>(std::cout, " ")
    );

    return 0;
}
