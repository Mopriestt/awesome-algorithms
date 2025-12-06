#include "gtest/gtest.h"
#include "simple_trie.hpp"

TEST(TrieSimpleTest, Basic) {
    algo::SimpleTrie trie;
    trie.add("abcdefg");
    trie.add("abcdefg");
    trie.add("abcefg");

    EXPECT_EQ(trie.count("abcdefg"), 2);
    EXPECT_EQ(trie.count("abcefg"), 1);
    EXPECT_EQ(trie.count_prefix("abc"), 3);
}