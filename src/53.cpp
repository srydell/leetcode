#include "helpers.hpp"

#include <algorithm>
#include <iostream>

using namespace std;
class Solution {
public:
  int maxSubArray(vector<int> &nums) {
    // The idea is to keep building on the same sub array
    // or restart and throw away the old one if it's bad (negative);
    //
    int current = nums[0];
    int best = nums[0];

    for (int i = 1; i < nums.size(); i++) {
      current = max(nums[i] /* restart sub array */,
                    nums[i] + current /* Keep building on this one */);

      best = max(current, best);
    }

    return best;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int expected = 6;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.maxSubArray(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {1};
    int expected = 1;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.maxSubArray(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
  {
    vector<int> nums = {5, 4, -1, 7, 8};
    int expected = 23;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.maxSubArray(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
