#include "helpers.hpp"

#include <deque>
#include <iostream>

using namespace std;
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    // For each of the windows we need to know the largest value.
    // It's not sufficient to know the currently largest value and if that goes
    // out of scope as there can be multiple of that value. Idea is to save a
    // monotonic dequeue that will help us keep track of both the values and the
    // indices for thos values This way we can both keep track of a new incoming
    // larger value (all values to the left that are smaller can then be
    // discarded as they will never be chosen) AND the indices that will be
    // removed as the window moves to the right.

    // Indices to the largest values in the current window
    // Largest value is at nums[indices.front()]
    std::deque<int> indices;

    vector<int> out;

    for (int i = 0; i < nums.size(); i++) {
      // Remove values that are no longer in the window
      while (!indices.empty() && indices.front() <= i - k) {
        indices.pop_front();
      }

      // Maintain values in decreasing order
      while (!indices.empty() && nums[indices.back()] <= nums[i]) {
        indices.pop_back();
      }

      // Store this value
      indices.push_back(i);

      // Record first value only when the full first window has been created
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
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<int> expected = {3, 3, 5, 5, 6, 7};
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.maxSlidingWindow(nums, k);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
