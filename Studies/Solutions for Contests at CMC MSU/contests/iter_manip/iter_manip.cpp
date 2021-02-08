#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

template <typename Iter, typename Func>
void myapply (Iter begin, Iter end, Func c)
{
    Iter it;
    it = begin;
    for (; it != end; ++it) {
        c(*it);
    }
}

template <typename It, typename Pr>
vector <reference_wrapper <typename iterator_traits <It>::value_type> > myfilter2 (It begin, It end, Pr c)
{
    It it = begin;
    vector <reference_wrapper <typename iterator_traits <It>::value_type> > x;
    for (; it != end; ++it) {
        if (c(*it)) {
            x.insert(x.end(), *it);
        }
    }
    return x;
}
