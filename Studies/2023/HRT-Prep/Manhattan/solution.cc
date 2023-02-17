#include <array>
#include <queue>
#include <string_view>
#include <vector>

#include "small_test_framework.h"

struct CoordWithDist
{
    int x;
    int y;
    int dist;
};

int process(std::vector <std::string_view> const& data, char src, char dest)
{
    int N = data.size();
    if (!N)
        return 0;

    int M = data[0].size();
    if (!M)
        return 0;

    std::vector <std::vector <bool>> visited(N);
    std::queue <CoordWithDist> candidates;
    for (int x = 0; x < N; ++x)
    {
        visited[x].resize(M);
        for (int y = 0; y < M; ++y)
        {
            if (data[x][y] == src)
            {
                candidates.push({x, y, 0});
                visited[x][y] = true;
            }
        }
    }

    // UP, RIGHT, DOWN, LEFT
    std::array <int, 4> dx {-1, 0, 1, 0};
    std::array <int, 4> dy {0, 1, 0, -1};
    auto validate = [&N, &M, &visited](int x, int y) -> bool {
        return x >= 0 && y >= 0 && x < N && y < M && !visited[x][y];
    };
    while (!candidates.empty())
    {
        auto &candidate = candidates.front();
        for (int i = 0; i < 4; i++)
        {
            CoordWithDist next {candidate.x + dx[i], candidate.y + dy[i], candidate.dist + 1};
            if (!validate(next.x, next.y))
                continue;

            if (data[next.x][next.y] == dest)
                return next.dist;

            candidates.push(next);
        }

        candidates.pop();
    }

    throw std::runtime_error("Destination or source not found");
}

int main(int argc, char const *argv[])
{
    /*
    #####################
    # - # - # A # - # A #
    #####################
    # - # A # - # - # - #
    #####################
    # - # - # - # B # - #
    #####################
    # A # - # - # - # - #
    #####################
    # - # A # - # A # A #
    #####################
    */
    std::vector <std::string_view> data = {
        "CxAxA",
        "xAxxx",
        "xxxBx",
        "Axxxx",
        "xACAA"
    };

    ASSERT_EQ(process(data, 'C', 'B'), 3);
    ASSERT_EQ(process(data, 'A', 'B'), 2);
    return 0;
}
