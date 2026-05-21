#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int search(vector<int> &nums, int target) {
    int left = 0;
    // We know size > 0
    int right = nums.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] == target) {
        return mid;
      }

      if (nums[mid] < target) {
        // To the right
        left = mid + 1;
      } else {
        // To the left
        right = mid - 1;
      }
    }
    return -1;
  }
};

int main() {
  Solution solution;

  {
    std::cout << "Input:    " << 0 << '\n';
    auto ans = solution.search();
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 0 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
