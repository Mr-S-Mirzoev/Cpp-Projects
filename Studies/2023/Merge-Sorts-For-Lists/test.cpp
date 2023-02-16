#include "small_test_framework.h"

#include "algorithms.hpp"
#include "linked_list.hpp"
#include "printable_vector.hpp"

#include <sstream>

TEST_MAIN_BEGIN()

UNIT_TEST_BEGIN(linked_list, basic)
{
    LinkedList<int> ll{1, 2, 3, 4, 5};
    EXPECT_EQ(ll.size(), 5);

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
    EXPECT_EQ(ll.size(), 3);

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
    EXPECT_FALSE(ll.empty());

    {
        const LinkedList<int> ll_copy{ll};
        EXPECT_EQ(ll_copy.front(), 2);
        EXPECT_EQ(ll_copy.back(), 2);
    }

    ll.pop_front();
    ref_val.clear();
    EXPECT_EQ(ll, ref_val);
    EXPECT_TRUE(ll.empty());

    ll = {1};
    ll.pop_back();
    EXPECT_EQ(ll, ref_val);
    EXPECT_TRUE(ll.empty());

    ll.push_back(1);
    ll.pop_back();
    EXPECT_EQ(ll, ref_val);
    EXPECT_TRUE(ll.empty());

    ll = {};
    EXPECT_EQ(ll, ref_val);
    EXPECT_TRUE(ll.empty());

    ll.push_back(2);
    ref_val.assign({2});
    EXPECT_EQ(ll, ref_val);

    ll.emplace_back(4);
    ref_val.assign({2, 4});
    EXPECT_EQ(ll, ref_val);
}
UNIT_TEST_END(linked_list, pop_push)

UNIT_TEST_BEGIN(linked_list, divide_and_concat)
{
    {
        LinkedList<int> ll{1, 2, 3};
        auto half = divide(ll);

        PrintableVector<int> ref_val;

        ref_val.assign({1});
        EXPECT_EQ(ll, ref_val);

        ref_val.assign({2, 3});
        EXPECT_EQ(half, ref_val);

        auto new_ll = concat(ll, std::move(half));
        ref_val.assign({1, 2, 3});
        EXPECT_EQ(new_ll, ref_val);
        EXPECT_TRUE(half.empty());
    }

    {
        LinkedList<int> ll{1, 2, 3, 4};
        auto half = divide(ll);

        PrintableVector<int> ref_val;

        ref_val.assign({1, 2});
        EXPECT_EQ(ll, ref_val);

        ref_val.assign({3, 4});
        EXPECT_EQ(half, ref_val);

        auto new_ll = concat(ll, std::move(half));
        ref_val.assign({1, 2, 3, 4});
        EXPECT_EQ(new_ll, ref_val);
        EXPECT_TRUE(half.empty());
    }
}
UNIT_TEST_END(linked_list, divide_and_concat)

UNIT_TEST_BEGIN(linked_list, sort)
{
    {
        LinkedList<int> ll{1, 2, 3, 4, 5};
        merge_sort(ll);

        PrintableVector<int> ref_val;
        ref_val.assign({1, 2, 3, 4, 5});
        EXPECT_EQ(ll, ref_val);
    }

    {
        LinkedList<int> ll{3, 1, 0, 4, 2, 5};
        merge_sort(ll);

        PrintableVector<int> ref_val;
        ref_val.assign({0, 1, 2, 3, 4, 5});
        EXPECT_EQ(ll, ref_val);
    }
}
UNIT_TEST_END(linked_list, sort)

UNIT_TEST_BEGIN(linked_list, print)
{
    LinkedList<int> ll{1, 2, 3, 4, 5};
    std::stringstream ss;
    ss << ll;
    EXPECT_EQ(ss.str(), "{ 1 2 3 4 5 }");
}
UNIT_TEST_END(linked_list, print)

TEST_MAIN_END()
