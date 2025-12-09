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
      if (nums[mid] == target) {
        return mid;
      }

      if (nums[mid] > target) {
        // It's in the left range
        right = mid - 1;
      } else {
        // It's in the right range
        left = mid + 1;
      }
    }
    return -1;
  }
};

int main() {

  {
    Solution solution;
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 9;
    int expected = 4;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 2;
    int expected = -1;
    std::cout << "Input:    " << target << ", " << str(nums) << '\n';
    auto ans = solution.search(nums, target);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
