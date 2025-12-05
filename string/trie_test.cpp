#include "gtest/gtest.h"
#include "trie.hpp"

TEST(TrieTest, Basic) {
    std::vector v1 = {1, 2, 3, 4, 5, 6};
    std::vector v2 = {1, 2, 3, 5, 6};

    algo::Trie<std::vector<int>> trie;
    trie.add(v1);
    trie.add(v2);
    trie.add(v1);

    EXPECT_EQ(trie.count(v1), 2);
    EXPECT_EQ(trie.count(v2), 1);
    EXPECT_EQ(trie.count_prefix({1, 2, 3}), 3);
}