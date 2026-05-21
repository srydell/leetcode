// Product of Array Except Self
// Difficulty: Medium
//
// Given an integer array nums, return an array answer such that answer[i] is equal to the
// product of all the elements of nums except nums[i]. The product of any prefix or suffix
// of nums is guaranteed to fit in a 32-bit integer. You must write an algorithm that runs
// in O(n) time and without using the division operation.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    // It doesn't matter in which order the product is taken, so one can do it one at a time.
    //
    int n = nums.size();
    vector<int> answer(n);

    int prefix = 1;
    for (int i = 0; i < n; i++) {
      answer[i] = prefix;
      prefix *= nums[i];
    }

    int suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
      answer[i] *= suffix;
      suffix *= nums[i];
    }
    return answer;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = vector<int>{1, 2, 3, 4};
    vector<int> expected = vector<int>{24, 12, 8, 6};
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.productExceptSelf(nums);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{-1, 1, 0, -3, 3};
    vector<int> expected = vector<int>{0, 0, 9, 0, 0};
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.productExceptSelf(nums);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
