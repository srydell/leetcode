#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Map the words to a vector of occurrences
// v[0] = 3 means there are 3 'a' in the word
pair<vector<int>, vector<int>> createMap(map<char, int> &freq1,
                                         map<char, int> &freq2) {
  vector<int> w1(26, 0);
  vector<int> w2(26, 0);
  size_t counter = 0;
  std::string s = "abcdefghijklmnopqrstuvwxyz";
  for (char c : s) {
    w1[counter] = freq1[c];
    w2[counter] = freq2[c];
    counter++;
  }
  return {w1, w2};
}

class Solution {
public:
  bool closeStrings(string word1, string word2) {
    if (word1.size() != word2.size()) {
      return false;
    }

    // { 'i': 3, 'k': 1 }
    map<char, int> freq1;
    map<char, int> freq2;
    for (size_t i = 0; i < word1.size(); i++) {
      freq1[word1[i]]++;
      freq2[word2[i]]++;
    }

    for (auto const [c, _] : freq1) {
      if (!freq2.contains(c)) {
        return false;
      }
    }

    auto [w1, w2] = createMap(freq1, freq2);

    // Since we can switch around any letter,
    // the only requirement is that there is enough letters to swap one to the
    // other i.e. there are three 'a' and three 'e' in the two words
    sort(w1.begin(), w1.end());
    sort(w2.begin(), w2.end());
    for (size_t i = 0; i < w1.size(); i++) {
      if (w1[i] != w2[i]) {
        return false;
      }
    }

    return true;
  }
};

int main() {
  Solution solution;

  {
    string word1 = "abc";
    string word2 = "bca";
    auto ans = solution.closeStrings(word1, word2);
    std::cout << ans << '\n';
    std::cout << "Expected: " << true << '\n';
  }

  {
    string word1 = "a";
    string word2 = "aa";
    auto ans = solution.closeStrings(word1, word2);
    std::cout << ans << '\n';
    std::cout << "Expected: " << false << '\n';
  }

  {
    string word1 = "cabbba";
    string word2 = "abbccc";
    auto ans = solution.closeStrings(word1, word2);
    std::cout << ans << '\n';
    std::cout << "Expected: " << true << '\n';
  }
}
