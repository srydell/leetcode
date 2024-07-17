#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int guessNumber(int n) {
    return n;
  }
};

int main() {
  Solution solution;

  {
    int n = 10;
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.guessNumber(n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 6 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int n = 1;
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.guessNumber(n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 1 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int n = 2;
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.guessNumber(n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 1 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
