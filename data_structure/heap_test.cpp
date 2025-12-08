#include "gtest/gtest.h"
#include "heap.hpp"

TEST(HeapTest, MinHeapBasic) {
    algo::Heap<int> h(true);  // min-heap

    // Initially empty
    EXPECT_EQ(h.size(), 0);

    // Add some elements
    h.add(5);
    h.add(1);
    h.add(3);
    h.add(4);
    h.add(2);

    EXPECT_EQ(h.size(), 5);

    // Top should be the smallest
    EXPECT_EQ(h.top(), 1);

    // Popping should give non-decreasing sequence
    int last = h.pop();
    EXPECT_EQ(last, 1);
    EXPECT_EQ(h.size(), 4);

    while (h.size() > 0) {
        int cur = h.pop();
        EXPECT_GE(cur, last);  // heap is min-heap, so each popped element >= previous
        last = cur;
    }

    EXPECT_EQ(h.size(), 0);

    // Popping / topping on empty should throw
    EXPECT_THROW(h.pop(), std::out_of_range);
    EXPECT_THROW(h.top(), std::out_of_range);
}

TEST(HeapTest, MaxHeapBasic) {
    algo::Heap<int> h(false);  // max-heap

    // Add some elements
    h.add(5);
    h.add(1);
    h.add(3);
    h.add(4);
    h.add(2);

    EXPECT_EQ(h.size(), 5);

    // Top should be the largest
    EXPECT_EQ(h.top(), 5);

    // Popping should give non-increasing sequence
    int last = h.pop();
    EXPECT_EQ(last, 5);
    EXPECT_EQ(h.size(), 4);

    while (h.size() > 0) {
        int cur = h.pop();
        EXPECT_LE(cur, last);  // max-heap: each popped element <= previous
        last = cur;
    }

    EXPECT_EQ(h.size(), 0);
}

TEST(HeapTest, MixedOperations) {
    algo::Heap<int> h(true);  // min-heap

    h.add(10);
    h.add(5);
    EXPECT_EQ(h.top(), 5);

    // pop once
    EXPECT_EQ(h.pop(), 5);
    EXPECT_EQ(h.top(), 10);

    // add more values
    h.add(7);
    h.add(3);
    h.add(8);
    // heap now contains: 10, 7, 3, 8 (as a min-heap)

    EXPECT_EQ(h.top(), 3);

    EXPECT_EQ(h.pop(), 3);
    EXPECT_EQ(h.pop(), 7);
    EXPECT_EQ(h.pop(), 8);
    EXPECT_EQ(h.pop(), 10);
    EXPECT_EQ(h.size(), 0);

    EXPECT_THROW(h.top(), std::out_of_range);
}
