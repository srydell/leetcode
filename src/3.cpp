#include "helpers.hpp"

#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    if (s.empty()) {
      return 0;
    }
    int left = 0;
    int currentLen = 1;
    int maxLen = 1;
    std::unordered_map<char, bool> currentWindow;
    currentWindow[s[0]] = true;

    for (int right = 1; right < s.size(); right++) {
      // Found a duplicate to the right -> push left border
      if (currentWindow[s[right]]) {
        while (s[left] != s[right]) {
          currentWindow[s[left]] = false;
          left++;
          currentLen--;
        }
        // Remove the previous occurrence of s[right]
        left++;
        currentLen--;
      }

      // Now include s[right]
      currentWindow[s[right]] = true;
      currentLen++;
      maxLen = max(maxLen, currentLen);
    }
    return maxLen;
  }
};

int main() {
  Solution solution;

  {
    // The answer is "abc", with the length of 3. Note that "bca" and "cab" are
    // also correct answers.
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
    // The answer is "wke", with the length of 3. Notice that the answer must be
    // a substring, "pwke" is a subsequence and not a substring.
    string s = "pwwkew";
    int expected = 3;
    std::cout << "Input:    " << s << '\n';
    auto ans = solution.lengthOfLongestSubstring(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
