#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>

class Kruskal {
public:
	int n;
	vector<int> father; // Disjoint-set
	Kruskal(int n) {
	    this->n = n;
		father.resize(n);
		for (int i = 0; i < n; i++) father[i] = i;
	}
	void add_edge(int u, int v, T value) {
		index_sanity_check(u, "add_edge");
		index_sanity_check(v, "add_edge");
		edges.push_back(make_pair(value, make_pair(u, v)));
	}

	T calculate() {
		// Change ans type if the result will overflow.
		T ans = 0;
		// Change comparator to Calculate maximum spanning forest.
		sort(edges.begin(), edges.end());

		for (auto e : edges) {
			if (find(e.second.first) != find(e.second.second)) {
				ans += e.first;
				merge(e.second.first, e.second.second);
			}
		}

		return ans;
	}
private:
	vector<pair<T, pair<int, int> > > edges;

	inline void merge(int u, int v) {
		father[find(u)] = father[v];
	}

	int find(int u) {
		if (father[u] != u) father[u] = find(father[u]);
		return father[u];
	}

	inline void index_sanity_check(int index, string where) {
		if (index >= n) throw overflow_error(where + ": index >= n");
		if (index < 0) throw overflow_error(where + ": index < 0");
	}
};

void SimpleTestKruskal() {
	Kruskal<int> kruskal(5);
	kruskal.add_edge(0, 1, 1);
	kruskal.add_edge(1, 2, 2);
	kruskal.add_edge(2, 3, 3);
	kruskal.add_edge(3, 4, 5);
	kruskal.add_edge(0, 4, 6);
	kruskal.add_edge(0, 3, 3);
	kruskal.add_edge(3, 1, 4);
	cout << kruskal.calculate() << endl;
}

// int main() {
// 	SimpleTestKruskal();
// 	return 0;
// }
