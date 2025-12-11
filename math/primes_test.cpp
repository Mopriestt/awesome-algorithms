#include "primes.hpp"
#include <gtest/gtest.h>
#include <algorithm>

using algo::getPrimeF;
using algo::getPrimes;
using algo::ull;

TEST(GetPrimeFTest, SmallNBasicPattern) {
    // 注意：你的实现对 n=0 会越界，这里从 n=1 开始测
    auto f10 = getPrimeF(10);

    ASSERT_EQ(f10.size(), 11u);

    // [0, 10] 中的质数是 2,3,5,7
    EXPECT_FALSE(f10[0]);
    EXPECT_FALSE(f10[1]);
    EXPECT_TRUE(f10[2]);
    EXPECT_TRUE(f10[3]);
    EXPECT_FALSE(f10[4]);
    EXPECT_TRUE(f10[5]);
    EXPECT_FALSE(f10[6]);
    EXPECT_TRUE(f10[7]);
    EXPECT_FALSE(f10[8]);
    EXPECT_FALSE(f10[9]);
    EXPECT_FALSE(f10[10]);
}

TEST(GetPrimeFTest, MatchesKnownPrimesUpTo50) {
    const int n = 50;
    auto f = getPrimeF(n);

    std::vector<int> expectedPrimes{
        2, 3, 5, 7, 11, 13, 17, 19,
        23, 29, 31, 37, 41, 43, 47
    };

    // primes must be marked true
    for (int p : expectedPrimes) {
        ASSERT_LT(p, static_cast<int>(f.size()));
        EXPECT_TRUE(f[p]) << "Prime " << p << " should be true";
    }

    // non-primes must be false
    for (int i = 0; i <= n; ++i) {
        bool isPrime = std::binary_search(expectedPrimes.begin(),
                                          expectedPrimes.end(), i);
        EXPECT_EQ(f[i], isPrime) << "Mismatch at " << i;
    }
}

TEST(GetPrimesUpToTest, SmallNValues) {
    auto p10 = getPrimes(10);
    std::vector<ull> expected10{2, 3, 5, 7};
    EXPECT_EQ(p10, expected10);

    auto p2 = getPrimes(2);
    std::vector<ull> expected2{2};
    EXPECT_EQ(p2, expected2);

    auto p1 = getPrimes(1);
    EXPECT_TRUE(p1.empty());
}

TEST(GetPrimesUpToTest, ConsistentWithFilterUpTo1000) {
    const ull n = 1000;
    auto primes = getPrimes(n);
    auto f = getPrimeF(static_cast<int>(n));

    for (ull x : primes) {
        ASSERT_GE(x, 2u);
        ASSERT_LE(x, n);
        EXPECT_TRUE(f[static_cast<std::size_t>(x)])
            << "getPrimes returned non-prime " << x;
    }

    // 2) 所有 f[i] 为 true 的 i 都应该出现在 primes 里面
    for (ull i = 2; i <= n; ++i) {
        if (f[static_cast<std::size_t>(i)]) {
            EXPECT_TRUE(std::binary_search(primes.begin(), primes.end(), i))
                << "Prime " << i << " not found in getPrimes(n)";
        }
    }
}

TEST(GetPrimesRangeTest, BasicRanges) {
    // [1, 10] -> {2, 3, 5, 7}
    auto p1_10 = getPrimes(1, 10);
    std::vector<ull> expected1_10{2, 3, 5, 7};
    EXPECT_EQ(p1_10, expected1_10);

    // [10, 20] -> {11, 13, 17, 19}
    auto p10_20 = getPrimes(10, 20);
    std::vector<ull> expected10_20{11, 13, 17, 19};
    EXPECT_EQ(p10_20, expected10_20);

    // [17, 19] -> {17, 19}
    auto p17_19 = getPrimes(17, 19);
    std::vector<ull> expected17_19{17, 19};
    EXPECT_EQ(p17_19, expected17_19);
}

TEST(GetPrimesRangeTest, ClampLowerBoundToTwo) {
    auto pNeg_10 = getPrimes(0, 10);
    std::vector<ull> expected{2, 3, 5, 7};
    EXPECT_EQ(pNeg_10, expected);
}

TEST(GetPrimesRangeTest, ConsistencyWithUpToForModerateRanges) {
    const ull N = 200;
    auto all = getPrimes(N); // primes in [1, N]

    auto makeExpected = [&](ull l, ull r) {
        std::vector<ull> expected;
        for (ull x : all) {
            if (x < l) continue;
            if (x > r) break;
            expected.push_back(x);
        }
        return expected;
    };

    {
        ull l = 50, r = 100;
        auto expected = makeExpected(l, r);
        auto actual = getPrimes(l, r);
        EXPECT_EQ(actual, expected);
    }

    {
        ull l = 100, r = 200;
        auto expected = makeExpected(l, r);
        auto actual = getPrimes(l, r);
        EXPECT_EQ(actual, expected);
    }

    {
        ull l = 2, r = 2;
        auto expected = makeExpected(l, r);
        auto actual = getPrimes(l, r);
        EXPECT_EQ(actual, expected);
    }
}

