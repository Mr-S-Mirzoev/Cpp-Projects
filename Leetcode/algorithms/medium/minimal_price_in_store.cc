#include <vector>
#include <algorithm>
#include <iostream>

int shoppingOffers(std::vector<int>& price, std::vector<std::vector<int>>& special, std::vector<int>& needs) {
    std::sort(special.begin(), special.end(), [price](const std::vector<int> &l, const std::vector<int> &r){
        if (l.back() < r.back())
            return true;
        else if (l.back() > r.back())
            return false;

        int first = 0, second = 0;
        int n = price.size();
        for (int i = 0; i < n; ++i) {
            first += price[i] * l[i];
            second += price[i] * r[i];
        }

        return first > second;
    });

    std::size_t last = 0;
    int sum = 0;
    while (last != special.size() - 1) {
        bool all_wrong = true;
        for (std::size_t i = last; i < special.size(); ++i) {
            bool some_fine = true;
            for (std::size_t j = 0; j < needs.size(); ++j)
                if (special[i][j] > needs[j]) {
                    some_fine = false;
                    break;
                }

            if (some_fine) {
                last = i;
                all_wrong = false;
                break;
            }
        }

        if (all_wrong)
            break;

        for (std::size_t j = 0; j < needs.size(); ++j)
            needs[j] -= special[last][j];
        sum += special[last].back();
    }

    for (std::size_t j = 0; j < needs.size(); ++j)
        sum += price[j] * needs[j];

    return sum;
}

int main(int argc, char const *argv[])
{
    /*
    [2,5]
    [[3,0,5],[1,2,10]]
    [3,2]
    */
    std::vector <int> a{2, 5};
    std::vector <std::vector <int>> b{
        {3, 0, 5},
        {1, 2, 10}
    };
    std::vector <int> c{3, 2};

    std::cout << shoppingOffers(a, b, c) << std::endl;
    return 0;
}
