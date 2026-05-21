#include "helpers.hpp"

#include <deque>
#include <iostream>

using namespace std;
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    // We need to know the max(current window) for each windows moving forward.
    // It's not sufficient to only know the current max of the current window as
    // there can be multiple such values. We need to retire values that are
    // outside of the window and retire values that are to the left of the
    // current maximum (as they will never be chosen) The idea is to keep a
    // monotonic queue of the best values so far. If we keep a queue of indices
    // we can know which to retire as they exit the window

    std::deque<int> indices;

    vector<int> out;

    for (int i = 0; i < nums.size(); i++) {
      // i is leaving the window?
      while (!indices.empty() && indices.front() <= i - k) {
        indices.pop_front();
      }

      // Is the new value larger than any of the current values in the window?
      while (!indices.empty() && nums[indices.back()] <= nums[i]) {
        indices.pop_back();
      }

      // Record this index
      indices.push_back(i);

      // Start recording maxes when the window is built
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
