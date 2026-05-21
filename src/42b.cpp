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
    // The idea is that at each index i
    // you can determine the height of the water if you know the max of the height from the left and right as well as the height at i as in:
    // water at i = min(max height from left, max height from right) - heigth at i
    // Basically you're saying "I know the lowest highest wall from both sides, that is the delimiting factor"
    //
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
        // Know that there is a wall to the right at least as high as left_max, i.e. this water level must be delimited by left_max
        water += left_max - height[left];
        left++;
      } else {
        // Know that there is a wall to the right at least as high as right_max, i.e. this water level must be delimited by right_max
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
