#include "manhattan.h"

#include <array>
#include <stdexcept>

ManhattanProcessor::ManhattanProcessor(std::vector<std::string_view> const& data) : data_(data)
{
    N_ = data_.size();
    if (!N_)
        throw std::runtime_error("Empty data");

    M_ = data_[0].size();
    if (!M_)
        throw std::runtime_error("Empty data");
}

void ManhattanProcessor::initialise_candidates(int src) noexcept
{
    visited_.clear();
    visited_.resize(N_);
    candidates_ = std::queue<CoordWithDist>();

    for (int x = 0; x < N_; ++x)
    {
        visited_[x].resize(M_);
        for (int y = 0; y < M_; ++y)
        {
            if (data_[x][y] == src)
            {
                candidates_.push({x, y, 0});
                visited_[x][y] = true;
            }
        }
    }
}

int ManhattanProcessor::process(int src, int dest)
{
    initialise_candidates(src);

    // UP, RIGHT, DOWN, LEFT
    std::array<int, 4> dx{-1, 0, 1, 0};
    std::array<int, 4> dy{0, 1, 0, -1};
    // clang-format off
    auto validate = [this](int x, int y) -> bool {
        return x >= 0 && y >= 0 && 
                x < N_ && y < M_ &&
                !visited_[x][y]; 
    };
    // clang-format on

    while (!candidates_.empty())
    {
        auto& candidate = candidates_.front();
        for (int i = 0; i < 4; i++)
        {
            CoordWithDist next{candidate.x + dx[i], candidate.y + dy[i], candidate.dist + 1};
            if (!validate(next.x, next.y))
                continue;

            if (data_[next.x][next.y] == dest)
                return next.dist;

            candidates_.push(next);
        }

        candidates_.pop();
    }

    throw std::runtime_error("Destination or source not found");
}
