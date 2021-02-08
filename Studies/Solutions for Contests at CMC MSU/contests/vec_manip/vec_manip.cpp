#include <vector>
#include <iterator>
#include <algorithm>

void process (const std::vector <int> &v1, std::vector <int> &v2)
{
    std::vector <int> copy(v1);
    if (v1.size() == 0 || v2.size() == 0) {
        return;
    }
    std::sort(copy.begin(),copy.end());
    auto it = std::unique (copy.begin(), copy.end());
    copy.resize(std::distance(copy.begin(),it));
    auto v2_it = v2.begin();
    auto v1_it = copy.begin();
    int sz = v2.size(), k = 0;
    while (v1_it != copy.end() && *v1_it < 0) {
        ++v1_it;
    }
    it = v1_it;
    while (it != copy.end() && *v1_it < sz) {
        ++it;
    }
    for (int i = 0; v2_it != v2.end(); i++) {
        if (i != *v1_it) {
            *v2_it = *(v2_it + k);
            ++v2_it;
        } else {
            if (*v1_it < sz) {
                k++;
                ++v1_it;
            }
        }
    }
    v2.resize(sz - k);
}
