#include <iostream>
#include <set>
#include <vector>

unsigned safe_sub(unsigned a, unsigned b)
{
    if (a <= b)
        return 0u;

    return a - b;
}

bool is_it_possible(std::vector<unsigned> const& helis, std::set<unsigned> pads, unsigned D)
{ // O(N * log(M))
    for (auto heli : helis)
    {                                                  // O(N)
        auto it = pads.lower_bound(safe_sub(heli, D)); // O(log(M))
        if (it == pads.end())
        {
            return false;
        }

        if (*it > heli + D)
        {
            return false;
        }

        pads.erase(it); // O(log(M))
    }

    return true;
}

unsigned safe_max(unsigned A, unsigned B)
{
    if (A > B)
        return A - B;
    else
        return B - A;
}

unsigned minimal_assignment_time(std::vector<unsigned> const& helis,
                                 std::vector<unsigned> const& pads)
{
    std::set<unsigned> pads_tree(pads.begin(), pads.end());

    //   X  X X    X
    //                   H      H   H  H H

    //                     X  X X    X
    // H      H   H  H H

    // find max and min
    auto min_it = pads_tree.lower_bound(helis[0]);
    unsigned min = 0;
    if (min_it != pads_tree.end())
    {
        if (min_it != pads_tree.begin())
        {
            auto prev = min_it;
            --prev;
            min = std::min(helis[0] - *prev, *min_it - helis[0]);
        }
        else
        {
            min = *min_it - helis[0];
        }
    }
    else
    {
        min = helis[0] - *(pads.rbegin());
    }

    unsigned max = std::max(safe_max(*helis.begin(), *pads.rbegin()),
                            safe_max(*helis.rbegin(), *pads.begin()));

    unsigned l = min, r = max;
    while (l < r)
    {
        unsigned m = (l + r) >> 1;
        bool possible = is_it_possible(helis, pads_tree, m);
        if (!possible)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }
    return l;
}

int main(int argc, char const* argv[])
{
    unsigned H, L;
    std::cin >> H >> L;
    // For example: {2, 5, 7, 12}
    std::vector<unsigned> helis(H);
    // For example: {0, 7, 11, 14, 16}
    std::vector<unsigned> pads(L);

    for (unsigned i = 0; i < H; ++i)
        std::cin >> helis[i];

    for (unsigned i = 0; i < L; ++i)
        std::cin >> pads[i];

    std::cout << minimal_assignment_time(helis, pads) << std::endl;
    return 0;
}
