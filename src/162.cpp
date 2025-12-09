#include "helpers.hpp"

#include <iostream>
#include <vector>

class Solution {
public:
  int findPeakElement(std::vector<int> &nums) {
    return static_cast<int>(nums.size());
  }
};

int main() {
  Solution solution;

  {
    std::vector<int> nums = {1, 2, 3, 1};
    int expected = 2;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.findPeakElement(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    std::vector<int> nums = {1, 2, 1, 3, 5, 6, 4};
    int expected = 5;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.findPeakElement(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
