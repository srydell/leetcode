#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int maxProfit(vector<int> &prices) {
    // For every stock at pos p you want to know 'what is the max(prices, where
    // i > p). Start from the back, the max({x}, i > 0) is x
    //

    if (prices.size() < 2) {
      return 0;
    }

    int maxPriceAhead = prices.back();
    int maxProfit = 0;
    for (int i = prices.size() - 2; i >= 0; i++) {
      int profit = maxPriceAhead - prices[i];
      if (profit > maxProfit) {
        maxProfit = profit;
      }

      if (prices[i] > maxPriceAhead) {
        maxPriceAhead = prices[i];
      }
    }

    return maxProfit;
  }
};

int main() {
  Solution solution;

  {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    int expected = 5;
    std::cout << "Input:    " << str(prices) << '\n';
    auto ans = solution.maxProfit(prices);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> prices = {7, 6, 4, 3, 1};
    int expected = 0;
    std::cout << "Input:    " << str(prices) << '\n';
    auto ans = solution.maxProfit(prices);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
