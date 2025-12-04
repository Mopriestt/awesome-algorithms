#include <iostream>

using namespace std;

const int M = 1000000007;

// Fermat's little theorem
// a ^ (p - 1) % p = 1 if a % p != 0
//
// Mod inverter
// a ^ (p - 2) % p => 1 / a
// b / a => b * a ^ (p - 2) % p

long long qpow(long long a, long long b) {
    long long ret = 1;
    while (b > 0) {
        a %= M;
        if (b & 1) ret = ret * a % M;
        b >>= 1;
        a = a * a % M;
    }
    return ret;
}

// return a / b % M;
long long divide(long long a, long long b) {
    return a * qpow(b, M -2) % M;
}

long long C(long long n, long long m) {
    long long ret = 1;
    if (m > n - m) {
        for (int i = m + 1; i <= n; i ++) ret = ret * i % M;
        for (int i = 2; i <= n - m; i ++) ret = divide(ret, i);
    } else {
        for (int i = n - m + 1; i <= n; i ++) ret = ret * i % M;
        for (int i = 2; i <= m; i ++) ret = divide(ret, i);
    }
    return ret;
}


long long A(long long n, long long m) {
    long long ret = 1;
    for (int i = n - m + 1; i <= n; i ++) ret = ret * i % M;
    return ret;
}

// int main() {
//     cout << C(6, 3) << endl;
//     cout << C(5, 2) << ' ' << C(5, 3) << endl;
//     cout << A(6, 2) << endl;
//     return 0;
// }