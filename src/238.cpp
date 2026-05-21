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
    // Keep two extra arrays, prefix and suffix such that:
    // let ni = nums[i]
    // let N = nums.size()
    // prefix[i] = n0 * n1 * ... * ni-1
    // suffix[i] = nN-1 * ... * ni+1
    // I want
    // answer[i] = prefix[i] * suffix[i]
    // Then
    // answer[0] = prefix[0] * suffix[0]
    // which follows then that prefix[0] = suffix[N-1] = 1

    vector<int> prefix(nums.size(), 1);
    for (int i = 0; i < nums.size() - 1; i++) {
      prefix[i + 1] = prefix[i] * nums[i];
    }

    vector<int> suffix(nums.size(), 1);
    for (int i = nums.size() - 2; i >= 0; i--) {
      suffix[i] = suffix[i + 1] * nums[i + 1];
    }

    vector<int> answer(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++) {
      answer[i] = prefix[i] * suffix[i];
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
