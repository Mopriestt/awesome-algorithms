#pragma once

#include <vector>
#include <algorithm>
#include <limits>
#include <utility>  // std::pair

namespace algo {

/*
 * DisjointSet2D
 *
 * Most commonly used APIs:
 *
 *   // construction
 *   DisjointSet2D dsu(rows, cols);
 *
 *   // initialize cell values (must be called before relying on sum/max/min)
 *   dsu.setValue(r, c, val);
 *
 *   // union two cells
 *   dsu.merge(r1, c1, r2, c2);
 *
 *   // query per-component properties of the cell (r, c)
 *   int         sz  = dsu.getSize(r, c);  // component size
 *   long long   s   = dsu.getSum(r, c);   // sum of values in the component
 *   int         mx  = dsu.getMax(r, c);   // max value in the component
 *   int         mn  = dsu.getMin(r, c);   // min value in the component
 *
 *   // get root coordinates of the component containing (r, c)
 *   std::pair<int,int> root = dsu.find(r, c);  // (root_row, root_col)
 *
 * Attributes are configured via DSU2D_ATTRS.
 */
#define DSU2D_ATTRS \
    X(Sum, sum, long long, 0,        v[a] += v[b];) \
    X(Max, max_, int, std::numeric_limits<int>::min(), v[a] = std::max(v[a], v[b]);) \
    X(Min, min_, int, std::numeric_limits<int>::max(), v[a] = std::min(v[a], v[b]);)

class DisjointSet2D {
public:
    int n, m;                  // grid size: n rows, m columns
    std::vector<int> parent;   // parent[id]
    std::vector<int> size;     // size[id] only valid at roots

    // Attribute vectors generated from DSU2D_ATTRS
#define X(Name, var, Type, init, merge_code) std::vector<Type> var;
    DSU2D_ATTRS
#undef X

    /*
     * Construct DSU over an n x m grid.
     * Valid ids: 0 .. n*m-1
     */
    DisjointSet2D(int n, int m) : n(n), m(m) {
        const int N = n * m;
        parent.resize(N);
        for (int i = 0; i < N; ++i) parent[i] = i;

        size.assign(N, 1);

        // Initialize all attributes with their default values.
#define X(Name, var, Type, init, merge_code) var.assign(N, init);
        DSU2D_ATTRS
#undef X
    }

    /*
     * Map (r, c) to linear index.
     */
    int index(int r, int c) const {
        return r * m + c;
    }

    /*
     * Find root of id with path compression.
     */
    int findIndex(int id) {
        int root = id;
        while (parent[root] != root) root = parent[root];
        while (id != root) {
            int p = parent[id];
            parent[id] = root;
            id = p;
        }
        return root;
    }

    /*
     * Find root index (linear) of cell (r, c).
     */
    int rootIndex(int r, int c) {
        return findIndex(index(r, c));
    }

    /*
     * Find root coordinates of cell (r, c).
     * Returns (root_row, root_col).
     */
    std::pair<int,int> find(int r, int c) {
        int root = rootIndex(r, c);
        return { root / m, root % m };
    }

    /*
     * Merge components containing two linear indices a, b.
     */
    void mergeIndex(int a, int b) {
        a = findIndex(a);
        b = findIndex(b);
        if (a == b) return;

        if (size[a] < size[b]) std::swap(a, b); // a is larger

        parent[b] = a;
        size[a] += size[b];

        // Merge all attributes into root a
#define X(Name, var, Type, init, merge_code) { auto &v = var; merge_code }
        DSU2D_ATTRS
#undef X
    }

    /*
     * Merge components containing cells (r1, c1) and (r2, c2).
     */
    void merge(int r1, int c1, int r2, int c2) {
        mergeIndex(index(r1, c1), index(r2, c2));
    }

    /*
     * Set initial value for cell (r, c).
     * Updates all attributes at that cell.
     */
    void setValue(int r, int c, int val) {
        int id = index(r, c);
#define X(Name, var, Type, init, merge_code) var[id] = static_cast<Type>(val);
        DSU2D_ATTRS
#undef X
    }

    /*
     * Getters for each configured attribute:
     *   getSum(r,c), getMax(r,c), getMin(r,c), ...
     */
#define X(Name, var, Type, init, merge_code)         \
    Type get##Name(int r, int c) {                   \
        int root = rootIndex(r, c);                  \
        return var[root];                            \
    }
    DSU2D_ATTRS
#undef X

    /*
     * Get size of the component containing (r, c).
     */
    int getSize(int r, int c) {
        int root = rootIndex(r, c);
        return size[root];
    }
};

#undef DSU2D_ATTRS

} // namespace algo
