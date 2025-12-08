#include "gtest/gtest.h"
#include "disjoint_set_2d.hpp"  // 换成你实际的头文件名

TEST(DisjointSet2DTest, Basic) {
    // 3x3 grid:
    // [ 1 2 3 ]
    // [ 4 5 6 ]
    // [ 7 8 9 ]
    const int n = 3, m = 3;
    const int vals[n][m] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    algo::DisjointSet2D dsu(n, m);

    // Initialize values
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            dsu.setValue(r, c, vals[r][c]);
        }
    }

    // Initially, each cell is its own component
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            EXPECT_EQ(dsu.getSize(r, c), 1);
            EXPECT_EQ(dsu.getSum(r, c), vals[r][c]);
            EXPECT_EQ(dsu.getMax(r, c), vals[r][c]);
            EXPECT_EQ(dsu.getMin(r, c), vals[r][c]);

            auto root = dsu.find(r, c);
            EXPECT_EQ(root.first, r);
            EXPECT_EQ(root.second, c);
        }
    }

    // Merge a plus-shape centered at (1,1):
    // cells: (1,1), (0,1), (1,0), (1,2), (2,1)
    dsu.merge(1, 1, 0, 1); // 5 with 2
    dsu.merge(1, 1, 1, 0); // + 4
    dsu.merge(1, 1, 1, 2); // + 6
    dsu.merge(1, 1, 2, 1); // + 8

    // Component values: {2,4,5,6,8}
    const int compSize = 5;
    const int compSum  = 2 + 4 + 5 + 6 + 8;
    const int compMax  = 8;
    const int compMin  = 2;

    const std::pair<int,int> cells[] = {
        {1,1}, {0,1}, {1,0}, {1,2}, {2,1}
    };

    // All plus-shape cells should share the same root and attributes
    auto root01 = dsu.find(1, 1);
    for (auto [r, c] : cells) {
        EXPECT_EQ(dsu.getSize(r, c), compSize);
        EXPECT_EQ(dsu.getSum(r, c), compSum);
        EXPECT_EQ(dsu.getMax(r, c), compMax);
        EXPECT_EQ(dsu.getMin(r, c), compMin);

        auto rt = dsu.find(r, c);
        EXPECT_EQ(rt.first, root01.first);
        EXPECT_EQ(rt.second, root01.second);
    }

    // Corners remain singleton components:
    // (0,0) -> 1
    EXPECT_EQ(dsu.getSize(0, 0), 1);
    EXPECT_EQ(dsu.getSum(0, 0), 1);
    EXPECT_EQ(dsu.getMax(0, 0), 1);
    EXPECT_EQ(dsu.getMin(0, 0), 1);

    // (0,2) -> 3
    EXPECT_EQ(dsu.getSize(0, 2), 1);
    EXPECT_EQ(dsu.getSum(0, 2), 3);
    EXPECT_EQ(dsu.getMax(0, 2), 3);
    EXPECT_EQ(dsu.getMin(0, 2), 3);

    // (2,0) -> 7
    EXPECT_EQ(dsu.getSize(2, 0), 1);
    EXPECT_EQ(dsu.getSum(2, 0), 7);
    EXPECT_EQ(dsu.getMax(2, 0), 7);
    EXPECT_EQ(dsu.getMin(2, 0), 7);

    // (2,2) -> 9
    EXPECT_EQ(dsu.getSize(2, 2), 1);
    EXPECT_EQ(dsu.getSum(2, 2), 9);
    EXPECT_EQ(dsu.getMax(2, 2), 9);
    EXPECT_EQ(dsu.getMin(2, 2), 9);

    // Finally, connect all corners into the big component via center (1,1)
    dsu.merge(0, 0, 1, 1);
    dsu.merge(0, 2, 1, 1);
    dsu.merge(2, 0, 1, 1);
    dsu.merge(2, 2, 1, 1);

    // All 9 cells now in one component
    int totalSum = 0;
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            totalSum += vals[r][c]; // 1..9 sum = 45

    const int totalSize = 9;
    const int totalMax  = 9;
    const int totalMin  = 1;

    auto globalRoot = dsu.find(1, 1);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            EXPECT_EQ(dsu.getSize(r, c), totalSize);
            EXPECT_EQ(dsu.getSum(r, c), totalSum);
            EXPECT_EQ(dsu.getMax(r, c), totalMax);
            EXPECT_EQ(dsu.getMin(r, c), totalMin);

            auto rt = dsu.find(r, c);
            EXPECT_EQ(rt.first,  globalRoot.first);
            EXPECT_EQ(rt.second, globalRoot.second);
        }
    }
}
