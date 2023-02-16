#include <string>
#include <iostream>

std::string solution(std::string &message, int K) {
    // write your code in C++14 (g++ 6.2.0)
    int i = K - 1;
    if (message.length() <= K)
        return message;

    if (message[i] == ' ')
        return message.substr(0, i);

    if (K < message.length() && message[K] == ' ')
        return message.substr(0, K);
    
    while (i >= 0 && message[i] != ' ')
        --i;
    
    if (i <= 0)
        return "";

    return message.substr(0, i);
}

int main(int argc, char const *argv[])
{
    std::string test = "The quick brown fox jumps over the lazy dog";
    std::cout << solution(test, 39) << std::endl;
    return 0;
}
