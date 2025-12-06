#include <iostream>
#include <vector>

using namespace std;
namespace algo::bitwise_seg {
    // Segment tree for range [0, n]
    class SegmentTree {
    public:
        int n;
        vector<int> t;
        SegmentTree(int _n) : n(_n + 1) { t.resize(n << 1, 0); }

        void build() {
            for (int i = n - 1; i > 0; -- i) t[i] = t[i << 1] + t[(i << 1) | 1];
        }

        void update(int p, int value) {
            for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
        }

        // Max value of [l, r]
        int query(int l, int r) {
            int res = 0;
            for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res = max(res, t[l ++]);
                if (r & 1) res = max(res, t[-- r]);
            }
            return res;
        }
    };
}

// int main() {
//     test_segment_tree();
//     return 0;
// }