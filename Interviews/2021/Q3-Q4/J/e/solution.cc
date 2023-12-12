#include <iostream>
#include <stdexcept>
#include <vector>

int scalar_mul(std::vector<std::pair<int, unsigned>> const& a,
               std::vector<std::pair<int, unsigned>> const& b)
{
    if (a.size() * b.size() == 0)
        return 0;

    int i_a = 0;
    int i_b = 0;

    unsigned left_a = a[0].second;
    unsigned left_b = b[0].second;
    int sum = 0;

    while (i_a < a.size() && i_b < b.size())
    {
        unsigned offset = std::min(left_a, left_b);
        sum += a[i_a].first * b[i_b].first * offset;

        left_b -= offset;
        left_a -= offset;

        if (!left_a)
            if (i_a + 1 < a.size())
                left_a = a[++i_a].second;
            else
                ++i_a;

        if (!left_b)
            if (i_b + 1 < b.size())
                left_b = b[++i_b].second;
            else
                ++i_b;
    }

    if (left_a || left_b)
        throw std::logic_error("Size mismatch");

    return sum;
}

int main(int argc, char const* argv[])
{
    // [{2, 3}, {1, 2}, {-1, 3}] * [{0, 4}, {5, 4}]
    std::vector<std::pair<int, unsigned>> a{{2, 3}, {1, 2}, {-1, 3}};
    std::vector<std::pair<int, unsigned>> b{{0, 4}, {5, 4}};

    std::cout << scalar_mul(a, b) << std::endl;

    return 0;
}
