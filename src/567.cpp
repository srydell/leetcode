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
    if (s1.size() > s2.size()) {
      return false;
    }

    unordered_map<char, int> freq;

    for (char c : s1) {
      freq[c]++;
    }

    // Fixed size window of size s1
    // Invariant: The window contains all of the letters in s1
    // Initialize to see which letters are missing
    int left = 0;
    for (int i = 0; i < s1.size(); i++) {
      char c = s2[i];
      freq[c]--;
      if (freq[c] == 0) {
        freq.erase(c);
      }
    }
    if (freq.empty()) {
      return true;
    }

    for (int right = s1.size(); right < s2.size(); right++) {
      char leftC = s2[left];
      char rightC = s2[right];

      // Remove outgoing char from window
      freq[leftC]++;
      if (freq[leftC] == 0) {
        freq.erase(leftC);
      }

      // Add incoming char to window
      freq[rightC]--;
      if (freq[rightC] == 0) {
        freq.erase(rightC);
      }

      left++;

      // Are we done?
      if (freq.empty()) {
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
