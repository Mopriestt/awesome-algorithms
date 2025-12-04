#include <iostream>
#include <vector>

using namespace std;

namespace algo::pointer_seg {
    const int MAX_RANGE = 100000;

    struct Node {
        int l, r, max, val;
        Node *cl, *cr;
        long long sum;
        inline long long getSum() {
            return sum + 1LL * (r - l + 1) * val;
        }
        inline long long getMax() {
            return max + val;
        }
    } T[MAX_RANGE * 2 + 10];

    class SegmentTree {
    public:
        Node *root = T;
        int ns = 0;

        SegmentTree(int n) {
            buildTree(root, 0, n);
        }

        pair<int, long long> query(int l, int r) {
            return _query(root, l, r);
        }

        void add(int l, int r, int v) {
            _add(root, l, r, v);
        }
    private:
        void _add(Node *p, int l, int r, int v) {
            if (l > p -> r || r < p -> l) return;
            if (l <= p -> l && r >= p -> r) {
                p -> val += v;
                return;
            }
            push(p);
            _add(p -> cl, l, r, v);
            _add(p -> cr, l, r, v);
            merge(p);
        }

        pair<int, long long> _query(Node *p, int l, int r) {
            if (l > p -> r || r < p -> l) return {0, 0};
            if (l <= p -> l && r >= p -> r) return {p -> getMax(), p -> getSum()};
            push(p);
            auto v1 = _query(p -> cl, l, r);
            auto v2 = _query(p -> cr, l, r);
            merge(p);
            return {max(v1.first, v2.first), v1.second + v2.second};
        }

        // Push down
        inline void push(Node *p) {
            if (p -> l == p -> r) return;
            p -> cl -> val += p -> val;
            p -> cr -> val += p -> val;
            p -> val = 0;
        }

        // Merge up
        inline void merge(Node *p) {
            p -> max = max(p -> cl -> getMax(), p -> cr -> getMax());
            p -> sum = p -> cl -> getSum() + p -> cr -> getSum();
        }

        void buildTree(Node *p, int l, int r) {
            p -> l = l, p -> r = r;
            p -> max = p -> sum = p -> val = 0;
            if (l == r) return;
            int mid = (l + r) >> 1;
            p -> cl = T + ++ns, p -> cr = T + ++ns;
            buildTree(p -> cl, l, mid);
            buildTree(p -> cr, mid + 1, r);
        }
    };

    void test_segment_tree() {
        int n = MAX_RANGE;
        srand(time(NULL));
        vector<int> a(n, 0);
        SegmentTree tree(n - 1);

        for (int query = 0; query < 100000; query ++) {
            int op = rand() % 2;
            int single = rand() % 4;
            int l = rand() % n, r = (rand() % 5 == 0) ? l : rand() % n;
            if (r < l) l ^= r ^= l ^= r;

            if (op == 0) {
                // add
                int v = rand() % 1000;
                tree.add(l, r, v);
                for (int i = l; i <= r; i ++) a[i] += v;
            } else {
                // query
                auto res = tree.query(l, r);
                int mx = 0;
                long long sum = 0LL;
                for (int i = l; i <= r; i ++) {
                    mx = max(mx, a[i]);
                    sum += a[i];
                }
                if (res.first != mx || res.second != sum) {
                    cout<<"Test failed"<<endl;
                    return;
                }
            }
        }
        cout<<"Test passed!"<<endl;
    }
}

// int main() {
//     test_segment_tree();
//     return 0;
// }