// Number of Substrings Containing All Three Characters
// Difficulty: Medium
//
// Given a string s consisting only of characters a, b and c. Return the number
// of substrings containing at least one occurrence of all these characters a, b
// and c.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int numberOfSubstrings(string s) {
    // Exact sliding window problem.
    //
    // Idea: Keep track of the number of a/b/c
    // Shrink the window from the left until it's invalid,
    // then there are left number of valid substrings ending in right
    int left = 0;
    array<int, 3> count{};
    int answer = 0;

    for (int right = 0; right < s.size(); right++) {
      count[s[right] - 'a']++;

      // Shring to invalid
      while (count[0] > 0 && count[1] > 0 && count[2] > 0) {
        count[s[left] - 'a']--;
        left++;
      }

      answer += left;
    }
    return answer;
  }
};

int main() {
  Solution solution;

  {
    // The substrings containing at least one occurrence of the characters a, b
    // and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc",
    // "cab", "cabc" and "abc" (again).
    string s = "abcabc";
    int expected = 10;
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.numberOfSubstrings(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // The substrings containing at least one occurrence of the characters a, b
    // and c are "aaacb", "aacb" and "acb".
    string s = "aaacb";
    int expected = 3;
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.numberOfSubstrings(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string s = "abc";
    int expected = 1;
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.numberOfSubstrings(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
