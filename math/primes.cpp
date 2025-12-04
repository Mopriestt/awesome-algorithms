#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Returns prime filter for [1, n]
vector<bool> getPrimeF(const int n) {
    vector<bool> f(n + 1, true);
    for (long long i = 2; i * i <= n; i ++) {
        if (!f[i]) continue;
        for (long long j = i * i; j <= n; j += i)
            f[j] = false;
    }
    f[0] = f[1] = false;
    return f;
}

// Returns primes in [1, n]
vector<long long> getPrimes(long long n) {
    vector<bool> f(n + 1, true);
    vector<long long> ret;
    for (long long i = 2; i <= n; i ++) {
        if (!f[i]) continue;
        ret.push_back(i);
        if (i * i > n) continue;
        for (long long j = i * i; j <= n; j += i)
            f[j] = false;
    }
    return ret;
}

// Returns primes in [l, r]
vector<long long> getPrimes(long long l, long long r) {
    if (l < 2) l = 2;
    int n = r - l + 1;
    vector<long long> ret;
    if (n < 1) return ret;
    vector<bool> f(n, true);
    long long ub = (long long) sqrt(r * 1.0) + 1;

    vector<long long> p = getPrimes(ub);

    for (long long i : p) {
        long long start = max(i * i, l / i * i);
        if (start < l) start += i;
        for (long long j = start; j <= r; j += i) f[j - l] = false;
    }

    for (long long i = l; i <= r; i ++)
        if (f[i - l]) ret.push_back(i);

    return ret;
}

void test_prime_f(long long n) {
    auto p = getPrimeF(n);
    for (long long i : p) cout<<i<<' ';
    cout<<endl;

}

void test_prime_n(long long n) {
    auto p = getPrimes(n);
    for (long long i : p) cout<<i<<' ';
    cout<<endl;
}

void test_prime_lr(long long l, long long r) {
    auto p = getPrimes(l, r);
    for (long long i : p) cout<<i<<' ';
    cout<<endl;
}

int main() {
    cout<<"test prime filter 1 to N"<<endl<<endl;
    test_prime_f(100);

    cout<<"test primes 1 to N"<<endl<<endl;
    test_prime_n(1000);

    cout<<endl<<"test primes L to R"<<endl<<endl;
    test_prime_lr(100000000, 100001000);
    return 0;
}
