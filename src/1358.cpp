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
    array<int, 3> count{};
    int left = 0;
    int answer = 0;

    for (int right = 0; right < s.size(); right++) {
      count[s[right] - 'a']++;

      while (count[0] > 0 && count[1] > 0 && count[2] > 0) {
        count[s[left] - 'a']--;
        left++;
      }

      // We shrunk all the answers to the smallest possible array containing
      // abc. All arrays created by expanding to the left from here is valid.
      //
      // Another way:
      // We shrink while the window still contains a, b, and c.
      // When the loop ends, [left..right] is invalid, but every substring
      // ending at right and starting before left was valid. Therefore there are
      // left valid substrings ending at right.
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
