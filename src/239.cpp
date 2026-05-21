#include "helpers.hpp"

#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    vector<int> maxes;

    std::deque<int> window;
    int current_max = -1;
    for (int i = 0; i < k; i++) {
      window.push_back(nums[i]);
      current_max = max(nums[i], current_max);
    }
    maxes.push_back(current_max);

    return maxes;
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
