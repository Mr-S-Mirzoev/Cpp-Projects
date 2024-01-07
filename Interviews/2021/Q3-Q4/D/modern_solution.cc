#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <vector>

bool is_solvable_with_time(const std::vector<unsigned>& helis, std::set<unsigned> pads,
                           unsigned time)
{
    if (helis.size() > pads.size())
        return false;

    for (auto heli : helis)
    {
        // Try to land on the pad that is the closest to the heli, and not further than `time` away
        // to the left.
        auto it = pads.lower_bound(heli > time ? heli - time : 0);
        if (it == pads.end())
            return false;

        // If the pad is further than `time` away to the right, it's not possible to land on it.
        if (*it > heli + time)
            return false;

        pads.erase(it);
    }

    return true;
}

unsigned minimal_assignment_time(const std::vector<unsigned>& helis,
                                 const std::vector<unsigned>& pads)
{
    if (helis.empty() || pads.empty())
        return -1;

    if (helis.size() > pads.size())
        return -1;

    const std::set<unsigned> pads_set(pads.begin(), pads.end());

    unsigned left = [&helis, &pads_set]()
    {
        auto closest_pad_after_first_heli_it = pads_set.lower_bound(helis.front());
        if (closest_pad_after_first_heli_it == pads_set.end())
            return helis.front() - *pads_set.rbegin();

        auto dist_to_right = *closest_pad_after_first_heli_it - helis[0];
        if (closest_pad_after_first_heli_it == pads_set.begin())
            return *closest_pad_after_first_heli_it - helis[0];

        auto closest_pad_before_first_heli_it = closest_pad_after_first_heli_it;
        std::advance(closest_pad_before_first_heli_it, -1);
        auto dist_to_left = helis[0] - *closest_pad_before_first_heli_it;

        return std::min(dist_to_left, dist_to_right);
    }();
    unsigned right = [&helis, &pads_set]()
    {
        auto abs_diff = [](unsigned a, unsigned b) { return (a > b) ? a - b : b - a; };

        return std::max(abs_diff(*pads_set.rbegin(), *helis.begin()),
                        abs_diff(*pads_set.begin(), *helis.rbegin()));
    }();

    std::cout << "left: " << left << ", right: " << right << std::endl;

    auto range = std::ranges::views::iota(left, right);
    auto partition_point =
        std::ranges::partition_point(range, [&helis, &pads_set](unsigned time)
                                     { return is_solvable_with_time(helis, pads_set, time); });
    if (partition_point == range.end())
        return -1;

    return *partition_point;
}

int main(int argc, char const* argv[])
{
    unsigned H, L;
    std::cout << "Enter helis count: " << std::endl;
    std::cin >> H;
    std::cout << "Enter pads count: " << std::endl;
    std::cin >> L;

    // For example: {2, 5, 7, 12}
    std::vector<unsigned> helis(H);
    // For example: {0, 7, 11, 14, 16}
    std::vector<unsigned> pads(L);

    std::cout << "Enter helis: " << std::endl;
    for (unsigned i = 0; i < H; ++i)
        std::cin >> helis[i];

    std::cout << "Enter pads: " << std::endl;
    for (unsigned i = 0; i < L; ++i)
        std::cin >> pads[i];

    std::cout << minimal_assignment_time(helis, pads) << std::endl;
    return 0;
}
