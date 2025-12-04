#include <iostream>

using namespace std;

void loopSubSet(int n) {
    for (int s = n; s; s = (s - 1) & n) {
        cout<<s<<endl;
    }
}

int nextComb(int comb) {
    int x = comb & -comb, y = comb + x;
    return ((comb & ~y) / x >> 1) | y;
}

void loopKSubSet(int n, int k) {
    for (int comb = (1 << k) - 1; comb < 1 << n; comb = nextComb(comb)) {
        cout<<comb<<endl;
    }
}

// int main() {
//     loopSubSet(100);
//     cout<<"============="<<endl;
//     loopKSubSet(5, 3);
// }
