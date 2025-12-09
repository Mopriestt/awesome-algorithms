#include "gtest/gtest.h"
#include "manacher.hpp"

TEST(ManacherTest, Basic) {
    std::string s = "abacabaaba";
    algo::Manacher m(s);

    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        EXPECT_TRUE(m.isPalindrome(i, i));
    }

    EXPECT_TRUE(m.isPalindrome(0, 2));
    EXPECT_TRUE(m.isPalindrome(2, 4));
    EXPECT_TRUE(m.isPalindrome(0, 6));
    EXPECT_TRUE(m.isPalindrome(5, 8));
    EXPECT_TRUE(m.isPalindrome(4, 9));

    EXPECT_FALSE(m.isPalindrome(0, 1));
    EXPECT_FALSE(m.isPalindrome(1, 3));
    EXPECT_FALSE(m.isPalindrome(3, 6));

    EXPECT_EQ(m.maxRad(3), 4);
    EXPECT_EQ(m.maxRad(1), 2);

    EXPECT_EQ(m.maxRad(0, 6), 4);
    EXPECT_EQ(m.maxRad(5, 8), 3);
}
