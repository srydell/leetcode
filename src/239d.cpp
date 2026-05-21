#include "helpers.hpp"

#include <deque>
#include <iostream>

using namespace std;
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    // For each window over nums we need to know the max of the values within
    // that window It's insufficient to know the current max(current window) as
    // there can be multiple such values. The easiest brute force solution is
    // just to go through each value in each window and find the max. This is
    // probably too inefficient. Another solution is to keep track of the
    // current candidates to be the max for each window, and update as we move
    // it along. One way to do that is with a monotonic queue that keeps track
    // of both the indices and the values of candidates. When the window moves
    // we can retire the candidates that exit the window and the ones that are
    // no longer suitable to be chosen (i.e. a new value is larger). As we move
    // the window, the queue gets populated.
    //
    std::deque<int> dq;

    vector<int> out;

    for (int i = 0; i < nums.size(); i++) {
      // Retire candidates no longer in the window
      while (!dq.empty() && dq.front() <= i - k) {
        dq.pop_front();
      }

      // Retire no longer possible candidates
      // NOTE: Fron the back as they are the 'least' likely
      while (!dq.empty() && nums[dq.back()] <= nums[i]) {
        dq.pop_back();
      }

      dq.push_back(i);

      // Only record max if within a window
      if (i >= k - 1) {
        out.push_back(nums[dq.front()]);
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
