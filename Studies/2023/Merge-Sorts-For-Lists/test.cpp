#include "small_test_framework.h"
#include "linked_list.hpp"

#include <vector>

template <Printable T>
class PrintableVector: public std::vector<T>
{
public:
    template <typename U> 
    friend std::ostream& operator<< (std::ostream &os, const PrintableVector<U>& other);
};

template <Printable T>
std::ostream &operator<<(std::ostream &os, const PrintableVector<T> &v)
{
    os << "{ ";
    for (const auto &el : v)
        os << el << " ";
    os << "}";
    return os;
}

TEST_MAIN_BEGIN()

UNIT_TEST_BEGIN(linked_list, basic)
{
    {
        LinkedList<int> ll{1, 2, 3, 4, 5};
        EXPECT_EQ(ll.length(), 5);

        PrintableVector<int> ref_val;

        ll.push_back(6);
        ref_val.assign({1, 2, 3, 4, 5, 6});
        EXPECT_EQ(ll, ref_val);

        ll.push_front(0);
        ref_val.assign({0, 1, 2, 3, 4, 5, 6});
        EXPECT_EQ(ll, ref_val);
    }

    {
        LinkedList<int> ll{1, 2, 3};
        EXPECT_EQ(ll.length(), 3);

        PrintableVector<int> ref_val;

        ll.pop_back();
        ref_val.assign({1, 2});
        EXPECT_EQ(ll, ref_val);

        ll.pop_front();
        ref_val.assign({2});
        EXPECT_EQ(ll, ref_val);

        ll.pop_front();
        ref_val.clear();
        EXPECT_EQ(ll, ref_val);

        //ll = {1};
        ll.push_back(1);
        ll.pop_back();
        EXPECT_EQ(ll, ref_val);
    }
}
UNIT_TEST_END(linked_list, basic)

TEST_MAIN_END()
