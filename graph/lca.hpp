#pragma once

#include <vector>
#include <algorithm>
#include <queue>

namespace algo {
    class Lca {
    public:
        explicit Lca(const std::vector<std::vector<int>>& tree, int root) {
            this->root = root;
            this->n = tree.size();
            this->max_log = 32 - __builtin_clz(n);
            this->up.assign(n, std::vector<int>(max_log));
            this->depth.resize(n);
            bfs(root, tree);
        }

        int lca(int u, int v) const {
            if (depth[u] > depth[v]) {
                std::swap(u, v);
            }
            for (int i = max_log - 1; i >= 0; i--) {
                if (depth[v] - depth[u] >= (1 << i)) {
                    v = up[v][i];
                }
            }
            if (u == v) {
                return u;
            }
            for (int i = max_log - 1; i >= 0; i--) {
                if (up[u][i] != up[v][i]) {
                    u = up[u][i];
                    v = up[v][i];
                }
            }
            return up[u][0];
        }

        int dist(int u, int v) const {
            return depth[u] + depth[v] - 2 * depth[lca(u, v)];
        }
    private:
        void bfs(int root, const std::vector<std::vector<int>>& tree) {
            std::queue<int> q;
            q.push(root);

            depth[root] = 0;
            up[root][0] = root; 

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int i = 1; i < max_log; i++) {
                    up[u][i] = up[up[u][i - 1]][i - 1];
                }

                for (int v : tree[u]) {
                    if (v != up[u][0]) {
                        depth[v] = depth[u] + 1;
                        up[v][0] = u;
                        q.push(v);
                    }
                }
            }
        }

        int root, n, max_log;
        std::vector<std::vector<int>> up;
        std::vector<int> depth;
    };
}