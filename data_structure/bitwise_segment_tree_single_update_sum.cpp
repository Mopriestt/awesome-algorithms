#include <iostream>
#include <vector>

using namespace std;
namespace algo::bitwise_seg2 {
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
            for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
        }

        // Max value of [l, r]
        int query(int l, int r) {
            int res = 0;
            for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res += t[l ++];
                if (r & 1) res += t[-- r];
            }
            return res;
        }
    };

    void test_segment_tree() {
        int n = 100000;
        vector<int> sum_array;
        SegmentTree tree(n);
        srand(time(NULL));
        for (int i = 0; i < n; i ++) {
            sum_array.push_back(rand() % 100 > 98 ? rand() % 1000 : rand() % 100);
            tree.update(i, sum_array[i]);
        }

        for (int query = 0; query < 10000; query ++) {
            int l = rand() % n, r = rand() % n;
            if (l > r) swap(l, r);
            int result = tree.query(l, r);

            int sum_value = 0;
            for (int i = l; i <= r; i ++) {
                sum_value = sum_value + sum_array[i];
            }
            if (sum_value != result) {
                cout<<"Test failed!"<<endl;
                return;
            }
        }

        cout<<"Test passed"<<endl;
    }
}

// int main() {
//     test_segment_tree();
//     return 0;
// }