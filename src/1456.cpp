#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  bool isVowel(char c) {
    static constexpr array<char, 5> vowels = {'a', 'e', 'i', 'o', 'u'};

    return find(vowels.begin(), vowels.end(), c) != vowels.end();
  }

  int maxVowels(string s, int k) {

    size_t start = 0;
    size_t end = start + static_cast<size_t>(k) - 1;

    int vowels =
        accumulate(s.begin(), s.begin() + k, 0, [this](int sofar, char c) {
          sofar += isVowel(c) ? 1 : 0;
          return sofar;
        });
    int maxVowels = vowels;

    for (start++, end++; end < s.size(); start++, end++) {
      // Remove back
      vowels -= isVowel(s[start - 1]) ? 1 : 0;
      // Add front
      vowels += isVowel(s[end]) ? 1 : 0;
      maxVowels = max(maxVowels, vowels);
    }
    return maxVowels;
  }
};

int main() {
  Solution solution;
  {
    string s = "abciiidef";
    int k = 3;
    auto ans = solution.maxVowels(s, k);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
  }

  {
    string s = "aeiou";
    int k = 2;
    auto ans = solution.maxVowels(s, k);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 2 << '\n';
  }

  {
    string s = "leetcode";
    int k = 3;
    auto ans = solution.maxVowels(s, k);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 2 << '\n';
  }
}
