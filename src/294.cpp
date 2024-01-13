#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  void decodeSubstring(stack<char> &chars) {
    string content = "";
    int32_t number = 1;
    while (chars.top() != '[') {
      content.push_back(chars.top());
      chars.pop();
    }
    std::ranges::reverse(content);

    // Remove '['
    chars.pop();

    string num = "";
    while (!chars.empty() && std::isdigit(chars.top())) {
      num.push_back(chars.top());
      chars.pop();
    }

    if (!num.empty()) {
      std::ranges::reverse(num);
      number = std::stoi(num);
    }

    string final_content = "";
    for (int32_t i = 0; i < number; i++) {
      final_content += content;
    }

    for (auto c : final_content) {
      chars.push(c);
    }
  }

  string decodeString(string s) {
    if (s.size() == 1) {
      return s;
    }

    std::stack<char> chars;
    for (size_t i = 0; i < s.size(); i++) {
      if (s[i] == ']') {
        decodeSubstring(chars);
        continue;
      }
      chars.push(s[i]);
    }

    string out;
    while (!chars.empty()) {
      out.push_back(chars.top());
      chars.pop();
    }
    std::ranges::reverse(out);
    return out;
  }
};

int main() {
  Solution solution;

  {
    string s = "3[z]2[2[y]pq4[2[jk]e1[f]]]ef";
    auto ans = solution.decodeString(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: "
              << "zzzyypqjkjkefjkjkefjkjkefjkjkefyypqjkjkefjkjkefjkjkefjkjkefef"
              << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string s = "3[a]2[bc]";
    auto ans = solution.decodeString(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: "
              << "aaabcbc" << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string s = "3[a2[c]]";
    auto ans = solution.decodeString(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: "
              << "accaccacc" << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string s = "2[abc]3[cd]ef";
    auto ans = solution.decodeString(s);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: "
              << "abcabccdcdcdef" << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
