// Sliding Window Maximum
// Difficulty: Hard
//
// You are given an array of integers nums, there is a sliding window of size k
// which is moving from the very left of the array to the very right. You can
// only see the k numbers in the window. Each time the sliding window moves
// right by one position. Return the max sliding window.

#include "helpers.hpp"

#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    // Fixed size sliding window problem
    // Need a fast way to keep track of the indices corresponding to the largest
    // value within the current window Keep track through a monotonic deque of
    // indices (and therefore values)
    deque<int> indices;
    std::vector<int> out;

    for (int i = 0; i < nums.size(); i++) {
      // Remove indices no longer within the current window
      while (!indices.empty() && indices.front() <= i - k) {
        indices.pop_front();
      }

      // Remove indices that can no longer be the largest value
      while (!indices.empty() && nums[indices.back()] <= nums[i]) {
        indices.pop_back();
      }

      // Record this index
      indices.push_back(i);

      // Record max within a window
      if (i >= k - 1) {
        out.push_back(nums[indices.front()]);
      }
    }

    return out;
  }
};

int main() {
  Solution solution;

  {
    // Window position Max --------------- ----- [1 3 -1] -3 5 3 6 7 3 1 [3 -1
    // -3] 5 3 6 7 3 1 3 [-1 -3 5] 3 6 7 5 1 3 -1 [-3 5 3] 6 7 5 1 3 -1 -3 [5 3
    // 6] 7 6 1 3 -1 -3 5 [3 6 7] 7
    vector<int> nums = vector<int>{1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<int> expected = vector<int>{3, 3, 5, 5, 6, 7};
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.maxSlidingWindow(nums, k);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{1};
    int k = 1;
    vector<int> expected = vector<int>{1};
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.maxSlidingWindow(nums, k);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
