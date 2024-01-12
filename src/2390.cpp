#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  string removeStars(string s) {
    stack<char> letters;

    for (char c : s) {
      if (c == '*') {
        letters.pop();
      } else {
        letters.push(c);
      }
    }

    string out;
    while (!letters.empty()) {
      out.push_back(letters.top());
      letters.pop();
    }
    reverse(out.begin(), out.end());
    return out;
  }
};

int main() {
  Solution solution;

  {
    string s = "leet**cod*e";
    auto ans = solution.removeStars(s);
    std::cout << ans << '\n';
    std::cout << "Expected: "
              << "lecoe" << '\n';
  }

  {
    string s = "erase*****";
    auto ans = solution.removeStars(s);
    std::cout << ans << '\n';
    std::cout << "Expected: "
              << "" << '\n';
  }
}
