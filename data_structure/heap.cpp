#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>

class Heap {
public:
    inline int size() {
        return arr.size();
    }

    Heap(bool is_min_heap = true) {
        symbol = is_min_heap ? 1 : -1;
    }

    T top() {
        if (arr.size() == 0) throw overflow_error("Topping on empty heap.");
        return arr[0] * symbol;
    }

    T pop() {
        if (arr.size() == 0) throw overflow_error("Popping on empty heap.");
        T ret = arr[0] * symbol;
        arr[0] = *--arr.end();
        arr.pop_back();
        sink(0);
        return ret;
    }

    void add(T x) {
        arr.push_back(x * symbol);
        _float(arr.size() - 1);
    }
private:
    short symbol;
    vector<T> arr;

    inline bool greater(int a, int b) {
        if (b >= arr.size()) return false;
        return arr[a] > arr[b];
    }

    void sink(int pos) {
        while (greater(pos, pos * 2 + 1) || greater(pos, pos * 2 + 2)) {
            if (greater(pos * 2 + 1, pos * 2 + 2)) {
                swap(arr[pos], arr[pos * 2 + 2]);
                pos = pos * 2 + 2;
            } else {
                swap(arr[pos], arr[pos * 2 + 1]);
                pos = pos * 2 + 1;
            }
        }
    }

    void _float(int pos) {
        while (pos > 0 && arr[pos] < arr[(pos - 1) >> 1]) {
            swap(arr[pos], arr[(pos - 1) >> 1]);
            pos = (pos - 1) >> 1;
        }
    }
};

void TestHeap(int n) {
    srand(time(NULL));
    vector<double> a(n);
    Heap<double> heap(false);

    for (int i = 0; i < n; i ++) {
        int x = double(rand()) / double(rand());
        a[i] = x;
        heap.add(x);
    }
    sort(a.begin(), a.end());

    for (int i = 0; i < n; i ++) {
        if (a[n - i - 1] != heap.pop()) {
            cout<<"Test Failed"<<endl;
            return;
        }
    }
    cout<<"Test Passed"<<endl;
}

// int main() {
//     TestHeap(100000);
//     return 0;
// }