// Shortest Subarray with Sum at Least K
// Difficulty: Hard
//
// Given an integer array nums and an integer k, return the length of the shortest
// non-empty subarray of nums with a sum of at least k. If there is no such subarray,
// return -1. A subarray is a contiguous part of an array.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int shortestSubarray(vector<int> &nums, int k) {
    // Sliding window problem
    // There is a problem with the values in nums being negative. Then a normal sliding window will not work as the sum does not necessarily increase by increasing the size of the window.
    // Instead keep a prefix sum of nums such that
    // prefix[i] = sum of nums[0...i-1]
    // In that way
    // Sum of subarray between i -> j, where i < j is
    // prefix[j] - prefix[i]
    //
    // Next, keep track of the smallest useful prefix values in increasing order with a monotonic deque such that
    // prefix[dq[0]] >= prefix[dq[1]] >= ...
    // This way we can find the ones where the sum is larger than k

    deque<int> dq;
    int n = nums.size();
    int best = n + 1; // Just a value it cannot become

    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
      prefix[i + 1] = nums[i] + prefix[i];
    }

    for (int i = 0; i <= n; i++) {
      // Can we form a valid subarray ending in i - 1?
      while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
        best = min(best, i - dq.front());
        dq.pop_front();
      }

      // Maintain increasing prefix deque
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
