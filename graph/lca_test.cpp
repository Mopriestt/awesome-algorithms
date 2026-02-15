#include <gtest/gtest.h>
#include "graph/lca.hpp"
#include <vector>

using namespace std;

// Helper to create a simple tree
// Structure:
//      0
//     / \
//    1   2
//   / \   \
//  3   4   5
//           \
//            6
vector<vector<int>> create_test_tree() {
    int n = 7;
    vector<vector<int>> adj(n);
    auto add_edge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    
    adj = vector<vector<int>>(n);
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(1, 3);
    add_edge(1, 4);
    add_edge(2, 5);
    add_edge(5, 6);
    return adj;
}

TEST(LCATest, SimpleTree) {
    auto tree = create_test_tree();
    algo::Lca lca_solver(tree, 0);

    EXPECT_EQ(lca_solver.lca(3, 4), 1);
    EXPECT_EQ(lca_solver.lca(3, 1), 1);
    EXPECT_EQ(lca_solver.lca(1, 3), 1);
    EXPECT_EQ(lca_solver.lca(3, 6), 0); // 3->1->0, 6->5->2->0
    EXPECT_EQ(lca_solver.lca(4, 5), 0);
    EXPECT_EQ(lca_solver.lca(6, 2), 2);
    EXPECT_EQ(lca_solver.lca(0, 6), 0);
    EXPECT_EQ(lca_solver.lca(0, 0), 0);
    EXPECT_EQ(lca_solver.lca(3, 3), 3);

    // Distance tests
    EXPECT_EQ(lca_solver.dist(3, 4), 2);
    EXPECT_EQ(lca_solver.dist(3, 6), 5);
    EXPECT_EQ(lca_solver.dist(0, 6), 3);
    EXPECT_EQ(lca_solver.dist(3, 3), 0);
}

TEST(LCATest, LineGraph) {
    // 0-1-2-3-4
    int n = 5;
    vector<vector<int>> adj(n);
    for(int i=0; i<n-1; ++i) {
        adj[i].push_back(i+1);
        adj[i+1].push_back(i);
    }
    algo::Lca lca_solver(adj, 0);

    EXPECT_EQ(lca_solver.lca(0, 4), 0);
    EXPECT_EQ(lca_solver.lca(3, 4), 3);
    EXPECT_EQ(lca_solver.lca(2, 3), 2);
    EXPECT_EQ(lca_solver.lca(1, 4), 1);
}

TEST(LCATest, StarGraph) {
    //      0
    //    / | \
    //   1  2  3
    int n = 4;
    vector<vector<int>> adj(n);
    for(int i=1; i<n; ++i) {
        adj[0].push_back(i);
        adj[i].push_back(0);
    }
    algo::Lca lca_solver(adj, 0);

    EXPECT_EQ(lca_solver.lca(1, 2), 0);
    EXPECT_EQ(lca_solver.lca(1, 3), 0);
    EXPECT_EQ(lca_solver.lca(2, 3), 0);
    EXPECT_EQ(lca_solver.lca(0, 1), 0);
}
