#include "gtest/gtest.h"
#include "hashing.hpp"

TEST(HashingTest, Basic) {
    const std::vector vec = { 97, 99, 48, 50, 98};
    const std::string str = "ac02b";

    EXPECT_EQ(algo::hash(vec), algo::hash(str));
    EXPECT_EQ(algo::hash(vec, 131), algo::hash(str, 131));
}

TEST(HashingTest, SubHash) {
    const std::string str = "abcabcabbaa";
    auto hash = algo::SubHash64(str);

    EXPECT_EQ(hash.sub_hash(0, 2), hash.sub_hash(3, 5));
    EXPECT_EQ(hash.sub_hash(0, 1), hash.sub_hash(6, 7));
    EXPECT_EQ(hash.sub_hash(3, 3), hash.sub_hash(10, 10));
}