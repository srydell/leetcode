#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int pivotIndex(vector<int> &nums) {

    vector<int> leftSum(nums.size(), 0);
    vector<int> rightSum(nums.size(), 0);

    int left = 0;
    int right = 0;
    size_t j = nums.size() - 1;
    for (size_t i = 0; i < nums.size(); i++, j--) {
      left += nums[i];
      right += nums[j];
      leftSum[i] = left;
      rightSum[j] = right;
    }
    for (size_t i = 0; i < nums.size(); i++) {
      if (leftSum[i] == rightSum[i]) {
        return static_cast<int>(i);
      }
    }
    return -1;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {1, 7, 3, 6, 5, 6};
    auto ans = solution.pivotIndex(nums);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
  }

  {
    vector<int> nums = {1, 2, 3};
    auto ans = solution.pivotIndex(nums);
    std::cout << ans << '\n';
    std::cout << "Expected: " << -1 << '\n';
  }

  {
    vector<int> nums = {2, 1, -1};
    auto ans = solution.pivotIndex(nums);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 0 << '\n';
  }
}
