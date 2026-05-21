// Binary Subarrays With Sum
// Difficulty: Medium
//
// Given a binary array nums and an integer goal, return the number of non-empty
// subarrays with a sum goal. A subarray is a contiguous part of the array.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int atMost(vector<int> &nums, int cutoff) {
    // Return the number of windows where the sum of the values is <= cutoff
    if (cutoff < 0) {
      return 0;
    }

    int left = 0;
    int sum = 0;
    int count = 0;
    for (int right = 0; right < nums.size(); right++) {
      sum += nums[right];

      while (sum > cutoff) {
        sum -= nums[left];
        left++;
      }
      // All the suffixes of this window also need to be counted
      count += right - left + 1;
    }

    return count;
  }

  int numSubarraysWithSum(vector<int> &nums, int goal) {
    // The key here is that they want an exact number goal.
    // This is very difficult to solve with just a simple sliding window.
    // Instead we use a trick to have a clean cutoff where the sum of every
    // window should be at least g. This way atMost(g) = exactSum(g) +
    // exactSum(g - 1) + ... and then we can just compute atMost(g) - atMost(g
    // - 1) = exactSum(g) Which is what we're after.
    return atMost(nums, goal) - atMost(nums, goal - 1);
  }
};

int main() {
  Solution solution;

  {
    // The 4 subarrays are bolded and underlined below: [1,0,1,0,1] [1,0,1,0,1]
    // [1,0,1,0,1] [1,0,1,0,1]
    vector<int> nums = vector<int>{1, 0, 1, 0, 1};
    int goal = 2;
    int expected = 4;
    std::cout << "Input:    " << str(nums) << ", " << goal << '\n';
    auto ans = solution.numSubarraysWithSum(nums, goal);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{0, 0, 0, 0, 0};
    int goal = 0;
    int expected = 15;
    std::cout << "Input:    " << str(nums) << ", " << goal << '\n';
    auto ans = solution.numSubarraysWithSum(nums, goal);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
