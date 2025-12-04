#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace algo::trie2 {
    // Arbitrary letter.
    struct Node {
        int sum;
        unordered_map<char, int> c;
        Node() : sum(0) {}
    }tmp;

    class Trie {
    public:
        vector<Node> nodes;
        Trie() { nodes.push_back(tmp); }

        void add(string &s) {
            int p = 0;
            for (char c : s) {
                if (nodes[p].c[c] == 0) {
                    nodes.push_back(tmp);
                    nodes[p].c[c] = nodes.size() - 1;
                }
                p = nodes[p].c[c];
                nodes[p].sum ++;
            }
        }

        int count(string &s) {
            int p = 0, res = 0;
            for (char c : s) {
                p = nodes[p].c[c];
                res += nodes[p].sum;
            }
            return res;
        }
    };

    void test_trie() {
        srand(time(NULL));
        int n = 2000;
        vector<string> words;
        for (int i = 0; i < n; i ++) {
            int l = rand() % 1000 + 1;
            string s;
            while (l --) s += char(rand() % 128);
            words.push_back(s);
        }

        Trie tree;
        for (string s : words) tree.add(s);
        for (string s : words) {
            int ans_1 = tree.count(s), ans_2 = 0;
            for (string t : words)
                for (int i = 0; i < min(s.size(), t.size()); i ++) {
                    if (s[i] != t[i]) break;
                    ans_2 ++;
                }
            if (ans_1 != ans_2) {
                cout<<"Test failed!"<<endl;
                return;
            }
        }
        cout<<"Test passed!"<<endl;
    }
}

// int main() {
//     test_trie();
//     return 0;
// }
