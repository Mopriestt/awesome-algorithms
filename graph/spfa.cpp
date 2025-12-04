#include <iostream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

/// @brief Implements the queue optimized Bellman-Ford algorithm to find the shortest paths in a graph.
/// @param G The graph represented as an adjacency list where G[u] is a vector of pairs (v, d),
///          indicating a directed edge from u to v with weight d.
/// @param ret A vector to store the computed shortest distances from the source vertex 's' to all other vertices.
/// @param s The source vertex from which shortest paths are calculated.
/// @param n The total number of vertices in the graph.
void spfa(vector<vector<pair<int, int>>> &G, vector<int> &ret, int s, int n) {
    queue<int> q;
    vector<char> inqueue(n, 0);
    inqueue[s] = 1;
    q.push(s);

    // Mind negative value.
    ret.resize(n, -1);
    ret[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = 0;

        for (auto &next : G[u]) {
            int v = next.first, d = next.second;
            if (ret[v] == -1 || ret[v] > ret[u] + d) {
                ret[v] = ret[u] + d;
                if (!inqueue[v]) {
                    q.push(v);
                    inqueue[v] = 1;
                }
            }
        }
    }
}

inline void spfa(vector<vector<pair<int, int>>> &G, vector<int> &ret, int s) {
    spfa(G, ret, s, G.size());
}

inline void spfa(vector<vector<pair<int, int>>> &G, vector<int> &ret) {
    spfa(G, ret, 0, G.size());
}

void test_spfa() {
    srand(time(0));
    int N = 300;
    vector<vector<int>> g(N, vector<int>(N, 0));
    vector<vector<pair<int, int>>> G(N);

    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            g[i][j] = rand() % 10000 + rand() % 10000;
            G[i].push_back({j, g[i][j]});
        }
        g[i][i] = 0;
    }

    for (int k = 0; k < N; k ++)
        for (int i = 0; i < N; i ++)
            for (int j = 0; j < N; j ++)
                if (g[i][k] + g[k][j] < g[i][j]) g[i][j] = g[i][k] + g[k][j];
    
    for (int i = 0; i < N; i ++) {
        vector<int> ret;
        spfa(G, ret, i);

        for (int j = 0; j < N; j ++) {
            if (ret[j] != g[i][j]) {
                cout<< "Test failed" <<endl;
                return;
            }
        }
    }
    cout << "Test passed" << endl;
}

// int main() {
//     test_spfa();
//     return 0;
// }
