#include "gcd.hpp"

#include <gtest/gtest.h>
#include "math/gcd.hpp"

constexpr int N = 7;
const long long test_cases[N][3] = {
    {1, 1, 1},
    {4, 6, 2},
    {6, 12, 6},
    {48, 102, 6},
    {7, 8, 1},
    {1024, 2022, 2},
    {12, 28, 4}
};

TEST(GCDTest, BasicCases) {
    for (int i = 0; i < N; i++) {
        long long a = test_cases[i][0];
        long long b = test_cases[i][1];
        long long r = test_cases[i][2];

        EXPECT_EQ(algo::gcd(a, b), r);
        EXPECT_EQ(algo::gcd(b, a), r);
    }
}

TEST(LCMTest, BasicCases) {
    for (int i = 0; i < N; i++) {
        long long a = test_cases[i][0];
        long long b = test_cases[i][1];
        long long r = test_cases[i][2];

        // Only well-defined for positive pairs; here a,b>0, so safe
        EXPECT_EQ(algo::lcm(a, b), a / r * b);
    }
}

TEST(ExGCDTest, SolveEquation) {
    for (int i = 0; i < N; i++) {
        long long a = test_cases[i][0];
        long long b = test_cases[i][1];
        long long r = test_cases[i][2];

        long long x, y;
        EXPECT_EQ(algo::exgcd(a, b, x, y), r);
        EXPECT_EQ(a * x + b * y, r);
    }
}
