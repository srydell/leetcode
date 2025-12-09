#include "helpers.hpp"

#include <algorithm>
#include <iostream>

using namespace std;
class Solution {
public:
  void buildPermutation(vector<int> perm, vector<int> const &nums,
                        vector<vector<int>> &out) {
    if (perm.size() == nums.size()) {
      out.push_back(perm);
      return;
    }

    for (auto num : nums) {
      if (std::find(perm.begin(), perm.end(), num) == perm.end()) {
        perm.push_back(num);
        buildPermutation(perm, nums, out);
        perm.pop_back();
      }
    }
  }

  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> out;
    buildPermutation({}, nums, out);
    return out;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> expected = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                    {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.permute(nums);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {0, 1};
    vector<vector<int>> expected = {{0, 1}, {1, 0}};
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.permute(nums);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {1};
    vector<vector<int>> expected = {{1}};
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.permute(nums);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
