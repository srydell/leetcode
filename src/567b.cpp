// Permutation in String
// Difficulty: Medium
//
// Given two strings s1 and s2, return true if s2 contains a permutation of s1,
// or false otherwise. In other words, return true if one of s1's permutations
// is the substring of s2.

#include "helpers.hpp"

#include <iostream>
#include <unordered_map>

using namespace std;
class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    // The idea is to keep a constant window of s1's charachters
    // The invariant: Does the window within s2 contain all of s1's characters
    if (s1.size() > s2.size()) {
      return false;
    }

    // missing letters within the current window
    // {character -> how many are missing}
    unordered_map<char, int> missing;
    for (int i = 0; i < s1.size(); i++) {
      missing[s1[i]]++;
      if (missing[s1[i]] == 0) {
        missing.erase(s1[i]);
      }
      missing[s2[i]]--;
      if (missing[s2[i]] == 0) {
        missing.erase(s2[i]);
      }
    }

    if (missing.empty()) {
      return true;
    }

    int left = 0;
    for (int right = s1.size(); right < s2.size(); right++) {
      char in = s2[right];
      char out = s2[left];
      left++;

      // Push in
      missing[in]--;
      if (missing[in] == 0) {
        missing.erase(in);
      }

      // Pop out
      missing[out]++;
      if (missing[out] == 0) {
        missing.erase(out);
      }

      if (missing.empty()) {
        return true;
      }
    }
    return false;
  }
};

int main() {
  Solution solution;

  {
    // s2 contains one permutation of s1 ("ba").
    string s1 = "ab";
    string s2 = "eidbaooo";
    bool expected = true;
    std::cout << "Input:    " << s1 << ", " << s2 << '\n';
    auto ans = solution.checkInclusion(s1, s2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string s1 = "ab";
    string s2 = "eidboaoo";
    bool expected = false;
    std::cout << "Input:    " << s1 << ", " << s2 << '\n';
    auto ans = solution.checkInclusion(s1, s2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
