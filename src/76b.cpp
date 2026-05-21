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
    // Variable sliding window style problem.
    // A window is valid within s if it contains every character of t including duplicates.
    // This means we should keep track of the number of characters found so far within s in e.g. a map.
    // Call this map need, then
    // need[c] == 0  => all chars of type c is found
    // need[c] < 0  => surplus number of type c
    // need[c] > 0  => need more characters of type c
    //
    unordered_map<char, int> need;
    for (int i = 0; i < t.size(); i++) {
      need[t[i]]++;
    }

    // Keep track of the best length/start found so far
    int bestLen = INT32_MAX;
    int bestStart = 0;

    // Missing number of characters
    int missing = t.size();

    int left = 0;

    for (int right = 0; right < s.size(); right++) {
      char in = s[right];

      // Keep track of the characters from t
      if (need[in] > 0) {
        missing--;
      }
      need[in]--;

      // Do we have a valid window?
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
