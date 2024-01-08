#include <gtest/gtest.h>

#include "algorithms.hpp"
#include "linked_list.hpp"
#include "printable_vector.hpp"

#include <sstream>

TEST(LinkedList, BasicEmpty)
{
    LinkedList<int> ll;
    EXPECT_TRUE(ll.empty());
    EXPECT_EQ(ll.size(), 0);

    ll.push_back(1);
    EXPECT_FALSE(ll.empty());
    EXPECT_EQ(ll.size(), 1);

    ll.push_back(2);
    EXPECT_EQ(ll, PrintableVector<int>({1, 2}));
}

TEST(LinkedList, BasicNonEmpty)
{
    LinkedList<int> ll{1, 2, 3, 4, 5};
    EXPECT_EQ(ll.size(), 5);

    ll.push_back(6);
    EXPECT_EQ(ll.size(), 6);
    EXPECT_EQ(ll, PrintableVector<int>({1, 2, 3, 4, 5, 6}));

    ll.push_front(0);
    EXPECT_EQ(ll.size(), 7);
    EXPECT_EQ(ll, PrintableVector<int>({0, 1, 2, 3, 4, 5, 6}));
}

TEST(LinkedList, BasicAccessors)
{
    LinkedList<int> ll{1, 2, 3};
    EXPECT_EQ(ll.front(), 1);
    EXPECT_EQ(ll.back(), 3);
    EXPECT_EQ(ll.size(), 3);

    ll.front() = 4;

    EXPECT_EQ(ll.front(), 4);
    EXPECT_EQ(ll.back(), 3);
    EXPECT_EQ(ll.size(), 3);

    ll.back() = 5;

    EXPECT_EQ(ll.front(), 4);
    EXPECT_EQ(ll.back(), 5);
    EXPECT_EQ(ll.size(), 3);

    EXPECT_EQ(ll, PrintableVector<int>({4, 2, 5}));
}

TEST(LinkedList, Copy)
{
    LinkedList<int> ll{1, 2, 3};
    LinkedList<int> ll_copy{ll};

    EXPECT_EQ(ll_copy.front(), 1);
    EXPECT_EQ(ll_copy.back(), 3);
    EXPECT_EQ(ll_copy.size(), 3);

    ll_copy.front() = 4;

    EXPECT_EQ(ll_copy.front(), 4);
    EXPECT_EQ(ll_copy.back(), 3);
    EXPECT_EQ(ll_copy.size(), 3);

    EXPECT_EQ(ll, PrintableVector<int>({1, 2, 3}));
    EXPECT_EQ(ll_copy, PrintableVector<int>({4, 2, 3}));
}

TEST(LinkedList, PopPush)
{
    LinkedList<int> ll{1, 2, 3};
    EXPECT_FALSE(ll.empty());

    ll.pop_back();
    EXPECT_EQ(ll.front(), 1);
    EXPECT_EQ(ll.back(), 2);

    ll.pop_front();

    EXPECT_EQ(ll.front(), 2);
    EXPECT_EQ(ll.back(), 2);

    ll.pop_front();
    EXPECT_TRUE(ll.empty());

    ll.push_back(-1);
    EXPECT_EQ(ll.front(), -1);
    EXPECT_EQ(ll.back(), -1);
    EXPECT_FALSE(ll.empty());

    ll.push_front(-2);
    EXPECT_EQ(ll.front(), -2);
    EXPECT_EQ(ll.back(), -1);
    EXPECT_FALSE(ll.empty());

    EXPECT_EQ(ll, PrintableVector<int>({-2, -1}));

    ll.pop_back();
    EXPECT_EQ(ll.front(), -2);
    EXPECT_EQ(ll.back(), -2);
    EXPECT_FALSE(ll.empty());

    ll.pop_back();
    EXPECT_TRUE(ll.empty());

    ll.push_front(1);
    EXPECT_EQ(ll.front(), 1);
    EXPECT_EQ(ll.back(), 1);
    EXPECT_FALSE(ll.empty());
}

TEST(LinkedList, DivideAndConcat)
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

TEST(LinkedList, Sort)
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

TEST(LinkedList, Print)
{
    LinkedList<int> ll{1, 2, 3, 4, 5};
    std::stringstream ss;
    ss << ll;
    EXPECT_EQ(ss.str(), "{ 1 2 3 4 5 }");
}
