#include "gtest/gtest.h"
#include "bitwise_segment_tree.hpp"

TEST(BitwiseSegmentTreeTest, Basic) {
    const std::vector vec = {1, 2, 3, 4, 5, 4, 3, 2, 1};

    algo::SegmentTree<int, algo::SumOp> sumT(vec);
    algo::SegmentTree<int, algo::MinOp> minT(vec);
    algo::SegmentTree<int, algo::MaxOp> maxT(static_cast<int>(vec.size()));
    for (int i = 0; i < static_cast<int>(vec.size()); ++i) {
        maxT.update(i, vec[i]);
    }

    // Initial queries
    EXPECT_EQ(sumT.query(0, 5), 19);  // 1+2+3+4+5+4
    EXPECT_EQ(sumT.query(1, 3), 9);   // 2+3+4
    EXPECT_EQ(sumT.query(0, 8), 25);  // total sum

    EXPECT_EQ(minT.query(0, 8), 1);
    EXPECT_EQ(minT.query(2, 6), 3);   // min of [3,4,5,4,3]

    EXPECT_EQ(maxT.query(0, 8), 5);
    EXPECT_EQ(maxT.query(3, 5), 5);   // max of [4,5,4]

    // rangeAdd: a[i] += 1 for all i
    sumT.rangeAdd(0, 8, 1);
    minT.rangeAdd(0, 8, 1);
    maxT.rangeAdd(0, 8, 1);
    // vec -> [2,3,4,5,6,5,4,3,2]
    EXPECT_EQ(sumT.query(0, 8), 34);  // 25 + 9 * 1
    EXPECT_EQ(minT.query(0, 8), 2);
    EXPECT_EQ(maxT.query(0, 8), 6);

    // rangeUpdate: set [2..4] = 10
    sumT.rangeUpdate(2, 4, 10);
    minT.rangeUpdate(2, 4, 10);
    maxT.rangeUpdate(2, 4, 10);
    // vec -> [2,3,10,10,10,5,4,3,2]
    EXPECT_EQ(sumT.query(0, 8), 49);  // 2+3+10+10+10+5+4+3+2
    EXPECT_EQ(minT.query(0, 8), 2);
    EXPECT_EQ(maxT.query(0, 8), 10);

    // point update: a[0] = 0
    sumT.update(0, 0);
    minT.update(0, 0);
    maxT.update(0, 0);
    // vec -> [0,3,10,10,10,5,4,3,2]
    EXPECT_EQ(sumT.query(0, 8), 47);

    // point add: a[8] += 5
    sumT.add(8, 5);
    minT.add(8, 5);
    maxT.add(8, 5);
    // vec -> [0,3,10,10,10,5,4,3,7]
    EXPECT_EQ(sumT.query(0, 8), 52);  // 47 + 5
    EXPECT_EQ(minT.query(0, 8), 0);
    EXPECT_EQ(maxT.query(0, 8), 10);
}
