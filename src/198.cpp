#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
class Solution {
public:
  int rob(std::vector<int> &nums) {
    int n = nums.size();
    if (n == 0)
      return 0;
    if (n == 1)
      return nums[0];

    // How much money can we rob up to house i
    vector<int> money_so_far(n, 0);
    money_so_far[0] = nums[0];
    money_so_far[1] = std::max(nums[0], nums[1]);

    for (int i = 2; i < n; i++) {
      // You can either rob this house or not
      // If you do rob it, you can't rob the previous one
      money_so_far[i] =
          std::max(money_so_far[i - 2] + nums[i], money_so_far[i - 1]);
    }
    return money_so_far[n - 1];
  }
};

template <typename T> string str(vector<T> const &v) {
  std::stringstream ss;
  ss << '[';
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    ss << v[i];
    if (i < v.size() - 1) {
      ss << ", ";
    }
  }
  ss << ']';
  return ss.str();
}

int main() {
  Solution solution;

  {
    vector<int> nums = {1, 2, 3, 1};
    int expected = 4;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.rob(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {2, 7, 9, 3, 1};
    int expected = 12;
    std::cout << "Input:    " << str(nums) << '\n';
    auto ans = solution.rob(nums);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
