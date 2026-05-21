#include "helpers.hpp"

#include <algorithm>
#include <iostream>

using namespace std;
class Solution {
public:
  int partition(vector<int> &nums, int left, int right) {
    int pivot = nums[right];
    int store = left;

    for (int i = left; i < right; i++) {
      if (nums[i] > pivot) {
        std::swap(nums[i], nums[store++]);
      }
    }

    swap(nums[store], nums[right]);
    return store;
  }

  int findKthLargest(vector<int> &nums, int k) {
    int target = k - 1;
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int p = partition(nums, left, right);
      if (p == target) {
        return nums[p];
      }
      if (p < target) {
        left = p + 1;
      } else {
        right = p - 1;
      }
    }
    return -1;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;
    int expected = 5;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.findKthLargest(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k = 4;
    int expected = 4;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.findKthLargest(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
