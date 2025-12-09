#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  void buildParenthesis(int currentIndex, vector<string> &result,
                        string current, int open, int close, int n) {
    if (currentIndex == 2 * n) {
      result.push_back(current);
      return;
    }
    // Can we open one?
    if (open < n) {
      buildParenthesis(currentIndex + 1, result, current + '(', open + 1, close,
                       n);
    }
    // Can we close one?
    if (close < open) {
      buildParenthesis(currentIndex + 1, result, current + ')', open, close + 1,
                       n);
    }
  }

  vector<string> generateParenthesis(int n) {
    vector<string> result;
    buildParenthesis(0, result, "", 0, 0, n);

    return result;
  }
};

int main() {
  Solution solution;

  {
    int n = 3;
    vector<string> expected = {"((()))", "(()())", "(())()", "()(())",
                               "()()()"};
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.generateParenthesis(n);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int n = 1;
    vector<string> expected = {"()"};
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.generateParenthesis(n);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
