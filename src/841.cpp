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
  bool canVisitAllRooms(vector<vector<int>> &rooms) {
    set<int> visitedRooms;
    visitedRooms.insert(0);
    queue<int> keys;
    for (auto key : rooms[0]) {
      keys.push(key);
    }

    while (!keys.empty()) {
      auto key = keys.front();
      keys.pop();

      if (visitedRooms.insert(key).second) {
        // Collect the keys from that room
        for (auto k : rooms[static_cast<size_t>(key)]) {
          keys.push(k);
        }
      }
    }

    return visitedRooms.size() == rooms.size();
  }
};

int main() {
  Solution solution;

  {
    vector<vector<int>> rooms = {{1}, {2}, {3}, {}};
    std::cout << "Input:    " << str(rooms) << '\n';
    auto ans = solution.canVisitAllRooms(rooms);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << true << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> rooms = {{1, 3}, {3, 0, 1}, {2}, {0}};
    std::cout << "Input:    " << str(rooms) << '\n';
    auto ans = solution.canVisitAllRooms(rooms);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << true << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
