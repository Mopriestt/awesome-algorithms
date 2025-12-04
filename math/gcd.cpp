#include <iostream>

using namespace std;

// Finds a valid (x, y) that satisfies ax + by = gcd(a, b)
// Returns gcd(a, b)
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    long long r = exgcd(b, a % b, x, y);
    long long t = x;
    x = y;
    y = t - (a / b) * y;
    return r;
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long r = b;
        b = a % b;
        a = r;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

const int N = 7;
int test_cases[N][3] =
{
    {1, 1, 1},
    {4, 6, 2},
    {6, 12, 6},
    {48, 102, 6},
    {7, 8, 1},
    {1024, 2022, 2},
    {12, 28, 4}
};

void test_gcd() {
    for (int i = 0; i < N; i ++) {
        long long a = test_cases[i][0], b = test_cases[i][1], r = test_cases[i][2];
        if (gcd(a, b) != r || gcd(b, a) != r) {
            cout<<"GCD Test Failed!"<<endl;
            return;
        }
    }
    cout<<"GCD Test Passed!"<<endl;
}

void test_exgcd() {
    for (int i = 0; i < N; i ++) {
        long long x, y;
        long long a = test_cases[i][0], b = test_cases[i][1], r = test_cases[i][2];
        if (exgcd(a, b, x, y) != r) {
            cout<<"EX-GCD Test Failed!"<<endl;
            return;
        }
        if (a * x + b * y != r) {
            cout<<"EX-GCD Test Failed!"<<endl;
            return;
        }
    }
    cout<<"EX-GCD Test Passed!"<<endl;
}

// int main() {
//     test_gcd();
//     test_exgcd();
//     return 0;
// }