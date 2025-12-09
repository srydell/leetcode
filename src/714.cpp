#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
class Solution {
public:
  // One can either buy, sell or do nothing.
  // If one has sold before, then one can buy,
  // if one has bought, then one can sell,
  // and you can always do nothing.
  // Buying a share at time t always means the same thing
  // for profit going forward (i.e. doesn't matter what you did before).
  // Therefore if there are two paths to buying at time t,
  // the maxProfit from time t is a constant subproblem between the two.
  vector<int> prices_ = {};
  int fee_ = 0;
  int best_profit_ = 0;
  int maxProfit(vector<int> &prices, int fee) {
    prices_ = prices;
    fee_ = fee;
    best_profit_ = 0;
    get_best_profit();
    return best_profit_;
  }

  void get_best_profit(bool has_share = false, int time = 0,
                       int current_profit = 0) {
    if (time >= prices_.size()) {
      if (current_profit > best_profit_) {
        best_profit_ = current_profit;
      }
      return;
    }

    // Either choose to do nothing
    get_best_profit(has_share, time + 1, current_profit);

    if (has_share) {
      // Sell it
      get_best_profit(!has_share, time + 1,
                      current_profit + prices_[time] - fee_);
    } else {
      // Buy it
      get_best_profit(!has_share, time + 1, current_profit - prices_[time]);
    }
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
    std::vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    std::cout << "Input:    " << str(prices) << ", " << fee << '\n';
    auto ans = solution.maxProfit(prices, fee);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 8 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    std::vector<int> prices = {1, 3, 7, 5, 10, 3};
    int fee = 3;
    std::cout << "Input:    " << str(prices) << ", " << fee << '\n';
    auto ans = solution.maxProfit(prices, fee);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 6 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
