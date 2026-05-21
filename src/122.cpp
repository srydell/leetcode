#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int maxProfit(vector<int> prices) { return 4; }
};

int main() {
  Solution solution;

  {
    // Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
    // Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3
    // = 3. Total profit is 4 + 3 = 7.
    vector<int> prices = vector<int>{7, 1, 5, 3, 6, 4};
    int expected = 7;
    std::cout << "Input:    " << str(prices) << '\n';
    auto ans = solution.maxProfit(prices);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    // Total profit is 4.
    vector<int> prices = vector<int>{1, 2, 3, 4, 5};
    int expected = 4;
    std::cout << "Input:    " << str(prices) << '\n';
    auto ans = solution.maxProfit(prices);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // There is no way to make a positive profit, so we never buy the stock to
    // achieve the maximum profit of 0.
    vector<int> prices = vector<int>{7, 6, 4, 3, 1};
    int expected = 0;
    std::cout << "Input:    " << str(prices) << '\n';
    auto ans = solution.maxProfit(prices);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
