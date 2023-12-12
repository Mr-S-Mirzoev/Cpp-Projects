#include <iostream>
#include <vector>

std::vector<long long unsigned> squares(std::vector<long> const& input)
{
    std::size_t N = input.size();

    if (N == 0)
        return {};

    std::size_t l = 0, r = N - 1, i = N - 1;
    long long left_val, right_val;

    std::vector<long long unsigned> out(N);

    while (i < N)
    {
        left_val = input[l];
        right_val = input[r];

        if (left_val >= 0)
        {
            out[i--] = right_val * right_val;
            --r;
        }
        else if (right_val < 0)
        {
            out[i--] = left_val * left_val;
            ++l;
        }
        else
        {
            if (-left_val > right_val)
            {
                out[i--] = left_val * left_val;
                ++l;
            }
            else
            {
                out[i--] = right_val * right_val;
                --r;
            }
        }
    }

    return out;
}

int main(int argc, char const* argv[])
{
    for (auto v : squares({-5, -2, -1, 0, 4, 7}))
        std::cout << v << " ";
    std::cout << std::endl;

    for (auto v : squares({-5, -2, -1, 4, 7}))
        std::cout << v << " ";
    std::cout << std::endl;

    for (auto v : squares({0, 4, 7}))
        std::cout << v << " ";
    std::cout << std::endl;

    for (auto v : squares({-5, -2, -1}))
        std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}
