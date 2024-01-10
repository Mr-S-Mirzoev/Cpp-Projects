#include <gtest/gtest.h>

#include "sparse_vector.h"

template <typename T>
class SparseVectorTest : public ::testing::Test
{
};

// Define the types for which you want to run the tests
typedef ::testing::Types<SparseVectorMBased<int>, SparseVectorVBased<int>> SparseVectorTypes;

// Register the test suite with the types
TYPED_TEST_SUITE(SparseVectorTest, SparseVectorTypes);

// Test for creating SparseVectorVBased from std::vector
TYPED_TEST(SparseVectorTest, CreateFromStdVector)
{
    std::vector<int> vec = {0, 1, 0, 3};
    TypeParam sparseVec(vec);

    std::vector<int> expectedVec = {0, 1, 0, 3};
    EXPECT_EQ(sparseVec.get(), expectedVec);
}

// Test for copy constructor
TYPED_TEST(SparseVectorTest, CopyConstructor)
{
    TypeParam original({0, 1, 0, 3});
    TypeParam copy = original;

    EXPECT_EQ(copy.get(), original.get());
}

// Test for addition assignment operator
TYPED_TEST(SparseVectorTest, AdditionAssignment)
{
    TypeParam sv1({0, 1, 0, 3});
    TypeParam sv2({1, 0, 2, 0});
    sv1 += sv2;

    std::vector<int> expectedVec = {1, 1, 2, 3};
    EXPECT_EQ(sv1.get(), expectedVec);
}

// Test for addition assignment with zero vector
TYPED_TEST(SparseVectorTest, AdditionAssignmentWithZeroVector)
{
    TypeParam sv1({0, 1, 0, 3});
    TypeParam sv2({0, 0, 0, 0});
    sv1 += sv2;

    std::vector<int> expectedVec = {0, 1, 0, 3};
    EXPECT_EQ(sv1.get(), expectedVec);
}

// Test for size mismatch exception in addition assignment
TYPED_TEST(SparseVectorTest, AdditionAssignmentSizeMismatch)
{
    TypeParam sv1({0, 1, 0, 3});
    TypeParam sv2({1, 0, 2});

    EXPECT_THROW(sv1 += sv2, std::runtime_error);
}

// Test for empty vector addition assignment
TYPED_TEST(SparseVectorTest, AdditionVector)
{
    TypeParam sv1({0, 1, 0, 3, 0});
    TypeParam sv2({0, 0, 1, 0, 0});

    std::vector<int> expectedVec = {0, 1, 1, 3, 0};
    EXPECT_EQ((sv1 + sv2).get(), expectedVec);
}
