#pragma once

namespace algo {
    // Finds a valid (x, y) that satisfies ax + by = gcd(a, b)
    // Returns gcd(a, b)
    inline long long exgcd(const long long a, const long long b, long long &x, long long &y) {
        if (b == 0) { x = 1, y = 0; return a; }
        const long long r = exgcd(b, a % b, x, y);
        const long long t = x;
        x = y;
        y = t - (a / b) * y;
        return r;
    }

    inline long long gcd(long long a, long long b) {
        while (b != 0) {
            long long r = b;
            b = a % b;
            a = r;
        }
        return a;
    }

    inline long long lcm(long long a, long long b) {
        return a / gcd(a, b) * b;
    }
}
