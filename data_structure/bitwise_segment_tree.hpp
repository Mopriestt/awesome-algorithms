/// @file bitwise_segment_tree.hpp
/// @brief Generic lazy segment tree with pluggable operations (sum / min / max).
///
/// This header provides:
///   * Three operation functors: SumOp, MaxOp, MinOp
///   * A generic segment tree template:
///       template <typename T, template<typename> class Op>
///       class SegmentTree;
///
/// The tree supports:
///   * Point update        : a[pos] = value
///   * Point add           : a[pos] += delta
///   * Range assign        : a[l..r] = value
///   * Range add           : a[l..r] += delta
///   * Range query         : Op::merge over [l..r]
///
/// Indexing:
///   * 0-based indices on the original array
///   * All ranges [l, r] are inclusive
///
/// Complexity:
///   * build from array:  O(n)
///   * each range/point op: O(log n)
///
/// Requirements:
///   * T must support:
///       - Default construction (T{})
///       - Copy / assign
///       - The arithmetic or comparison used by the Op
///   * Op<T> must define:
///       - using value_type = T;
///       - static constexpr T identity();
///       - static T merge(const T&, const T&);
///       - static void apply_add(T& nodeVal, const T& delta, int len);
///       - static void apply_assign(T& nodeVal, const T& value, int len);
///
/// Example (range sum over long long, with range add / assign):
///
///     #include "bitwise_segment_tree.hpp"
///     using algo::SegmentTree;
///     using algo::SumOp;
///
///     int n = 10;
///     SegmentTree<long long, SumOp> st(n);
///
///     st.update(3, 5);          // a[3] = 5
///     st.add(3, 2);             // a[3] += 2   -> 7
///     st.rangeAdd(0, 4, 1);     // a[0..4] += 1
///     st.rangeUpdate(2, 5, 10); // a[2..5] = 10
///
///     long long ans = st.query(0, 9); // sum over [0,9]
///
/// Example (range max over int, with range add / assign):
///
///     using algo::MaxOp;
///     std::vector<int> a = {1, 5, 2, 7, 3};
///     SegmentTree<int, MaxOp> st(a);
///
///     int mx1 = st.query(0, 4);    // max in [0,4] = 7
///     st.rangeAdd(0, 4, 10);       // all +10 -> {11, 15, 12, 17, 13}
///     int mx2 = st.query(1, 3);    // max in [1,3] = 17
///     st.rangeUpdate(1, 3, 0);     // a[1..3] = 0
///     int mx3 = st.query(0, 4);    // max in [0,4] = 13 (index 4)

#pragma once

#include <vector>
#include <limits>

namespace algo {

    template <typename T>
    struct SumOp {
        using value_type = T;

        static constexpr T identity() { return T{}; }

        static T merge(const T& a, const T& b) {
            return a + b;
        }

        static void apply_add(T& nodeVal, const T& delta, int len) {
            nodeVal += delta * static_cast<T>(len);
        }

        static void apply_assign(T& nodeVal, const T& value, int len) {
            nodeVal = value * static_cast<T>(len);
        }
    };

    template <typename T>
    struct MaxOp {
        using value_type = T;

        static constexpr T identity() {
            return std::numeric_limits<T>::lowest();
        }

        static T merge(const T& a, const T& b) {
            return (a < b) ? b : a;
        }

        static void apply_add(T& nodeVal, const T& delta, int /*len*/) {
            nodeVal += delta;
        }

        static void apply_assign(T& nodeVal, const T& value, int /*len*/) {
            nodeVal = value;
        }
    };

    template <typename T>
    struct MinOp {
        using value_type = T;

        static constexpr T identity() {
            return std::numeric_limits<T>::max();
        }

        static T merge(const T& a, const T& b) {
            return (a < b) ? a : b;
        }

        static void apply_add(T& nodeVal, const T& delta, int /*len*/) {
            nodeVal += delta;
        }

        static void apply_assign(T& nodeVal, const T& value, int /*len*/) {
            nodeVal = value;
        }
    };

    template <typename T, template<typename> class Op>
    class SegmentTree {
    public:
        using OpT = Op<T>;
        using value_type = T;

        explicit SegmentTree(int n)
            : n_(n),
              tree_(4 * n, OpT::identity()),
              add_(4 * n, T{}),
              assign_(4 * n, T{}),
              hasAssign_(4 * n, false)
        {}

        explicit SegmentTree(const std::vector<T>& a)
            : SegmentTree(static_cast<int>(a.size())) {
            if (!a.empty()) {
                build(1, 0, n_ - 1, a);
            }
        }

        int size() const { return n_; }

        T query(int l, int r) {
            return query(1, 0, n_ - 1, l, r);
        }

        /// Add `delta` to every element in the inclusive range [l, r].
        void rangeAdd(int l, int r, const T& delta) {
            rangeAdd(1, 0, n_ - 1, l, r, delta);
        }

        /// Assign `value` to every element in the inclusive range [l, r].
        void rangeUpdate(int l, int r, const T& value) {
            rangeUpdate(1, 0, n_ - 1, l, r, value);
        }

        /// Set a single position: a[pos] = value.
        void update(int pos, const T& value) {
            rangeUpdate(pos, pos, value);
        }

        /// Add `delta` to a single position: a[pos] += delta.
        void add(int pos, const T& delta) {
            rangeAdd(pos, pos, delta);
        }

    private:
        int n_;
        std::vector<T> tree_;
        std::vector<T> add_;
        std::vector<T> assign_;
        std::vector<bool> hasAssign_;


        void build(int idx, int l, int r, const std::vector<T>& a) {
            if (l == r) {
                tree_[idx] = a[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(idx << 1, l, mid, a);
            build(idx << 1 | 1, mid + 1, r, a);
            pull(idx);
        }

        void pull(int idx) {
            tree_[idx] = OpT::merge(tree_[idx << 1], tree_[idx << 1 | 1]);
        }

        void apply_add(int idx, const T& delta, int len) {
            OpT::apply_add(tree_[idx], delta, len);
            if (hasAssign_[idx]) {
                add_[idx] += delta;
            } else {
                add_[idx] += delta;
            }
        }

        void apply_assign(int idx, const T& value, int len) {
            OpT::apply_assign(tree_[idx], value, len);
            hasAssign_[idx] = true;
            assign_[idx] = value;
            add_[idx] = T{};
        }

        void push_down(int idx, int l, int r) {
            int mid = (l + r) >> 1;
            int left_len = mid - l + 1;
            int right_len = r - mid;

            int lc = idx << 1;
            int rc = idx << 1 | 1;

            if (hasAssign_[idx]) {
                apply_assign(lc, assign_[idx], left_len);
                apply_assign(rc, assign_[idx], right_len);
                hasAssign_[idx] = false;
            }

            if (add_[idx] != T{}) {
                apply_add(lc, add_[idx], left_len);
                apply_add(rc, add_[idx], right_len);
                add_[idx] = T{};
            }
        }

        void rangeAdd(int idx, int l, int r, int ql, int qr, const T& delta) {
            if (ql > r || qr < l) return;
            if (ql <= l && r <= qr) {
                apply_add(idx, delta, r - l + 1);
                return;
            }
            push_down(idx, l, r);
            int mid = (l + r) >> 1;
            rangeAdd(idx << 1, l, mid, ql, qr, delta);
            rangeAdd(idx << 1 | 1, mid + 1, r, ql, qr, delta);
            pull(idx);
        }

        void rangeUpdate(int idx, int l, int r, int ql, int qr, const T& value) {
            if (ql > r || qr < l) return;
            if (ql <= l && r <= qr) {
                apply_assign(idx, value, r - l + 1);
                return;
            }
            push_down(idx, l, r);
            int mid = (l + r) >> 1;
            rangeUpdate(idx << 1, l, mid, ql, qr, value);
            rangeUpdate(idx << 1 | 1, mid + 1, r, ql, qr, value);
            pull(idx);
        }

        T query(int idx, int l, int r, int ql, int qr) {
            if (ql > r || qr < l) {
                return OpT::identity();
            }
            if (ql <= l && r <= qr) {
                return tree_[idx];
            }
            push_down(idx, l, r);
            int mid = (l + r) >> 1;
            T left = query(idx << 1, l, mid, ql, qr);
            T right = query(idx << 1 | 1, mid + 1, r, ql, qr);
            return OpT::merge(left, right);
        }
    };

} // namespace algo
