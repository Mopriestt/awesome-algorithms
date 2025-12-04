#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

class UFSet {
public:
    int n;
    vector<int> parent, size, mx;
    vector<long long> sum;
    UFSet(int n) {
        parent.resize(n + 1);
        for (int i = 0; i <= n; i ++) parent[i] = i;
        size.resize(n + 1, 1);
        mx.resize(n + 1, 0);
        sum.resize(n + 1, 0);
    }

    int find(int u) {
        if (parent[u] == u) return u;
        parent[u] = find(parent[u]);
        return parent[u];
    }

    inline void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        size[x] += size[y];
        sum[x] += sum[y];
        mx[x] = max(mx[x], mx[y]);
        parent[y] = x;
    }
 
    inline long long getSum(int u) {
        return sum[find(u)];
    }

    inline int getMax(int u) {
        return mx[find(u)];
    }

    inline int getSize(int u) {
        return size[find(u)];
    }
};

// int main() {
//     UFSet uf(10);
//     return 0;
// }