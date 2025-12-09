#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int n = prices.size();
    if (n == 0)
      return 0;

    std::vector<int> maxPriceAhead(n, 0);
    maxPriceAhead[n - 1] = prices[n - 1];

    for (int i = n - 2; i >= 0; --i) {
      maxPriceAhead[i] = std::max(maxPriceAhead[i + 1], prices[i]);
    }

    int maxProfit = 0;
    for (int i = 0; i < n; ++i) {
      int profit = maxPriceAhead[i] - prices[i];
      maxProfit = std::max(maxProfit, profit);
    }
    return maxProfit;
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
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    std::cout << "Input:    " << str(prices) << '\n';
    auto ans = solution.maxProfit(prices);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 5 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> prices = {7, 6, 4, 3, 1};
    std::cout << "Input:    " << str(prices) << '\n';
    auto ans = solution.maxProfit(prices);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 0 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
