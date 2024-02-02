#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

string str(vector<int> const &v) {
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

string str(vector<vector<int>> const &v) {
  std::stringstream ss;
  ss << '[';
  for (size_t i = 0; i < v.size(); i++) {
    ss << str(v[i]);
    if (i < v.size() - 1) {
      ss << ", ";
    }
  }
  ss << ']';
  return ss.str();
}

class Solution {
public:
  int minReorder(int n, vector<vector<int>> &connections) {}
};

int main() {
  Solution solution;

  {
    vector<vector<int>> connections = {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}};
    int n = 6;
    std::cout << "Input:    " << n << ", " << str(connections) << '\n';
    auto ans = solution.minReorder(n, connections);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> connections = {{1, 0}, {1, 2}, {3, 2}, {3, 4}};
    int n = 5;
    std::cout << "Input:    " << n << ", " << str(connections) << '\n';
    auto ans = solution.minReorder(n, connections);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 2 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> connections = {{1, 0}, {2, 0}};
    int n = 3;
    std::cout << "Input:    " << n << ", " << str(connections) << '\n';
    auto ans = solution.minReorder(n, connections);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 0 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
