#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  double findMaxAverage(vector<int> &nums, int k) {
    size_t start = 0;
    size_t end = start + static_cast<size_t>(k) - 1;
    double average = accumulate(nums.begin(), nums.begin() + k, 0.0);
    double maxAverage = average;
    for (end++, start++; end < nums.size(); end++, start++) {
      average -= nums[start - 1];
      average += nums[end];
      maxAverage = max(maxAverage, average);
    }
    return maxAverage / k;
  }
};

int main() {
  Solution s;
  {
    vector<int> nums = {1, 12, -5, -6, 50, 3};
    int k = 4;
    auto ans = s.findMaxAverage(nums, k);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 12.75000 << '\n';
  }

  {
    vector<int> nums = {5};
    int k = 1;
    auto ans = s.findMaxAverage(nums, k);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 5.000 << '\n';
  }
}
