#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  vector<int> twoSum2(vector<int> &nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
      for (int j = i + 1; j < nums.size(); j++) {
        if (nums[i] + nums[j] == target) {
          return {i, j};
        }
      }
    }

    return {-1, -1};
  }

  vector<int> twoSum(vector<int> &nums, int target) {
    map<int, int> seen;

    for (int i = 0; i < nums.size(); i++) {
      int complement = target - nums[i];

      if (seen.contains(complement)) {
        return {seen[complement], i};
      }

      seen[nums[i]] = i;
    }

    return {-1, -1};
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> expected = {0, 1};
    std::cout << "Input:    nums = " << str(nums) << ", target = " << target
              << '\n';
    auto ans = solution.twoSum(nums, target);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
