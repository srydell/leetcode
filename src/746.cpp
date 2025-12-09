#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
class Solution {
public:
  int minCostClimbingStairs(std::vector<int> &cost) {
    int n = cost.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = 0;

    for (int i = 2; i <= n; i++) {
      dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }
    return dp[n];
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
    vector<int> cost = {10, 15, 20};
    int expected = 15;
    std::cout << "Input:    " << str(cost) << '\n';
    auto ans = solution.minCostClimbingStairs(cost);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    int expected = 6;
    std::cout << "Input:    " << str(cost) << '\n';
    auto ans = solution.minCostClimbingStairs(cost);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
