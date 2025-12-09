#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  void buildSubsets(int current, vector<int> subset, vector<int> &nums,
                    vector<vector<int>> &allSubsets) {
    if (current == nums.size()) {
      allSubsets.push_back(subset);
      return;
    }

    // Do not choose this number
    buildSubsets(current + 1, subset, nums, allSubsets);

    // Choose this number
    subset.push_back(nums[current]);
    buildSubsets(current + 1, subset, nums, allSubsets);
  }

  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> allSubsets;
    buildSubsets(0, {}, nums, allSubsets);
    return allSubsets;
  }
};

int main() {

  {
    Solution solution;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> expected = {{},  {1},    {2},    {1, 2},
                                    {3}, {1, 3}, {2, 3}, {1, 2, 3}};
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.subsets(nums);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<int> nums = {0};
    vector<vector<int>> expected = {{}, {0}};
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.subsets(nums);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
