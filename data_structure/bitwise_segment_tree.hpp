#pragma once

#include <vector>
#include <limits>

namespace algo {

    // ===================== 操作类定义 =====================

    // 区间和
    template <typename T>
    struct SumOp {
        using value_type = T;

        static constexpr T identity() { return T{}; }

        static T merge(const T& a, const T& b) {
            return a + b;
        }

        // 区间加：整段加 delta
        static void apply_add(T& nodeVal, const T& delta, int len) {
            nodeVal += delta * static_cast<T>(len);
        }

        // 区间赋值：整段改成 value
        static void apply_assign(T& nodeVal, const T& value, int len) {
            nodeVal = value * static_cast<T>(len);
        }
    };

    // 区间最大值
    template <typename T>
    struct MaxOp {
        using value_type = T;

        static constexpr T identity() {
            return std::numeric_limits<T>::lowest();
        }

        static T merge(const T& a, const T& b) {
            return (a < b) ? b : a;
        }

        // 区间加：所有元素加 delta，max 也整体 +delta
        static void apply_add(T& nodeVal, const T& delta, int /*len*/) {
            nodeVal += delta;
        }

        // 区间赋值：所有元素变成 value，max 就是 value
        static void apply_assign(T& nodeVal, const T& value, int /*len*/) {
            nodeVal = value;
        }
    };

    // 区间最小值
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

    // ===================== 通用线段树模板 =====================
    //
    // 使用方式：
    //   SegmentTree<long long, SumOp> st_sum(n);
    //   SegmentTree<int, MaxOp> st_max(n);
    //
    // 支持：
    //   - update(pos, value)         单点赋值
    //   - add(pos, delta)           单点加
    //   - rangeUpdate(l, r, value)  区间赋值
    //   - rangeAdd(l, r, delta)     区间加
    //   - query(l, r)               区间聚合
    //
    // 下标：0-based，区间 [l, r] 为闭区间

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

        // 区间查询 [l, r]
        T query(int l, int r) {
            return query(1, 0, n_ - 1, l, r);
        }

        // 区间加：对 [l, r] 所有元素加 delta
        void rangeAdd(int l, int r, const T& delta) {
            rangeAdd(1, 0, n_ - 1, l, r, delta);
        }

        // 区间赋值：把 [l, r] 所有元素改成 value
        void rangeUpdate(int l, int r, const T& value) {
            rangeUpdate(1, 0, n_ - 1, l, r, value);
        }

        // 单点赋值：a[pos] = value
        void update(int pos, const T& value) {
            rangeUpdate(pos, pos, value);
        }

        // 单点加：a[pos] += delta
        void add(int pos, const T& delta) {
            rangeAdd(pos, pos, delta);
        }

    private:
        int n_;
        std::vector<T> tree_;      // 线段树节点值
        std::vector<T> add_;       // 懒标记：加法
        std::vector<T> assign_;    // 懒标记：赋值
        std::vector<bool> hasAssign_; // 是否有 pending assign

        // ===== 内部工具函数 =====

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

        inline void pull(int idx) {
            tree_[idx] = OpT::merge(tree_[idx << 1], tree_[idx << 1 | 1]);
        }

        // 对当前节点应用“区间加” lazy
        inline void apply_add(int idx, const T& delta, int len) {
            OpT::apply_add(tree_[idx], delta, len);
            if (hasAssign_[idx]) {
                // 有 assign 的前提下再加：叠加到 add_ 上
                add_[idx] += delta;
            } else {
                add_[idx] += delta;
            }
        }

        // 对当前节点应用“区间赋值” lazy
        inline void apply_assign(int idx, const T& value, int len) {
            OpT::apply_assign(tree_[idx], value, len);
            hasAssign_[idx] = true;
            assign_[idx] = value;
            add_[idx] = T{}; // 赋值会清除之前的加法 lazy
        }

        // 下推懒标记
        void push_down(int idx, int l, int r) {
            int mid = (l + r) >> 1;
            int left_len = mid - l + 1;
            int right_len = r - mid;

            int lc = idx << 1;
            int rc = idx << 1 | 1;

            // 先下推 assign（覆盖性更强）
            if (hasAssign_[idx]) {
                apply_assign(lc, assign_[idx], left_len);
                apply_assign(rc, assign_[idx], right_len);
                hasAssign_[idx] = false;
            }

            // 再下推 add（在 assign 之后叠加）
            if (add_[idx] != T{}) {
                apply_add(lc, add_[idx], left_len);
                apply_add(rc, add_[idx], right_len);
                add_[idx] = T{};
            }
        }

        // 区间加
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

        // 区间赋值
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

        // 区间查询
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
