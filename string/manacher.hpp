#pragma once

#include <string>
#include <vector>

namespace algo {

    class Manacher {
    public:
        std::string s;
        std::string st;   // transformed string: ^ # s0 # s1 # ... # sn-1 # $
        int n;
        std::vector<int> rad; // radius in transformed string

        explicit Manacher(std::string s)
            : s(std::move(s)), n(static_cast<int>(this->s.size())) {
            calc();
        }

        // Return whether [l, r] is palindrome
        bool isPalindrome(int l, int r) const {
            int len = r - l + 1;
            return maxRad(l, r) * 2 >= len;
        }

        // Longest odd-length palindrome radius centered at s[x]:
        // max k such that s[x-k..x+k] is a palindrome.
        int maxRad(int x) const {
            int r = rad[x * 2 + 2];
            return r / 2;
        }

        // Radius around the center of substring [l, r] in the original string.
        // (Works for both odd and even "visual" centers.)
        int maxRad(int l, int r) const {
            int c = getCenter(l, r);
            int r0 = rad[c];
            return r0 / 2;
        }

    private:
        void calc() {
            initTransformed();

            int m = static_cast<int>(st.size());
            rad.assign(m, 0);

            int center = 0, right = 0;
            for (int i = 1; i < m - 1; ++i) { // 避开两端哨兵
                if (i < right) {
                    int mirror = 2 * center - i;
                    rad[i] = std::min(rad[mirror], right - i);
                } else {
                    rad[i] = 1;
                }
                while (st[i + rad[i]] == st[i - rad[i]]) {
                    ++rad[i];
                }
                if (i + rad[i] > right) {
                    right = i + rad[i];
                    center = i;
                }
            }
        }

        void initTransformed() {
            int m = 2 * n + 3;
            st.resize(m);
            st[0] = '^';
            for (int i = 0; i < n; ++i) {
                st[2 * i + 1] = '#';
                st[2 * i + 2] = s[i];
            }
            st[2 * n + 1] = '#';
            st[2 * n + 2] = '$';
        }

        static int getCenter(int l, int r) {
            return l + r + 2;
        }
    };

}
