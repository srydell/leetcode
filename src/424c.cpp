// Longest Repeating Character Replacement
// Difficulty: Medium
//
// You are given a string s and an integer k. You can choose any character of
// the string and change it to any other uppercase English character. You can
// perform this operation at most k times. Return the length of the longest
// substring containing the same letter you can get after performing the above
// operations.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int characterReplacement(string s, int k) {
    // Note: All characters uppercase => 26 letters
    // Want: size(window) longest substring of one char after k changes
    // Invariant: Each window should have at most k changes to be one char. I.e.
    // size(window) - freq(char to change to) <= k freq(char to change to)
    // should be the most frequent char within the window. Idea: Keep track of
    // the number of each char within the window.
    array<int, 26> count{};
    int left = 0;
    int best = 0;
    int maxFreq = 0;

    for (int right = 0; right < s.size(); right++) {
      int in = s[right] - 'A';
      count[in]++;

      maxFreq = max(maxFreq, count[in]);

      while (right - left + 1 - maxFreq > k) {
        // Remove left char
        int out = s[left] - 'A';
        count[out]--;
        left++;
      }

      best = max(best, right - left + 1);
    }
    return best;
  }
};

int main() {
  Solution solution;

  {
    // Replace the two 'A's with two 'B's or vice versa.
    string s = "ABAB";
    int k = 2;
    int expected = 4;
    std::cout << "Input:    " << s << ", " << k << '\n';
    auto ans = solution.characterReplacement(s, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // Replace the one 'A' in the middle with 'B' and form "AABBBBA". The
    // substring "BBBB" has the longest repeating letters, which is 4. There may
    // exists other ways to achieve this answer too.
    string s = "AABABBA";
    int k = 1;
    int expected = 4;
    std::cout << "Input:    " << s << ", " << k << '\n';
    auto ans = solution.characterReplacement(s, k);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
