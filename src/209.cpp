// Minimum Size Subarray Sum
// Difficulty: Medium
//
// Given an array of positive integers nums and a positive integer target,
// return the minimal length of a subarray whose sum is greater than or equal to
// target. If there is no such subarray, return 0 instead.

#include "helpers.hpp"

#include <iostream>
#include <limits>

using namespace std;
class Solution {
public:
  int minSubArrayLen(int target, vector<int> nums) {
    // Variable sliding window problem
    // All numbers are >0
    // Find min(sum(window)) >= target
    // Invariant: The sum(window) >= target
    // Idea: Whenever the sum is larger than target
    // move left pointer as far as possible while maintaining invariant

    int best = std::numeric_limits<int>::max();
    int left = 0;
    int currentSum = 0;
    for (int right = 0; right < nums.size(); right++) {
      currentSum += nums[right];
      while (currentSum >= target) {
        best = min(best, right - left + 1);
        currentSum -= nums[left];
        left++;
      }
    }
    return best == std::numeric_limits<int>::max() ? 0 : best;
  }
};

int main() {
  Solution solution;

  {
    // The subarray [4,3] has the minimal length under the problem constraint.
    int target = 7;
    vector<int> nums = vector<int>{2, 3, 1, 2, 4, 3};
    int expected = 2;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.minSubArrayLen(target, nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int target = 4;
    vector<int> nums = vector<int>{1, 4, 4};
    int expected = 1;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.minSubArrayLen(target, nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int target = 11;
    vector<int> nums = vector<int>{1, 1, 1, 1, 1, 1, 1, 1};
    int expected = 0;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.minSubArrayLen(target, nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
