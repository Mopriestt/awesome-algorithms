#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

namespace algo {

    template <typename Container>
    class Trie {

    public:
        using sequence_type = Container;
        using element_type = typename Container::value_type;

    private:
        struct Node {
            int count;
            int sum;
            std::unique_ptr<
                std::unordered_map<element_type, int>
            > next;
            void require_next_map() {
                if (next != nullptr) return;
                next = std::make_unique<std::unordered_map<element_type, int>>();
            }
            Node() : count(0), sum(0), next(nullptr) {}
        };

        std::vector<Node> node_pool;

        const Node* find_node(const sequence_type& seq) const {
            auto cur = 0;

            for (const auto &ch : seq) {
                if (!node_pool[cur].next) return nullptr;
                const auto& mp = *node_pool[cur].next;
                auto it = mp.find(ch);
                if (it == mp.end()) return nullptr;
                cur = it->second;
            }

            return &node_pool[cur];
        }

    public:
        Trie() {
            node_pool.emplace_back();
        }

        void add(const sequence_type& seq) {
            int cur = 0;
            ++node_pool[cur].sum;
            for (const auto &ch : seq) {
                node_pool[cur].require_next_map();
                auto &mp = *node_pool[cur].next;
                auto it = mp.find(ch);
                if (it == mp.end()) {
                    node_pool.emplace_back();
                    mp[ch] = node_pool.size() - 1;
                    cur = node_pool.size() - 1;
                } else {
                    cur = it->second;
                }
                ++node_pool[cur].sum;
            }
            ++node_pool[cur].count;
        }

        int count(const sequence_type& seq) const {
            const Node* node = find_node(seq);
            return node ? node->count : 0;
        }

        int count_prefix(const sequence_type& seq) const {
            const Node* node = find_node(seq);
            return node ? node->sum : 0;
        }

        void clear() {
            node_pool.clear();
            node_pool.emplace_back();
        }
    };

}
