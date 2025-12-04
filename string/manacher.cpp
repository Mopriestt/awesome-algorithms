#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Manacher {
public:
    string s;
    string st;
    int n;
    vector<int> rad;
    Manacher(string s) {
        this -> s = s;
        n = s.size();
        calc();
    }

    void init() {
        rad.resize(n * 2 + 2);
        st.resize(n * 2 + 2);
        st[0] = '$';
        for (int i = 0; i < n; i ++) {
            st[i * 2 + 1] = '#';
            st[i * 2 + 2] = s[i];
        }
        st[n * 2 + 1] = '#';
    }

    void calc() {
        init();
        
        int i, mx = 0,id = 0;
        for (i = 1; i < st.size(); i ++)
        {
            if (mx > i) rad[i] = min(rad[2 * id - i], mx - i);
            else rad[i] = 1;
            while (st[i + rad[i]]==st[i - rad[i]]) rad[i] ++;
            if (rad[i] + i > mx)
            {
                mx = rad[i] + i;
                id = i;
            }
        }
    }

    inline int _getCenter(int l, int r) {
        return l + r + 2;
    }

    inline bool isPalindrom(int l, int r) {
        return rad[_getCenter(l, r)] >= r - l + 1;
    }

    inline int maxRad(int x) {
        return rad[x * 2 + 2] / 2;
    }

    inline int maxRad(int l, int r) {
        return rad[_getCenter(l, r)] / 2;
    }
};

bool test_palindrom(string &s, int l, int r) {
    string a, b;
    for (int i = l; i <= r; i ++) a += s[i];
    for (int i = r; i >= l; i --) b += s[i];
    return a == b;
}

int test_rad(string &s, int l, int r) {
    if (s[l] != s[r]) return 0;
    int ct = 0;
    while (l >= 0 && r < s.size() && s[l] == s[r]) {
        ++ ct;
        -- l, ++ r;
    }
    return ct;
}

void test_manacher(int n, int charSet) {
    string s;
    for (int i = 0; i < n; i ++) s += rand() % charSet + 'a';
    Manacher m(s);
    for (int i = 0; i < n; i ++)
        for (int j = i; j < n; j ++)
            if (test_palindrom(s, i, j) != m.isPalindrom(i, j)) {
                cout<<"Test failed!"<<endl;
                return;
            }
    for (int i = 0; i < n; i ++) {
        if (test_rad(s, i, i) != m.maxRad(i)) {
            cout<<"Test failed!"<<endl;
            return;
        }
        if (i < n - 1 && test_rad(s, i, i + 1) != m.maxRad(i, i + 1)) {
            cout<<"Test failed!"<<endl;
            return;
        }
    }
    cout<<"Test passed"<<endl;
}

// int main() {
//     srand(time(0));
//     test_manacher(100, 1);
//     test_manacher(300, 2);
//     test_manacher(500, 2);
//     test_manacher(500, 3);
//     test_manacher(1000, 3);
//     return 0;
// }