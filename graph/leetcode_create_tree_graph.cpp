#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int n;
    vector<vector<int>> g;
    void addedges(vector<vector<int>> &edges) {
        g.resize(n);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]); // Remove if graph is unidrectional
        }
    }

    void dfs(int u, int fa) {
        for (auto v : g[u]) if (v != fa) {
            dfs(v, u);
        }
    }
};

// int main() {
//     return 0;
// }