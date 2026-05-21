// Trapping Rain Water
// Difficulty: Hard
//
// Given n non-negative integers representing an elevation map where the width of each bar
// is 1, compute how much water it can trap after raining.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int trap(vector<int> &height) {
    // The trick is to use two pointers that point within the map.
    // Then try to decide for each index, how much water should be above this height?
    // Essentially
    // water at i = min(max height from left, max height from right) - current height
    if (height.empty()) {
      return 0;
    }
    int water = 0;
    int left = 0;
    int right = height.size() - 1;

    int left_max = 0;
    int right_max = 0;

    while (left <= right) {
      left_max = max(left_max, height[left]);
      right_max = max(right_max, height[right]);

      if (left_max <= right_max) {
        // Right side has a wall at least as high as left_max,
        // so this position is limited by left_max
        water += left_max - height[left];
        left++;
      } else {
        // Left side has a wall at least as high as right_max,
        // so this position is limited by right_max
        water += right_max - height[right];
        right--;
      }
    }
    return water;
  }
};

int main() {
  Solution solution;

  {
    // The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
    vector<int> height = vector<int>{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int expected = 6;
    std::cout << "Input:    " << str(height) << '\n';
    auto ans = solution.trap(height);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> height = vector<int>{4, 2, 0, 3, 2, 5};
    int expected = 9;
    std::cout << "Input:    " << str(height) << '\n';
    auto ans = solution.trap(height);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
