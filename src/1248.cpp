// Count Number of Nice Subarrays
// Difficulty: Medium
//
// Given an array of integers nums and an integer k. A continuous subarray is
// called nice if there are k odd numbers on it. Return the number of nice
// sub-arrays.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int atMost(vector<int> &nums, int cutoff) {
    if (cutoff < 0) {
      return 0;
    }

    int left = 0;
    int answer = 0;
    int oddCount = 0;
    for (int right = 0; right < nums.size(); right++) {
      oddCount += nums[right] % 2 == 1;

      while (oddCount > cutoff) {
        oddCount -= nums[left] % 2 == 1;
        left++;
      }

      // All the suffixes of this array also has at most cutoff odd numbers in
      // it
      answer += right - left + 1;
    }
    return answer;
  }

  int numberOfSubarrays(vector<int> &nums, int k) {
    // A subarray is 'nice' if there are *exactly* k odd numbers within it.
    // Exactly is difficult to count with a slidinw window type solution.
    // Instead count the subarrays that have at most k odd numbers. This way
    // atMost(k) = exactly(0) + exactly(1) + ... + exactly(k)
    // and therefore
    // exactly(k) = atMost(k) - atMost(k-1)
    return atMost(nums, k) - atMost(nums, k - 1);
  }
};

int main() {
  Solution solution;

  {
    // The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
    vector<int> nums = vector<int>{1, 1, 2, 1, 1};
    int k = 3;
    int expected = 2;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.numberOfSubarrays(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // There are no odd numbers in the array.
    vector<int> nums = vector<int>{2, 4, 6};
    int k = 1;
    int expected = 0;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.numberOfSubarrays(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{2, 2, 2, 1, 2, 2, 1, 2, 2, 2};
    int k = 2;
    int expected = 16;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.numberOfSubarrays(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
