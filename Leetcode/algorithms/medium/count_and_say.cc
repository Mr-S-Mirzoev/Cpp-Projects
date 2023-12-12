#include <iostream>
#include <string>
#include <vector>

std::vector<int> sayVec(std::vector<int> const& v)
{
    if (v.empty())
        return v;

    unsigned N = 2;
    std::vector<int> s;
    s.resize(v.size() << 1);

    s[N - 2] = 1;    // count
    s[N - 1] = v[0]; // first character
    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i] == s[N - 1])
        {
            ++s[N - 2];
        }
        else
        {
            N += 2;
            s[N - 2] = 1;
            s[N - 1] = v[i];
        }
    }
    if (N != v.size() << 1)
        s.resize(N);
    return s;
}

std::string countAndSay(int n)
{
    std::vector<int> s = {1};
    for (int i = 2; i <= n; ++i)
        s = sayVec(s);

    std::string result;
    for (int d : s)
    {
        result += ('0' + d);
    }
    return result;
}

int main(int argc, char const* argv[])
{
    std::cout << countAndSay(4) << std::endl;
    return 0;
}
