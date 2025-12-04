#include <iostream>
#include <vector>

using namespace std;

/// @brief Implements the Dijkstra to find the shortest paths in a graph.
/// @param G The graph represented as an adjacency list where G[u] is a vector of pairs (v, d),
///          indicating a directed edge from u to v with weight d.
/// @param ret A vector to store the computed shortest distances from the source vertex 's' to all other vertices.
/// @param s The source vertex from which shortest paths are calculated.
/// @param n The total number of vertices in the graph.
void dijkstra(vector<vector<pair<int, int>>> &G, vector<int> &ret, int s, int n) {
    vector<char> vis(n, 0);
    ret.resize(n, -1);
    ret[s] = 0;
    for (int i = 0; i < n - 1; i ++) {
        int k = -1;
        for (int j = 0; j < n; j ++)
            if (vis[j] == 0 && ret[j] != -1 && (k == -1 || ret[k] > ret[j])) k = j;
        vis[k] = 1;
        
        for (auto &e : G[k]) {
            if (ret[e.first] == -1 || ret[e.first] > ret[k] + e.second) {
                ret[e.first] = ret[k] + e.second;
            }
        }
    }
}

inline void dijkstra(vector<vector<pair<int, int>>> &G, vector<int> &ret, int s) {
    dijkstra(G, ret, s, G.size());
}

inline void dijkstra(vector<vector<pair<int, int>>> &G, vector<int> &ret) {
    dijkstra(G, ret, 0, G.size());
}

void test_dijkstra() {
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
        dijkstra(G, ret, i);

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
//     test_dijkstra();
//     return 0;
// }