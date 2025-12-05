#pragma once

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
                std::unordered_map<element_type, std::unique_ptr<Node>>
            > next;
            void require_next_map() {
                if (next != nullptr) return;
                next = std::make_unique<std::unordered_map<element_type, std::unique_ptr<Node>>>();
            }
            Node() : count(0), sum(0), next(nullptr) {}
        } root;

    public:
        void add(const sequence_type& seq) {
            auto cur = &root;
            ++cur->sum;
            for (const auto &ch : seq) {
                cur->require_next_map();
                auto [it, inserted] =
                    cur->next->try_emplace(ch, std::make_unique<Node>());
                cur = it->second.get();
                ++cur->sum;
            }
            ++cur->count;
        }

        int count(const sequence_type& seq) const {
            auto cur = &root;

            for (const auto &ch : seq) {
                if (!cur->next) return 0;
                auto it = cur->next->find(ch);
                if (it == cur->next->end()) return 0;
                cur = it->second.get();
            }
            return cur->count;
        }

        int count_prefix(const sequence_type& seq) const {
            const Node* cur = &root;
            for (const auto& ch : seq) {
                if (!cur->next) return 0;
                const auto& mp = *cur->next;
                auto it = mp.find(ch);
                if (it == mp.end()) return 0;
                cur = it->second.get();
            }
            return cur->sum;
        }

        void clear() {
            root = Node{};
        }
    };

}
