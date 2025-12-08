#pragma once

#include <vector>
#include <stdexcept>


namespace algo {

    template <typename T>
    class Heap {
    public:
        int size() {
            return arr.size();
        }

        Heap(bool isMinHeap = true) {
            symbol = isMinHeap ? 1 : -1;
        }

        T top() {
            if (arr.empty()) throw std::out_of_range("Topping on empty heap.");
            return arr[0] * symbol;
        }

        T pop() {
            if (arr.empty()) throw std::out_of_range("Popping on empty heap.");
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
        std::vector<T> arr;

        bool greater(int a, int b) {
            if (b >= arr.size()) return false;
            return arr[a] > arr[b];
        }

        void sink(int pos) {
            while (greater(pos, pos * 2 + 1) || greater(pos, pos * 2 + 2)) {
                if (greater(pos * 2 + 1, pos * 2 + 2)) {
                    std::swap(arr[pos], arr[pos * 2 + 2]);
                    pos = pos * 2 + 2;
                } else {
                    std::swap(arr[pos], arr[pos * 2 + 1]);
                    pos = pos * 2 + 1;
                }
            }
        }

        void _float(int pos) {
            while (pos > 0 && arr[pos] < arr[(pos - 1) >> 1]) {
                std::swap(arr[pos], arr[(pos - 1) >> 1]);
                pos = (pos - 1) >> 1;
            }
        }
    };
}
