#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace algo::trie1 {
    // A word must only contains lower case english letter.
    struct Node {
        int sum, c[26];
        Node() : sum(0) { for (short _ = 0; _ < 26; _ ++) c[_] = -1; }
    }tmp;

    class Trie {
    public:
        vector<Node> nodes;
        Trie() { nodes.push_back(tmp); }

        void add(string &s) {
            int p = 0;
            for (char c : s) {
                if (nodes[p].c[c - 'a'] == -1) {
                    nodes.push_back(tmp);
                    nodes[p].c[c - 'a'] = nodes.size() - 1;
                }
                p = nodes[p].c[c - 'a'];
                nodes[p].sum ++;
            }
        }

        int count(string &s) {
            int p = 0, res = 0;
            for (char c : s) {
                p = nodes[p].c[c - 'a'];
                res += nodes[p].sum;
            }
            return res;
        }
    };

    void test_trie() {
        srand(time(NULL));
        int n = 1000;
        vector<string> words;
        for (int i = 0; i < n; i ++) {
            int l = rand() % 1000 + 1;
            string s;
            while (l --) s += char('a' + rand() % 26);
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
