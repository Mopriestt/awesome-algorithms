#pragma once

#include <array>
#include <string_view>
#include <vector>

// A simple fast trie implementation supporting lower case only letter.
namespace algo {

    class SimpleTrie {
        struct Node {
            int count;
            int sum;
            std::array<int, 26> next;
            Node() : count(0), sum(0) { next.fill(-1); }
        };

        std::vector<Node> node_pool;

        const Node* find_node(const std::string_view seq) const {
            auto cur = 0;

            for (const auto &ch : seq) {
                const auto& mp = node_pool[cur].next;
                if (mp[ch - 'a'] == -1) return nullptr;
                cur = mp[ch - 'a'];
            }

            return &node_pool[cur];
        }

    public:
        SimpleTrie() {
            node_pool.emplace_back();
        }

        void add(const std::string_view seq) {
            int cur = 0;
            ++node_pool[cur].sum;
            for (const auto &ch : seq) {
                if (node_pool[cur].next[ch - 'a'] == -1) {
                    node_pool.emplace_back();
                    node_pool[cur].next[ch - 'a'] = node_pool.size() - 1;
                }
                cur = node_pool[cur].next[ch - 'a'];
                ++node_pool[cur].sum;
            }
            ++node_pool[cur].count;
        }

        int count(const std::string_view seq) const {
            const Node* node = find_node(seq);
            return node ? node->count : 0;
        }

        int count_prefix(const std::string_view seq) const {
            const Node* node = find_node(seq);
            return node ? node->sum : 0;
        }

        void clear() {
            node_pool.clear();
            node_pool.emplace_back();
        }
    };

}
