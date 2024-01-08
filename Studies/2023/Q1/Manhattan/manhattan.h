#pragma once

#include <queue>
#include <string_view>
#include <vector>

struct CoordWithDist
{
    int x;
    int y;
    int dist;
};

class ManhattanProcessor
{
    std::vector<std::string_view> const& data_;
    int N_;
    int M_;
    std::vector<std::vector<bool>> visited_;
    std::queue<CoordWithDist> candidates_;

public:
    ManhattanProcessor(std::vector<std::string_view> const& data);

    int process(int src, int dest);

private:
    void initialise_candidates(int src) noexcept;
};