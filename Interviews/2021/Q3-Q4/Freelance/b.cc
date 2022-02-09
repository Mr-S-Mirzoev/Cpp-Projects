#include <vector>
#include <algorithm>
#include <iostream>

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(std::vector<int> &P, std::vector<int> &S) {
    // write your code in C++14 (g++ 6.2.0)
    std::sort(S.begin(), S.end(), std::greater<int>());

    int sum = 0;
    int k = 0;
    for (int el : P)
        sum += el;

    for (int el : S)
        if ((sum -= el) <= 0)
            break;
        else
            ++k;
    
    return k + 1;
}

int main(int argc, char const *argv[])
{
    /* code */
    // std::vector <int> P = {1, 4, 1};
    // std::vector <int> S = {1, 5, 1};
    // std::vector <int> P = {4, 4, 2, 4};
    // std::vector <int> S = {5, 5, 2, 5};
    std::vector <int> P = {2, 3, 4, 2};
    std::vector <int> S = {2, 5, 7, 2};
    std::cout << solution(P, S) << std::endl;
    return 0;
}
