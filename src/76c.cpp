// Minimum Window Substring
// Difficulty: Hard
//
// Given two strings s and t of lengths m and n respectively, return the minimum window
// substring of s such that every character in t (including duplicates) is included in the
// window. If there is no such substring, return the empty string "". The testcases will be
// generated such that the answer is unique.

#include "helpers.hpp"

#include <cstdint>
#include <iostream>
#include <unordered_map>

using namespace std;
class Solution {
public:
  string minWindow(string s, string t) {
    // Variable length sliding window type problem
    // Invariant: Window is valid within s if it contains all characters from t
    //
    // Idea:
    // Keep track of the characters needed from t within a map char -> count of chars missing
    // Then keep track of how many chars are needed to get all chars from t

    unordered_map<char, int> need;
    for (char c : t) {
      need[c]++;
    }

    int missing = t.size();
    int bestLen = INT32_MAX;
    int bestStart = 0;

    int left = 0;

    for (int right = 0; right < s.size(); right++) {
      char in = s[right];

      // Keep track of invariant
      if (need[in] > 0) {
        missing--;
      }
      need[in]--;

      // While valid window
      while (missing == 0) {
        int len = right - left + 1;
        if (len < bestLen) {
          bestLen = len;
          bestStart = left;
        }

        char out = s[left];
        need[out]++;
        if (need[out] > 0) {
          missing++;
        }
        left++;
      }
    }

    return bestLen == INT32_MAX ? "" : s.substr(bestStart, bestLen);
  }
};

int main() {
  Solution solution;

  {
    // The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string expected = "BANC";
    std::cout << "Input:    " << s << ", " << t << '\n';
    auto ans = solution.minWindow(s, t);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // The entire string s is the minimum window.
    string s = "a";
    string t = "a";
    string expected = "a";
    std::cout << "Input:    " << s << ", " << t << '\n';
    auto ans = solution.minWindow(s, t);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // Both 'a's from t must be included in the window. Since the largest window of s only has one 'a', return empty string.
    string s = "a";
    string t = "aa";
    string expected = "";
    std::cout << "Input:    " << s << ", " << t << '\n';
    auto ans = solution.minWindow(s, t);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
