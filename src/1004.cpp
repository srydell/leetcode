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
  int longestOnes(vector<int> &nums, int k) {
    size_t start = 0;
    int length = 0;
    int maxLength = length;
    for (size_t end = start; end < nums.size(); end++) {
      if (nums[end] == 0) {
        if (k > 0) {
          // We can flip it
          nums[end] = -1;
          k--;
          length++;
          maxLength = max(length, maxLength);
        } else {
          // k is 0 and the next is 0
          // => Move start forward until we can steal a k (nums[start] == -1)
          //    or we reach start == end
          while (nums[start] != -1 && start != end) {
            length--;
            start++;
          }
          // We push start one since we flipped the previous start value
          nums[start] = 0;
          nums[end] = -1;
          start++;
          // k is unchanged since we flip end with the flipped start
        }
      } else {
        // Just a 1
        length++;
        maxLength = max(length, maxLength);
      }
    }

    return maxLength;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    int k = 2;
    auto ans = solution.longestOnes(nums, k);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 6 << '\n';
  }

  {
    vector<int> nums = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0,
                        1, 1, 0, 0, 0, 1, 1, 1, 1};
    int k = 3;
    auto ans = solution.longestOnes(nums, k);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 10 << '\n';
  }

  {
    vector<int> nums = {1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0,
                        0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1,
                        1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1};
    int k = 8;
    auto ans = solution.longestOnes(nums, k);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 25 << '\n';
  }
}
