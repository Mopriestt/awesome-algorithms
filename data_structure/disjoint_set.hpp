#pragma once

#include <vector>
#include <algorithm>
#include <limits>

namespace algo {

/*
 * Configurable Disjoint Set Union (Union-Find)
 *
 * You can configure which per-set attributes to maintain by editing DSU_ATTRS.
 * Each X(...) entry defines:
 *   - Public getter name suffix  (Name)
 *   - Member vector name         (var)
 *   - Stored type                (Type)
 *   - Initial value              (init)
 *   - Merge rule when sets join  (merge_code)
 *
 * To remove an attribute, simply delete/comment its line in DSU_ATTRS.
 */
#define DSU_ATTRS \
    X(Sum, sum, long long, 0,        v[x] += v[y];) \
    X(Max, max_, int, std::numeric_limits<int>::min(), v[x] = std::max(v[x], v[y]);) \
    X(Min, min_, int, std::numeric_limits<int>::max(), v[x] = std::min(v[x], v[y]);)

class DisjointSet {
public:
    // parent[u] : parent of node u
    // size[u]   : size of the component whose root is u (valid only at roots)
    std::vector<int> parent, size;

    // Declare attribute vectors based on DSU_ATTRS.
#define X(Name, var, Type, init, merge_code) std::vector<Type> var;
    DSU_ATTRS
#undef X

    /*
     * Construct DSU with elements 0..n (inclusive).
     * By convention you typically use 1..n and ignore 0.
     */
    explicit DisjointSet(int n) {
        parent.resize(n + 1);
        for (int i = 0; i <= n; ++i) parent[i] = i;

        size.assign(n + 1, 1);

        // Initialize all attribute vectors with their default values.
#define X(Name, var, Type, init, merge_code) var.assign(n + 1, init);
        DSU_ATTRS
#undef X
    }

    /*
     * Find the representative (root) of node u with path compression.
     */
    int find(int u) {
        int root = u;
        // Find root.
        while (parent[root] != root) root = parent[root];
        // Path compression.
        while (u != root) {
            int p = parent[u];
            parent[u] = root;
            u = p;
        }
        return root;
    }

    /*
     * Union the sets containing x and y.
     * Uses union-by-size and merges all configured attributes.
     */
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (size[x] < size[y]) std::swap(x, y); // ensure x is the larger set

        parent[y] = x;
        size[x] += size[y];

        // Merge all attributes defined in DSU_ATTRS.
#define X(Name, var, Type, init, merge_code) { auto &v = var; merge_code }
        DSU_ATTRS
#undef X
    }

    /*
     * Set initial value for a single element u.
     * This updates all attributes at index u simultaneously.
     * You typically call this once per element after construction.
     */
    void set_value(int u, int val) {
#define X(Name, var, Type, init, merge_code) var[u] = static_cast<Type>(val);
        DSU_ATTRS
#undef X
    }

    /*
     * Getter for each configured attribute:
     *   getSum(u), getMax(u), getMin(u), ...
     * They all operate on the component containing u.
     */
#define X(Name, var, Type, init, merge_code) \
    Type get##Name(int u) { return var[find(u)]; }
    DSU_ATTRS
#undef X

    /*
     * Get size of the component containing u.
     */
    int getSize(int u) {
        return size[find(u)];
    }
};

#undef DSU_ATTRS

} // namespace algo
