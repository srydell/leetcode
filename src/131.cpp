#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  bool isPalindrome(int left, int right, string const &s) {
    if (s.empty()) {
      return false;
    }
    if (s.size() == 1) {
      return true;
    }

    while (left <= right) {
      if (s[left] != s[right]) {
        return false;
      }
      left++;
      right--;
    }

    return true;
  }

  void backtrack(int left, int right, vector<string> parts, string const &s,
                 vector<vector<string>> &allPartitions) {
    if (right >= s.size()) {
      // std::cout << "left=" << left << ", right=" << right
      //           << " parts=" << str(parts) << '\n';
      if (left == right) {
        allPartitions.push_back(parts);
      }
      return;
    }

    // Move forward
    backtrack(left, right + 1, parts, s, allPartitions);

    // Can we choose the current substring?
    if (isPalindrome(left, right, s)) {
      parts.push_back(s.substr(left, right - left + 1));
      backtrack(right + 1, right + 1, parts, s, allPartitions);
    }
  }

  vector<vector<string>> partition(string s) {
    vector<vector<string>> allPartitions;
    backtrack(0, 0, {}, s, allPartitions);
    return allPartitions;
  }
};

int main() {

  {
    Solution solution;
    string s = "aab";
    vector<vector<string>> expected = {{"a", "a", "b"}, {"aa", "b"}};
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.partition(s);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    string s = "a";
    vector<vector<string>> expected = {{"a"}};
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.partition(s);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
