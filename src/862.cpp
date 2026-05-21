// Shortest Subarray with Sum at Least K
// Difficulty: Hard
//
// Given an integer array nums and an integer k, return the length of the
// shortest non-empty subarray of nums with a sum of at least k. If there is no
// such subarray, return -1. A subarray is a contiguous part of an array.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int shortestSubarray(vector<int> &nums, int k) {
    // Sliding window type problem
    // The key issue is that nums can contain negative numbers so increasing the
    // window does not necessary increase the sum. Instead we combine the window
    // with a prefix sum and a monotonic deque Idea: Let prefix[i] = sum of
    // nums[0..i-1]
    // Then the subarray sum from j to i-1 is: prefix[i] -
    // prefix[j] We want the shortest i-j such that: prefix[i] - prefix[j] >= k
    // For each i, we want the earliest valid best j, but also we should discard
    // useless prefix sums. The next part is that we should store the indices
    // within a monotonic sum such that prefix[dq[0]] < prefix[dq[1]] < ... Why?
    // If prefix[i] <= prefix[dq.back()]
    // then i is strictly better than dq.back():
    // * later index
    // * smaller or equal prefix sum
    // * gives larger future subarray sums
    // * gives shorter future lengths
    // so we should remove dq.back()

    int n = nums.size();

    vector<long long> prefix(n + 1, 0);
    // Initialize the prefix sum
    for (int i = 0; i < n; i++) {
      prefix[i + 1] = prefix[i] + nums[i];
    }

    deque<int> dq;
    int best = n + 1;

    for (int i = 0; i <= n; i++) {
      // Can we form valid subarrays ending at i-1?
      while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
        best = min(best, i - dq.front());
        dq.pop_front();
      }

      // Maintain increasing prefix sums
      while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
        dq.pop_back();
      }
      dq.push_back(i);
    }
    return best == n + 1 ? -1 : best;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = vector<int>{1};
    int k = 1;
    int expected = 1;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.shortestSubarray(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{1, 2};
    int k = 4;
    int expected = -1;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.shortestSubarray(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{2, -1, 2};
    int k = 3;
    int expected = 3;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.shortestSubarray(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
