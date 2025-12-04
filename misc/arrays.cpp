#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int partition(vector<int> &nums, int l, int r, int k) {
    int x = nums[r], pivot = l;
    for (int j = l; j < r; j ++)
        if (nums[j] <= x) {
            swap(nums[j], nums[pivot]);
            ++ pivot;
        }
    swap(nums[pivot], nums[r]);
    return pivot;
}

// All distinct number
int getKthSmallest(vector<int> &nums, int l, int r, int k) {
    if (l == r) return nums[l];

    int pivotIndex = partition(nums, l, r, k);

    if (k <= pivotIndex - l) return getKthSmallest(nums, l, pivotIndex - 1, k);
    return getKthSmallest(nums, pivotIndex, r, k - (pivotIndex - l));
}

// int main() {
//     vector<int> testData;
//     testData = {1,2,3,4,5};
//
//     cout<<getKthSmallest(testData, 0, testData.size() - 1, 1);
//
//     return 0;
// }