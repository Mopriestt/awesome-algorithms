#include "gtest/gtest.h"
#include "simple_trie.hpp"

TEST(TrieSimpleTest, Basic) {
    algo::SimpleTrie trie(10);
    trie.add("abcdefg");
    trie.add("abcdefg");
    trie.add("abcefg");

    EXPECT_EQ(trie.count("abcdefg"), 2);
    EXPECT_EQ(trie.count("abcefg"), 1);
    EXPECT_EQ(trie.count_prefix("abc"), 3);
}

TEST(TrieSimpleTest, Remove) {
    algo::SimpleTrie trie(10);
    trie.add("abcdefg");
    trie.add("abcdefg");
    trie.add("abcefg");

    EXPECT_EQ(trie.count("abcdefg"), 2);
    EXPECT_EQ(trie.count_prefix("abc"), 3);

    EXPECT_TRUE(trie.remove("abcdefg"));
    EXPECT_EQ(trie.count("abcdefg"), 1);
    EXPECT_EQ(trie.count_prefix("abc"), 2);

    EXPECT_TRUE(trie.remove("abcdefg"));
    EXPECT_EQ(trie.count("abcdefg"), 0);
    EXPECT_EQ(trie.count_prefix("abc"), 1);

    EXPECT_FALSE(trie.remove("abcdefg"));
    EXPECT_EQ(trie.count("abcdefg"), 0);
    EXPECT_EQ(trie.count_prefix("abc"), 1);

    EXPECT_TRUE(trie.remove("abcefg"));
    EXPECT_EQ(trie.count("abcefg"), 0);
    EXPECT_EQ(trie.count_prefix("abc"), 0);
}