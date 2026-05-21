// Longest Repeating Character Replacement
// Difficulty: Medium
//
// You are given a string s and an integer k. You can choose any character of
// the string and change it to any other uppercase English character. You can
// perform this operation at most k times. Return the length of the longest
// substring containing the same letter you can get after performing the above
// operations.

#include "helpers.hpp"

#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;
class Solution {
public:
  int characterReplacement(string s, int k) {
    // Variable sliding window problem
    // There are only uppercase letters
    // A window is valid if it only contains the same letters
    // A window can have changed letters c <= k times.
    // State: c & letter containing & letter position changed
    // Idea: Move right pointer until there is a new type of letter. If we can
    // change it, do so and continue. If not, move the left pointer until we
    // can. Keep track of the length of the valid windows
    int best = 1;
    char current = s[0];
    int left = 0;
    std::deque<int> changed;

    for (int right = 1; right < s.size(); right++) {
      if (s[right] != current) {
        if (changed.size() < k) {
          // Change it!
          changed.push_back(right);
        } else {
          // No way to change it,
          // Move left pointer to latest change + 1
          // and change this one instead
          left = changed.front() + 1;
          changed.pop_front();
          changed.push_back(right);
        }
      }
      best = std::max(best, right - left + 1);
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
