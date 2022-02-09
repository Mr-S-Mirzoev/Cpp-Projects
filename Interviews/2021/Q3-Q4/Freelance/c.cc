#include <queue>
#include <vector>
#include <iostream>

int solution(std::vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    double sum = 0;
    for (int el : A)
        sum += el;
    
    std::priority_queue <double> queue(A.begin(), A.end());
    int n = 0;
    double goal = sum / 2;
    double max;
    while (sum > goal) {
        max = queue.top();
        queue.pop();
        max /= 2;
        sum -= max;
        ++n;
        queue.push(max);
    }

    return n;
}

int main(int argc, char const *argv[])
{
    // std::vector<int> A = {5, 19, 8, 1};
    std::vector<int> A = {3, 0, 5};
    std::cout << solution(A) << std::endl;
    return 0;
}
