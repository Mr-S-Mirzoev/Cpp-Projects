#include "small_test_framework.h"

#include "linked_list.hpp"
#include "printable_vector.hpp"

TEST_MAIN_BEGIN()

UNIT_TEST_BEGIN(linked_list, basic)
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
UNIT_TEST_END(linked_list, basic)

UNIT_TEST_BEGIN(linked_list, pop_push)
{
    LinkedList<int> ll{1, 2, 3};
    EXPECT_EQ(ll.front(), 1);
    EXPECT_EQ(ll.back(), 3);
    EXPECT_EQ(ll.length(), 3);

    PrintableVector<int> ref_val;

    ll.pop_back();
    ref_val.assign({1, 2});
    EXPECT_EQ(ll.front(), 1);
    EXPECT_EQ(ll.back(), 2);
    EXPECT_EQ(ll, ref_val);

    ll.pop_front();
    ref_val.assign({2});
    EXPECT_EQ(ll.front(), 2);
    EXPECT_EQ(ll.back(), 2);
    EXPECT_EQ(ll, ref_val);

    {
        const LinkedList<int> ll_copy{ll};
        EXPECT_EQ(ll_copy.front(), 2);
        EXPECT_EQ(ll_copy.back(), 2);
    }

    ll.pop_front();
    ref_val.clear();
    EXPECT_EQ(ll, ref_val);

    ll = {1};
    ll.pop_back();
    EXPECT_EQ(ll, ref_val);

    ll.push_back(1);
    ll.pop_back();
    EXPECT_EQ(ll, ref_val);

    ll = {};
    EXPECT_EQ(ll, ref_val);
}
UNIT_TEST_END(linked_list, pop_push)

TEST_MAIN_END()
