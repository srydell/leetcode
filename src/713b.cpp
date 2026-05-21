// Subarray Product Less Than K
// Difficulty: Medium
//
// Given an array of integers nums and an integer k, return the number of
// contiguous subarrays where the product of all the elements in the subarray is
// strictly less than k.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int numSubarrayProductLessThanK(vector<int> &nums, int k) {
    if (k <= 1) {
      return 0;
    }
    // Variable size sliding window problem
    int left = 0;
    int count = 0;
    long long prod = 1;

    for (int right = 0; right < nums.size(); right++) {
      prod *= nums[right];

      while (prod >= k) {
        // Remove from the left
        prod /= nums[left];
        left++;
      }

      if (prod < k) {
        // All suffixes of this valid window ending at right are valid
        count += right - left + 1;
      }
    }
    return count;
  }
};

int main() {
  Solution solution;

  {
    // The 8 subarrays that have product less than 100 are: [10], [5], [2], [6],
    // [10, 5], [5, 2], [2, 6], [5, 2, 6] Note that [10, 5, 2] is not included
    // as the product of 100 is not strictly less than k.
    vector<int> nums = vector<int>{10, 5, 2, 6};
    int k = 100;
    int expected = 8;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.numSubarrayProductLessThanK(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{1, 2, 3};
    int k = 0;
    int expected = 0;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.numSubarrayProductLessThanK(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
