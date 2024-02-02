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
  int explore(size_t i, set<int> &visited, vector<vector<int>> &connections) {
    if (!visited.insert(static_cast<int>(i)).second) {
      return 0;
    }

    queue<int> islandsToVisit;
    for (size_t island = 0; island < connections[i].size(); island++) {
      if (connections[i][island] == 1 && island != i) {
        islandsToVisit.push(static_cast<int>(island));
      }
    }

    while (!islandsToVisit.empty()) {
      auto island = islandsToVisit.front();
      islandsToVisit.pop();

      for (size_t nextIsland = 0;
           nextIsland < connections[static_cast<size_t>(island)].size();
           nextIsland++) {
        int temp = static_cast<int>(nextIsland);
        if (connections[static_cast<size_t>(island)][nextIsland] == 1 &&
            visited.insert(temp).second) {
          islandsToVisit.push(temp);
        }
      }
    }
    return 1;
  }

  int findCircleNum(vector<vector<int>> &isConnected) {
    if (isConnected.size() == 1) {
      return 1;
    }
    set<int> visited;
    int numIslands = 0;
    for (size_t i = 0; i < isConnected.size(); i++) {
      numIslands += explore(i, visited, isConnected);
    }
    return numIslands;
  }
};

int main() {
  Solution solution;

  {
    vector<vector<int>> isConnected = {
        {1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 1, 1}};
    std::cout << "Input:    " << str(isConnected) << '\n';
    auto ans = solution.findCircleNum(isConnected);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 1 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> isConnected = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    std::cout << "Input:    " << str(isConnected) << '\n';
    auto ans = solution.findCircleNum(isConnected);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 2 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> isConnected = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    std::cout << "Input:    " << str(isConnected) << '\n';
    auto ans = solution.findCircleNum(isConnected);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
