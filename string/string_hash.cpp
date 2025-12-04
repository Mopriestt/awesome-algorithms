#include <iostream>
#include <vector>

using namespace std;

class StringHash {
public:
    const long long M = 1000000007;
    const int seed = 131;

    vector<int> s;
    vector<long long> preHash;
    vector<long long> p;
    vector<long long> d;
    int n;

    StringHash(vector<int> arr) {
        s = arr;
        init();
    }

    StringHash(string str) {
        for (char c : str) s.push_back(int(c));
        init();
    }

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

    void init() {
        n = s.size();
        p.resize(n);
        d.resize(n);
        preHash.resize(n);
        p[0] = 1;
        d[0] = 1;
        preHash[0] = s[0];
        for (int i = 1; i < n; i ++) {
            p[i] = p[i - 1] * seed % M;
            d[i] = qpow(p[i], M - 2) % M;
            preHash[i] = (preHash[i - 1] + s[i] * p[i]) % M;
        }
    }

    inline long long subHash(int l, int r) {
        long long ret = preHash[r];
        if (l != 0) ret = (ret - preHash[l - 1] + M) % M;
        return ret * d[l] % M;
    }
};

// int main() {
//     string a = "1234123";
//     StringHash sh(a);
//     cout<<sh.subHash(0, 2)<<endl;
//     cout<<sh.subHash(4, 6)<<endl;
//     cout<<sh.subHash(0, 6)<<endl;
//     cout<<sh.subHash(1, 2)<<endl;
//     cout<<sh.subHash(5, 6)<<endl;
//     return 0;
// }