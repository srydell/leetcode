// Longest Substring Without Repeating Characters
// Difficulty: Medium
//
// Given a string s, find the length of the longest substring without duplicate characters.

#include "helpers.hpp"

#include <iostream>
#include <unordered_map>

using namespace std;
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    // Variable lenght sliding window type problem
    // Invariant: a valid window has only unique characters
    // Idea: Keep track of the number of each character within a unordered_set<char>

    if (s.empty()) {
      return 0;
    }

    int left = 0;
    unordered_set<char> chars;
    int best = 0;
    for (int right = 0; right < s.size(); right++) {
      char in = s[right];
      while (chars.contains(in)) {
        chars.erase(s[left]);
        left++;
      }
      chars.insert(s[right]);
      best = max(best, right - left + 1);
    }
    return best;
  }
};

int main() {
  Solution solution;

  {
    // The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
    string s = "abcabcbb";
    int expected = 3;
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.lengthOfLongestSubstring(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // The answer is "b", with the length of 1.
    string s = "bbbbb";
    int expected = 1;
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.lengthOfLongestSubstring(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // The answer is "wke", with the length of 3. Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
    string s = "pwwkew";
    int expected = 3;
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.lengthOfLongestSubstring(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
