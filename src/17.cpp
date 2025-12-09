#include "helpers.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
  string getLetters(char digit) {
    switch (digit) {
    case '2': {
      return "abc";
    }
    case '3': {
      return "def";
    }
    case '4': {
      return "ghi";
    }
    case '5': {
      return "jkl";
    }
    case '6': {
      return "mno";
    }
    case '7': {
      return "pqrs";
    }
    case '8': {
      return "tuv";
    }
    case '9': {
      return "wxyz";
    }
    }
    return {};
  }

  void backtrack(int current_index, string const &digits, vector<string> &out,
                 string current) {
    if (current.size() == digits.size()) {
      out.push_back(current);
      return;
    }

    for (char letter : getLetters(digits[current.size()])) {
      backtrack(current_index + 1, digits, out, current + letter);
    }
  }

  std::vector<std::string> letterCombinations(string digits) {
    vector<string> out;
    backtrack(0, digits, out, "");
    return out;
  }
};

int main() {
  Solution solution;

  {
    string digits = "23";
    vector<string> expected = {"ad", "ae", "af", "bd", "be",
                               "bf", "cd", "ce", "cf"};
    std::cout << "Input:    " << digits << '\n';
    auto ans = solution.letterCombinations(digits);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string digits = "2";
    vector<string> expected = {"a", "b", "c"};
    std::cout << "Input:    " << digits << '\n';
    auto ans = solution.letterCombinations(digits);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
