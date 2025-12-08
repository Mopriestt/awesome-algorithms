#include "gtest/gtest.h"
#include "disjoint_set.hpp"

TEST(DisjointSetTest, Basic) {
    const std::vector<int> vec = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    const int n = static_cast<int>(vec.size());

    algo::DisjointSet dsu(n);

    // Initialize per-node values: use set_value(i, a[i])
    // Convention: DSU uses 1-based indices, vec is 0-based.
    for (int i = 1; i <= n; ++i) {
        dsu.setValue(i, vec[i - 1]);
    }

    // Initially, each element is its own set
    for (int i = 1; i <= n; ++i) {
        EXPECT_EQ(dsu.getSize(i), 1);
        EXPECT_EQ(dsu.getSum(i), vec[i - 1]);
        EXPECT_EQ(dsu.getMax(i), vec[i - 1]);
        EXPECT_EQ(dsu.getMin(i), vec[i - 1]);
    }

    // Merge [1,2,3] into one component
    dsu.merge(1, 2);
    dsu.merge(2, 3);
    // Component {1,2,3} -> values [1,2,3]
    EXPECT_EQ(dsu.getSize(1), 3);
    EXPECT_EQ(dsu.getSize(2), 3);
    EXPECT_EQ(dsu.getSize(3), 3);

    EXPECT_EQ(dsu.getSum(1), 1 + 2 + 3);
    EXPECT_EQ(dsu.getSum(2), 1 + 2 + 3);
    EXPECT_EQ(dsu.getSum(3), 1 + 2 + 3);

    EXPECT_EQ(dsu.getMax(1), 3);
    EXPECT_EQ(dsu.getMin(1), 1);

    // Merge [4,5,6] into another component
    dsu.merge(4, 5);
    dsu.merge(5, 6);
    // Component {4,5,6} -> values [4,5,4]
    EXPECT_EQ(dsu.getSize(4), 3);
    EXPECT_EQ(dsu.getSize(5), 3);
    EXPECT_EQ(dsu.getSize(6), 3);

    EXPECT_EQ(dsu.getSum(4), 4 + 5 + 4);
    EXPECT_EQ(dsu.getMax(4), 5);
    EXPECT_EQ(dsu.getMin(4), 4);

    // Merge the two components: {1,2,3} U {4,5,6}
    dsu.merge(1, 4);
    // Component {1,2,3,4,5,6} -> values [1,2,3,4,5,4]
    const int mergedSize = 6;
    const int mergedSum  = 1 + 2 + 3 + 4 + 5 + 4;
    const int mergedMax  = 5;
    const int mergedMin  = 1;

    for (int u : {1,2,3,4,5,6}) {
        EXPECT_EQ(dsu.getSize(u), mergedSize);
        EXPECT_EQ(dsu.getSum(u), mergedSum);
        EXPECT_EQ(dsu.getMax(u), mergedMax);
        EXPECT_EQ(dsu.getMin(u), mergedMin);
    }

    // Elements 7,8,9 are still singletons
    EXPECT_EQ(dsu.getSize(7), 1);
    EXPECT_EQ(dsu.getSum(7), vec[6]);  // 3
    EXPECT_EQ(dsu.getMax(7), vec[6]);  // 3
    EXPECT_EQ(dsu.getMin(7), vec[6]);  // 3;

    EXPECT_EQ(dsu.getSize(9), 1);
    EXPECT_EQ(dsu.getSum(9), vec[8]);  // 1
    EXPECT_EQ(dsu.getMax(9), vec[8]);  // 1
    EXPECT_EQ(dsu.getMin(9), vec[8]);  // 1

    // Merge everything into one big component
    dsu.merge(6, 7);
    dsu.merge(7, 8);
    dsu.merge(8, 9);
    // All nodes {1..9} now connected
    int totalSize = 9;
    int totalSum  = 0;
    for (int v : vec) totalSum += v;   // 1+2+3+4+5+4+3+2+1 = 25
    int totalMax  = 5;
    int totalMin  = 0; // still 1..9 original, but we never changed any to 0, so min = 1 actually

    totalMin = 1;

    for (int u = 1; u <= n; ++u) {
        EXPECT_EQ(dsu.getSize(u), totalSize);
        EXPECT_EQ(dsu.getSum(u), totalSum);
        EXPECT_EQ(dsu.getMax(u), totalMax);
        EXPECT_EQ(dsu.getMin(u), totalMin);
    }
}
