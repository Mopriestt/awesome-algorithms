#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace algo {
    class SubHash64 {
    public:
        using u64 = std::uint64_t;
        static constexpr u64 BASE = 13154239110511ull;

        explicit SubHash64(const std::string& s) {
            build_from_chars(s);
        }

        explicit SubHash64(const std::vector<int>& v) {
            build_from_ints(v);
        }

        u64 full_hash() const {
            return pre_[n_];
        }

        u64 sub_hash(int l, int r) const {
            int len = r - l + 1;
            return pre_[r + 1] - pre_[l] * pow_[len];
        }

        int size() const { return n_; }

    private:
        int n_ = 0;
        std::vector<u64> pre_; // prefix hash
        std::vector<u64> pow_; // BASE^i

        void build_from_chars(const std::string& s) {
            n_ = static_cast<int>(s.size());
            pre_.assign(n_ + 1, 0);
            pow_.assign(n_ + 1, 0);

            pow_[0] = 1;
            for (int i = 0; i < n_; ++i) {
                pow_[i + 1] = pow_[i] * BASE;
                u64 x = static_cast<unsigned char>(s[i]);
                pre_[i + 1] = pre_[i] * BASE + x;
            }
        }

        void build_from_ints(const std::vector<int>& v) {
            n_ = static_cast<int>(v.size());
            pre_.assign(n_ + 1, 0);
            pow_.assign(n_ + 1, 0);

            pow_[0] = 1;
            for (int i = 0; i < n_; ++i) {
                pow_[i + 1] = pow_[i] * BASE;
                u64 x = static_cast<u64>(v[i]);
                pre_[i + 1] = pre_[i] * BASE + x;
            }
        }
    };

    inline uint64_t hash(const std::string& s) {
        static constexpr uint64_t BASE = 13154239110511ull;
        uint64_t hash = 0;
        for (const auto& c : s) {
            hash = hash * BASE + static_cast<unsigned char>(c);
        }
        return hash;
    }

    inline uint64_t hash(const std::string& s, const uint64_t seed) {
        uint64_t hash = 0;
        for (const auto& c : s) {
            hash = hash * seed + static_cast<unsigned char>(c);
        }
        return hash;
    }

    inline uint64_t hash(const std::vector<int>& s) {
        static constexpr uint64_t BASE = 13154239110511ull;
        uint64_t hash = 0;
        for (const auto& c : s) {
            hash = hash * BASE + static_cast<uint64_t>(c);
        }
        return hash;
    }

    inline uint64_t hash(const std::vector<int>& s, const uint64_t seed) {
        uint64_t hash = 0;
        for (const auto& c : s) {
            hash = hash * seed + static_cast<uint64_t>(c);
        }
        return hash;
    }
}