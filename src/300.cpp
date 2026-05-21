// Longest Increasing Subsequence
// Difficulty: Medium
//
// Given an integer array nums, return the length of the longest strictly increasing
// subsequence.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int lengthOfLIS(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    // Invariant: dp[i] = length of the longest subsequence ending exactly in i

    int best = 1;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        if (nums[j] < nums[i]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
      best = max(best, dp[i]);
    }
    return best;
  }
};

int main() {
  Solution solution;

  {
    // The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
    vector<int> nums = vector<int>{10, 9, 2, 5, 3, 7, 101, 18};
    int expected = 4;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.lengthOfLIS(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{0, 1, 0, 3, 2, 3};
    int expected = 4;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.lengthOfLIS(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{7, 7, 7, 7, 7, 7, 7};
    int expected = 1;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.lengthOfLIS(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
