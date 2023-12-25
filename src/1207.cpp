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

class Solution {
public:
  bool uniqueOccurrences(vector<int> &arr) {
    map<int, int> m;
    for (auto e : arr) {
      m[e]++;
    }
    set<int> s;
    for (auto [key, value] : m) {
      if (auto const &[_, hasInserted] = s.insert(value); !hasInserted) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  Solution solution;

  {
    vector<int> arr = {1, 2, 2, 1, 1, 3};
    auto ans = solution.uniqueOccurrences(arr);
    std::cout << ans << '\n';
    std::cout << "Expected: " << true << '\n';
  }

  {
    vector<int> arr = {1, 2};
    auto ans = solution.uniqueOccurrences(arr);
    std::cout << ans << '\n';
    std::cout << "Expected: " << false << '\n';
  }

  {
    vector<int> arr = {-3, 0, 1, -3, 1, 1, 1, -3, 10, 0};
    auto ans = solution.uniqueOccurrences(arr);
    std::cout << ans << '\n';
    std::cout << "Expected: " << true << '\n';
  }

  {
    vector<int> arr = {3, 5, -2, -3, -6, -6};
    auto ans = solution.uniqueOccurrences(arr);
    std::cout << ans << '\n';
    std::cout << "Expected: " << false << '\n';
  }
}
