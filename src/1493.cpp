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
  int longestSubarray(vector<int> &nums) {
    bool hasDeleted = false;
    int longest = 0;
    int maxLongest = longest;
    size_t start = 0;
    for (size_t end = start; end < nums.size(); end++) {
      if (nums[end] == 1) {
        // Simple 1 => Just count up
        longest++;
        maxLongest = max(longest, maxLongest);
      } else {
        // Move start until we can move the hole
        while (hasDeleted && start != end) {
          if (nums[start] == -1) {
            nums[start] = 0;
            hasDeleted = false;
          } else {
            longest--;
          }
          start++;
        }

        nums[end] = -1;
        hasDeleted = true;
      }
    }
    if (!hasDeleted) {
      maxLongest--;
    }
    return maxLongest;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {1, 1, 0, 1};
    auto ans = solution.longestSubarray(nums);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
  }

  {
    vector<int> nums = {0, 1, 1, 1, 0, 1, 1, 0, 1};
    auto ans = solution.longestSubarray(nums);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 5 << '\n';
  }

  {
    vector<int> nums = {1, 1, 1};
    auto ans = solution.longestSubarray(nums);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 2 << '\n';
  }
}
