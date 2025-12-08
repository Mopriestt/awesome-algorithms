#include "gtest/gtest.h"
#include "single_update_segment_tree.hpp"

TEST(SingleUpdateSegmentTreeTest, Basic) {
    const std::vector<int> vec = {1, 2, 3, 4, 5};

    algo::SingleUpdateSegmentTree<int, algo::SumOp> sumT(vec);
    algo::SingleUpdateSegmentTree<int, algo::MinOp> minT(vec);
    algo::SingleUpdateSegmentTree<int, algo::MaxOp> maxT(vec);

    // initial queries
    EXPECT_EQ(sumT.query(0, 4), 15);   // 1+2+3+4+5
    EXPECT_EQ(sumT.query(1, 3), 9);    // 2+3+4

    EXPECT_EQ(minT.query(0, 4), 1);
    EXPECT_EQ(minT.query(2, 4), 3);

    EXPECT_EQ(maxT.query(0, 4), 5);
    EXPECT_EQ(maxT.query(1, 3), 4);

    // point update via API
    sumT.update(0, 10);   // [10,2,3,4,5]
    EXPECT_EQ(sumT.query(0, 0), 10);
    EXPECT_EQ(sumT.query(0, 4), 24);

    // point add via API
    sumT.add(1, 5);       // [10,7,3,4,5]
    EXPECT_EQ(sumT.query(0, 1), 17);
    EXPECT_EQ(sumT.query(0, 4), 29);

    // operator[] sugar: assign / += / -=
    sumT[2] = 100;        // [10,7,100,4,5]
    EXPECT_EQ(sumT.query(2, 2), 100);

    sumT[3] += 3;         // [10,7,100,7,5]
    EXPECT_EQ(sumT.query(3, 3), 7);

    sumT[4] -= 2;         // [10,7,100,7,3]
    EXPECT_EQ(sumT.query(4, 4), 3);

    EXPECT_EQ(sumT.query(0, 4), 127);  // 10+7+100+7+3

    // operator[] sugar works on min / max too (through update/add)
    maxT[0] = 42;
    maxT[1] += 10;        // vec for maxT -> [42,12,3,4,5]
    EXPECT_EQ(maxT.query(0, 4), 42);

    minT[0] = -5;
    minT[1] -= 3;         // vec for minT -> [-5,-1,3,4,5]
    EXPECT_EQ(minT.query(0, 4), -5);
    EXPECT_EQ(minT.query(1, 4), -1);
}
