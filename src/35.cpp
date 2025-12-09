#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size();
    int pivot;

    if (target > nums[right - 1]) {
      return right;
    }

    while (left <= right) {
      pivot = (left + right) / 2;

      if (target == nums[pivot]) {
        return pivot;
      }

      if (target > nums[pivot]) {
        left = pivot + 1;
      } else {
        right = pivot - 1;
      }
    }
    return left;
  }
};

int main() {

  {
    Solution solution;
    vector<int> nums = {1, 3, 5, 6};
    int target = 5;
    int expected = 2;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.searchInsert(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<int> nums = {1, 3, 5, 6};
    int target = 2;
    int expected = 1;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.searchInsert(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<int> nums = {1, 3, 5, 6};
    int target = 7;
    int expected = 4;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.searchInsert(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
