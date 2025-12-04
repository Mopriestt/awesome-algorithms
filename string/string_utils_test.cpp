#include "gtest/gtest.h"
#include "string/string_utils.hpp"

TEST(StringUtilsTest, SplitBasic) {
    auto res = algo::split("a,b,c", ",");
    ASSERT_EQ(res.size(), 3);
    EXPECT_EQ(res[0], "a");
    EXPECT_EQ(res[1], "b");
    EXPECT_EQ(res[2], "c");
}