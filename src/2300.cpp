
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Solution {
public:
  std::vector<int> successfulPairs(std::vector<int> &spells,
                                   std::vector<int> &potions,
                                   long long success) {

    std::vector<int> out = std::vector<int>(spells.size(), 0);
    std::sort(potions.begin(), potions.end());
    for (size_t i = 0; i < spells.size(); i++) {
      // Calculate the minimum potion required for the current spell
      // to achieve the success threshold
      // success <= spells[i] * potions[j] for any j
      // => potions[j] >= success / spells[i]
      long long minPotion = (success + spells[i] - 1) / spells[i];
      auto it = std::lower_bound(potions.begin(), potions.end(), minPotion);
      out[i] = static_cast<int>(potions.end() - it);
    }

    return out;
  }
};

template <typename T> std::string str(std::vector<T> const &v) {
  std::stringstream ss;
  ss << '[';
  for (size_t i = 0; i < v.size(); i++) {
    ss << v[i];
    if (i < v.size() - 1) {
      ss << ", ";
    }
  }
  ss << ']';
  return ss.str();
}

int main() {
  Solution solution;

  {
    std::vector<int> spells = {5, 1, 3};
    std::vector<int> potions = {1, 2, 3, 4, 5};
    long long success = 7;
    std::cout << "Input:" << '\n';
    std::cout << "spells = " << str(spells) << '\n';
    std::cout << "potions = " << str(potions) << '\n';
    std::cout << "success = " << success << '\n';
    auto ans = solution.successfulPairs(spells, potions, success);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(std::vector<int>{4, 0, 3}) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
  {
    std::vector<int> spells = {3, 1, 2};
    std::vector<int> potions = {8, 5, 8};
    long long success = 16;
    std::cout << "Input:" << '\n';
    std::cout << "spells = " << str(spells) << '\n';
    std::cout << "potions = " << str(potions) << '\n';
    std::cout << "success = " << success << '\n';
    auto ans = solution.successfulPairs(spells, potions, success);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(std::vector<int>{2, 0, 2}) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
