// Find All Anagrams in a String
// Difficulty: Medium
//
// Given two strings s and p, return an array of all the start indices of p's
// anagrams in s. You may return the answer in any order.

#include "helpers.hpp"

#include <iostream>
#include <unordered_map>

using namespace std;
class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    // Fixed window problem
    // p should be contained within s
    // Invariant:
    //   sizeof(window in s) == sizeof(p)
    //   All letters of p should be within the window of s

    if (s.size() < p.size()) {
      return {};
    }

    // Keep track of the missing letters within the current window
    // {char -> number of that char that is missing}
    unordered_map<char, int> missing;
    for (int i = 0; i < p.size(); i++) {
      missing[p[i]]++;
      if (missing[p[i]] == 0) {
        missing.erase(p[i]);
      }

      missing[s[i]]--;
      if (missing[s[i]] == 0) {
        missing.erase(s[i]);
      }
    }

    vector<int> indices;
    if (missing.empty()) {
      indices.push_back(0);
    }

    int left = 0;
    for (int right = p.size(); right < s.size(); right++) {
      char in = s[right];
      char out = s[left];
      left++;

      missing[in]--;
      if (missing[in] == 0) {
        missing.erase(in);
      }

      missing[out]++;
      if (missing[out] == 0) {
        missing.erase(out);
      }

      if (missing.empty()) {
        indices.push_back(left);
      }
    }
    return indices;
  }
};

int main() {
  Solution solution;

  {
    // The substring with start index = 0 is "cba", which is an anagram of
    // "abc". The substring with start index = 6 is "bac", which is an anagram
    // of "abc".
    string s = "cbaebabacd";
    string p = "abc";
    vector<int> expected = vector<int>{0, 6};
    std::cout << "Input:    " << s << ", " << p << '\n';
    auto ans = solution.findAnagrams(s, p);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // The substring with start index = 0 is "ab", which is an anagram of "ab".
    // The substring with start index = 1 is "ba", which is an anagram of "ab".
    // The substring with start index = 2 is "ab", which is an anagram of "ab".
    string s = "abab";
    string p = "ab";
    vector<int> expected = vector<int>{0, 1, 2};
    std::cout << "Input:    " << s << ", " << p << '\n';
    auto ans = solution.findAnagrams(s, p);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
