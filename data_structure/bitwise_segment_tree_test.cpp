#include "gtest/gtest.h"
#include "bitwise_segment_tree.hpp"

TEST(BitwiseSegmentTreeTest, Basic) {
    const std::vector vec = {1, 2, 3, 4, 5, 4, 3, 2, 1};

    algo::SegmentTree<int, algo::SumOp> sumT(vec);
    algo::SegmentTree<int, algo::MinOp> minT(vec);
    algo::SegmentTree<int, algo::MaxOp> maxT(vec.size());
    for (int i = 0; i < vec.size(); i++) maxT.update(i, vec[i]);

    EXPECT_EQ(sumT.query(0, 5), 19);
    EXPECT_EQ(sumT.query(1, 3), 9);
}

