#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int search(vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      // We choose a mid point, there is always a side that is sorted
      // Check which side is sorted first

      if (nums[mid] == target) {
        return mid;
      }

      if (nums[left] <= nums[mid]) {
        // left side is sorted. Can it be within the sorted range?
        if (nums[left] <= target && target < nums[mid]) {
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      } else {
        // Right side is sorted. Can it be within the sorted range?
        if (nums[mid] < target && target <= nums[right]) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      }
    }

    return -1;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;
    int expected = 4;
    std::cout << "Input:    " << str(nums) << ", " << target << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 3;
    int expected = -1;
    std::cout << "Input:    " << str(nums) << ", " << target << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {1};
    int target = 0;
    int expected = -1;
    std::cout << "Input:    " << str(nums) << ", " << target << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
