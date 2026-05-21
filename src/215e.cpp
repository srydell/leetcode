#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int findKthLargest(vector<int> nums, int k) { return k; }
};

int main() {
  Solution solution;

  {
    vector<int> nums = vector<int>{3, 2, 1, 5, 6, 4};
    int k = 2;
    int expected = 5;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.findKthLargest(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = vector<int>{3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k = 4;
    int expected = 4;
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.findKthLargest(nums, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
