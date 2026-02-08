#pragma once

#include <vector>
#include <cmath>

namespace algo {

    typedef unsigned long long ull;

    // Returns prime filter for [1, n]
    inline std::vector<bool> getPrimeF(const int n) {
        std::vector<bool> f(n + 1, true);
        for (ull i = 2; i * i <= n; i ++) {
            if (!f[i]) continue;
            for (ull j = i * i; j <= n; j += i)
                f[j] = false;
        }
        f[0] = f[1] = false;
        return f;
    }

    // Returns primes in [1, n]
    inline std::vector<ull> getPrimes(ull n) {
        std::vector<bool> f(n + 1, true);
        std::vector<ull> ret;
        for (ull i = 2; i <= n; i ++) {
            if (!f[i]) continue;
            ret.push_back(i);
            if (i * i > n) continue;
            for (ull j = i * i; j <= n; j += i)
                f[j] = false;
        }
        return ret;
    }

    // Returns primes in [l, r]
    inline std::vector<ull> getPrimes(ull l, ull r) {
        if (l < 2) l = 2;
        ull n = r - l + 1;
        std::vector<ull> ret;
        if (n < 1) return ret;
        std::vector<bool> f(n, true);
        auto ub = static_cast<ull>(sqrt(static_cast<double>(r)) + 1);

        std::vector<ull> p = getPrimes(ub);

        for (const auto& i : p) {
            ull start = std::max(i * i, l / i * i);
            if (start < l) start += i;
            for (ull j = start; j <= r; j += i) f[j - l] = false;
        }

        for (ull i = l; i <= r; i ++)
            if (f[i - l]) ret.push_back(i);

        return ret;
    }

}
