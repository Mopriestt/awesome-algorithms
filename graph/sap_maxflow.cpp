#include <iostream>
#include <vector>

using namespace std;

class Sap {
public:
    const int oo = 1 << 30;

    struct Edge {
        int t, f, op;

        Edge(int t, int f) : t(t), f(f) {}
    };

    int n, S, T;
    vector<int> vd;
    vector<int> d;
    vector<vector<Edge>> G;
    
    Sap(int n, int S, int T) : n(n), S(S), T(T) {
        G.resize(n);
    }

    void addedge(int i, int j, int f) {
        G[i].push_back(Edge(j, f));
        G[j].push_back(Edge(i, 0));
        G[i].back().op = G[j].size() - 1;
        G[j].back().op = G[i].size() - 1;
    }

    int dfs(int u, int flow) {
        if (u == T) return flow;
        int tmp, ret = 0;
        for (auto &e : G[u]) {
            if (e.f > 0 && d[u] == d[e.t] + 1) {
                tmp = dfs(e.t, min(flow - ret, e.f));
                e.f -= tmp;
                G[e.t][e.op].f += tmp;
                ret += tmp;
                if (flow == ret) return ret;
            }
        }
        if (!--vd[d[u]]) d[S]=n;
        else vd[++d[u]]++;
        return ret;
    }

    int calculate() {
        d.resize(n);
        vd.resize(n);
        vd[S] = n;
        int ans = 0;

        while (d[S] < n) ans += dfs(S, oo);
        return ans;
    }
};

void test_sap() {
    Sap sap(6, 0, 5);
    // https://www.geeksforgeeks.org/wp-content/uploads/ford_fulkerson2.png
    sap.addedge(0, 1, 11);
    sap.addedge(0, 2, 12);
    sap.addedge(2, 1, 1);
    sap.addedge(1, 3, 12);
    sap.addedge(2, 4, 11);
    sap.addedge(4, 3, 7);
    sap.addedge(3, 5, 19);
    sap.addedge(4, 5, 4);
    cout<< sap.calculate() << endl;
}

// int main() {
//     test_sap();
//     return 0;
// }