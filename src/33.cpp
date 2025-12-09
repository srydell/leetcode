#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  // The idea is to use a binary search over the entire range.
  //
  // One of the keys are that if you divide the range in two, at least one of
  // them is sorted. Based on that you can carry on with a binary search over
  // the sorted part of the range.
  int search(vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      // Did we find it?
      if (nums[mid] == target) {
        return mid;
      }

      // Which side of mid is sorted?
      if (nums[left] <= nums[mid]) {
        // The left side is sorted.
        // Continue with a binary search based on this
        if (nums[left] <= target && target < nums[mid]) {
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      } else {
        // The left side is sorted.
        if (nums[right] >= target && target > nums[mid]) {
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
  {
    Solution solution;
    vector<int> nums = {1, 3};
    int target = 4;
    int expected = -1;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<int> nums = {1, 3};
    int target = 3;
    int expected = 1;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;
    int expected = 4;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 3;
    int expected = -1;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<int> nums = {1};
    int target = 0;
    int expected = -1;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
