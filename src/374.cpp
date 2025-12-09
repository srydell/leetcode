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
  int actual = 1;
  int guess(int i) {
    if (i == actual) {
      return 0;
    }
    if (i > actual) {
      return -1;
    }
    return 1;
  }

  int guessNumber(int n) {
    int maxNumber = n, minNumber = 1;
    while (true) {
      int meanNumber = (maxNumber - minNumber) / 2 + minNumber;
      // Do NOT use (maxNumber+minNumber)/2 in case of over flow
      int res = guess(meanNumber);
      if (res == 0) {
        return meanNumber;
      } else if (res == 1) {
        minNumber = meanNumber + 1;
      } else {
        maxNumber = meanNumber - 1;
      }
    }
  }
};

int main() {

  {
    Solution solution;
    int n = 10;
    solution.actual = 6;
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.guessNumber(n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << solution.actual << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    int n = 1;
    solution.actual = 1;
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.guessNumber(n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << solution.actual << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    int n = 2;
    solution.actual = 1;
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.guessNumber(n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << solution.actual << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
