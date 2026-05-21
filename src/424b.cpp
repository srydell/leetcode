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
    // Sliding variable size window problem.
    // Invariant: Can I make this window one repeated character with k changes?
    // Idea: Keep track of the number of letters for each type in the current
    // window. Change all of the letters within that window to the most frequent
    // one. I.e. size(window) - count_of_most_frequenc_letter <= k All letters
    // are uppercase
    // (=> 26 letters)

    array<int, 26> count{};
    int left = 0;
    int best = 0;
    int maxFreq = 0;

    for (int right = 0; right < s.size(); right++) {
      // Map this character to its frequency
      int r = s[right] - 'A';
      count[r]++;
      // Note: r is the only possible new max freq
      maxFreq = max(maxFreq, count[r]);

      while (right - left + 1 - maxFreq > k) {
        int removed_letter = s[left] - 'A';
        count[removed_letter]--;
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
