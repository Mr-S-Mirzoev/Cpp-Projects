#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

struct Point
{
    int x, y;
};

class Solution
{
    struct PairHasher
    {
        std::size_t operator()(std::pair<int, int> p) const
        {
            long long v = p.first;
            v = (v << 32) + p.second;
            return std::hash<long long>()(v);
        }
    };

    // (k, b) from y = kx + b
    std::unordered_map<std::pair<int, int>, unsigned, PairHasher> lines;
    unsigned max = 1;

public:
    int maxPoints(std::vector<Point>& points)
    {
        std::size_t sz = points.size();
        int slope_x, slope_y, del;
        for (std::size_t i = 0; i < sz - 1; ++i)
        {
            for (std::size_t j = i + 1; j < sz; ++j)
            {
                slope_x = points[j].y - points[i].y;
                slope_y = points[j].x - points[i].x;
                del = std::__detail::__gcd(slope_x, slope_y);
                slope_x /= del;
                slope_y /= del;

                if (slope_x < 0)
                {
                    slope_x = -slope_x;
                    slope_y = -slope_y;
                }
                else if (slope_x * slope_y == 0)
                {
                    slope_x = std::abs(slope_x);
                    slope_y = std::abs(slope_y);
                }

                auto it = lines.find({slope_x, slope_y});
                if (it == lines.end())
                {
                    lines.insert({{slope_x, slope_y}, 2}); // since line connects 2 points
                    max = std::max(max, 2u);
                }
                else
                {
                    max = std::max(max, ++(it->second));
                }

#ifdef PRINT
                std::cout << "{" << slope_x << ", " << slope_y << "}; (" << points[i].x << ", "
                          << points[i].y << "); (" << points[j].x << ", " << points[j].y << ")"
                          << std::endl;
#endif // PRINT
            }

            lines.clear();
        }

#ifdef PRINT
        for (auto el : lines)
            std::cout << "[" << el.first.first << ", " << el.first.second << "] " << el.second
                      << std::endl;
#endif // PRINT

        return max;
    }
};

int main(int argc, char const* argv[])
{
    // std::vector <Point> points =  {{0,1},{0,0},{0,4},{0,-2},{0,-1},{0,3},{0,-4}};
    std::vector<Point> points = {{2, 3}, {3, 3}, {-5, 3}};
    Solution s;
    std::cout << s.maxPoints(points) << std::endl;
    return 0;
}
