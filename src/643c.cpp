// Maximum Average Subarray I
// Difficulty: Easy
//
// You are given an integer array nums consisting of n elements, and an integer
// k. Find a contiguous subarray whose length is equal to k that has the maximum
// average value and return this value. Any answer with a calculation error less
// than 10-5 will be accepted.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  double findMaxAverage(vector<int> nums, int k) {
    double current = 0.0;

    // Initialize the window average
    for (int i = 0; i < k; i++) {
      current += nums[i];
    }

    // Move the window forward and keep track of the best average
    double best = current;
    for (int right = k; right < nums.size(); right++) {
      current = current - nums[right - k] + nums[right];
      best = max(best, current);
    }

    return best / k;
  }
};

int main() {
  Solution solution;

  {
    // Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75
    vector<int> nums = vector<int>{1, 12, -5, -6, 50, 3};
    int k = 4;
    double expected = 12.75000;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.findMaxAverage(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{5};
    int k = 1;
    double expected = 5.00000;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.findMaxAverage(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
