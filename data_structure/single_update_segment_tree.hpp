#pragma once

#include <vector>
#include <limits>

namespace algo {

    // ===== Operation functors =====

    // Range sum
    template <typename T>
    struct SumOp {
        using value_type = T;

        static constexpr T identity() { return T{}; }

        static T merge(const T& a, const T& b) {
            return a + b;
        }
    };

    // Range maximum
    template <typename T>
    struct MaxOp {
        using value_type = T;

        static constexpr T identity() {
            return std::numeric_limits<T>::lowest();
        }

        static T merge(const T& a, const T& b) {
            return (a < b) ? b : a;
        }
    };

    // Range minimum
    template <typename T>
    struct MinOp {
        using value_type = T;

        static constexpr T identity() {
            return std::numeric_limits<T>::max();
        }

        static T merge(const T& a, const T& b) {
            return (a < b) ? a : b;
        }
    };

    // ===== SingleUpdateSegmentTree =====
    //
    // - Point update : update(pos, value)
    // - Point add    : add(pos, delta)
    // - Range query  : query(l, r) over [l, r] inclusive
    //
    // Sugar on single point:
    //   tree[i] = v;
    //   tree[i] += d;
    //   tree[i] -= d;
    //
    // Template parameters:
    //   T   : value type
    //   Op  : operation functor template (SumOp / MaxOp / MinOp)

    template <typename T, template<typename> class Op>
    class SingleUpdateSegmentTree {
    public:
        using OpT = Op<T>;
        using value_type = T;

        // Construct an empty tree of size n, initialized with OpT::identity().
        explicit SingleUpdateSegmentTree(int n)
            : n_(n) {
            init_storage(n_);
        }

        // Construct from an initial array.
        explicit SingleUpdateSegmentTree(const std::vector<T>& a)
            : n_(static_cast<int>(a.size())) {
            init_storage(n_);
            for (int i = 0; i < n_; ++i) {
                tree_[base_ + i] = a[i];
            }
            for (int i = base_ - 1; i > 0; --i) {
                tree_[i] = OpT::merge(tree_[i << 1], tree_[i << 1 | 1]);
            }
        }

        int size() const { return n_; }

        // Range query on [l, r] inclusive.
        T query(int l, int r) const {
            T res_left  = OpT::identity();
            T res_right = OpT::identity();
            int L = l + base_;
            int R = r + base_;
            while (L <= R) {
                if (L & 1) {
                    res_left = OpT::merge(res_left, tree_[L++]);
                }
                if (!(R & 1)) {
                    res_right = OpT::merge(tree_[R--], res_right);
                }
                L >>= 1;
                R >>= 1;
            }
            return OpT::merge(res_left, res_right);
        }

        // Point assign: a[pos] = value.
        void update(int pos, const T& value) {
            int p = pos + base_;
            tree_[p] = value;
            for (p >>= 1; p > 0; p >>= 1) {
                tree_[p] = OpT::merge(tree_[p << 1], tree_[p << 1 | 1]);
            }
        }

        // Point add: a[pos] += delta.
        void add(int pos, const T& delta) {
            int p = pos + base_;
            tree_[p] = tree_[p] + delta;
            for (p >>= 1; p > 0; p >>= 1) {
                tree_[p] = OpT::merge(tree_[p << 1], tree_[p << 1 | 1]);
            }
        }

        // ---------- operator[] sugar for single point ----------

        // Proxy for st[i] = v; st[i] += d; st[i] -= d; and read as T.
        class PointProxy {
        public:
            PointProxy(SingleUpdateSegmentTree* st, int pos)
                : st_(st), pos_(pos) {}

            // Read value: T v = st[i];
            operator T() const {
                return st_->query(pos_, pos_);
            }

            // st[i] = value;
            PointProxy& operator=(const T& value) {
                st_->update(pos_, value);
                return *this;
            }

            // st[i] += delta;
            PointProxy& operator+=(const T& delta) {
                st_->add(pos_, delta);
                return *this;
            }

            // st[i] -= delta;
            PointProxy& operator-=(const T& delta) {
                st_->add(pos_, -delta);
                return *this;
            }

        private:
            SingleUpdateSegmentTree* st_;
            int pos_;
        };

        // Non-const: allow assignment / += / -=
        PointProxy operator[](int pos) {
            return PointProxy(this, pos);
        }

        // Const: read-only access
        T operator[](int pos) const {
            return query(pos, pos);
        }

    private:
        int n_{0};            // logical size
        int base_{1};         // first leaf index (power of two)
        std::vector<T> tree_; // size = 2 * base_

        void init_storage(int n) {
            base_ = 1;
            while (base_ < n) base_ <<= 1;
            tree_.assign(base_ << 1, OpT::identity());
        }
    };

} // namespace algo
