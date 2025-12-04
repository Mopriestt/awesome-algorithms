#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct MinCostFlow {
    const int oo = 1 << 30;

    struct Edge {
        int t, f, c, op;

        Edge(int t, int f, int c) : t(t), f(f), c(c) {}
    };

    int n, S, T, minflow, fee;
    vector<vector<Edge>> G;
    vector<int> d;
    vector<char> inq;
    vector<Edge*> path;
    
    MinCostFlow(int n, int S, int T) : n(n), S(S), T(T) {
        G.resize(n);
        d.resize(n);
        inq.resize(n);
        path.resize(n);
    }

    void addedge(int i, int j, int f, int c) {
        G[i].push_back(Edge(j, f, c));
        G[j].push_back(Edge(i, 0, -c));
        G[i].back().op = G[j].size() - 1;
        G[j].back().op = G[i].size() - 1;
    }

    void spfa() {
        for (int i = 0; i < n; i ++) {
            inq[i] = false;
            d[i] = oo;
        }
        d[S] = 0;
        queue<int> que;
        que.push(S);
        inq[S] = true;

        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto &e : G[u])
                if (d[e.t] > d[u] + e.c && e.f > 0) {
                    d[e.t] = d[u] + e.c;
                    path[e.t] = &e;
                    if (!inq[e.t]) {
                        inq[e.t] = true;
                        que.push(e.t);
                    }
                }
            inq[u] = false;
        }
    }

    void dfs(int u) {
        minflow = min(minflow, path[u]->f);
        fee += path[u]->c;
        if (G[u][path[u]->op].t != S) dfs(G[u][path[u]->op].t);
        path[u]->f -= minflow;
        G[u][path[u]->op].f += minflow;
    }

    int calculate() {
        int ans = 0;
        for (;;) {
            spfa();
            if (d[T] == oo) break;
            minflow = oo;
            fee = 0;
            dfs(T);
            ans += minflow * fee;
        }
        return ans;
    }
};

// int main() {
//     MinCostFlow mcf(5, 0, 4);
//     mcf.addedge(0, 1, 3, 1);
//     mcf.addedge(0, 3, 4, 3);
//     mcf.addedge(1, 2, 2, 2);
//     mcf.addedge(3, 2, 3, 1);
//     mcf.addedge(3, 4, 2, 4);
//     mcf.addedge(2, 4, 1, 1);
//     cout<<mcf.calculate()<<endl;
// }