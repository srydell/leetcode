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
  using pos = pair<size_t, size_t>;
  vector<vector<int>> &m_grid;

  std::vector<pos> getNeighbours(size_t x, size_t y) {
    std::vector<pos> neighbours = {};
    if (x > 0) {
      if (isOrange(x - 1, y)) {
        neighbours.push_back({x - 1, y});
      }
    }
    if (x < m_grid.size() - 1) {
      if (isOrange(x + 1, y)) {
        neighbours.push_back({x + 1, y});
      }
    }
    if (y > 0) {
      if (isOrange(x, y - 1)) {
        neighbours.push_back({x, y - 1});
      }
    }
    if (y < m_grid[0].size() - 1) {
      if (isOrange(x, y + 1)) {
        neighbours.push_back({x, y + 1});
      }
    }
    return neighbours;
  }

  bool isOrange(size_t x, size_t y) { return m_grid[x][y] > 0; }

  size_t s(int i) { return static_cast<size_t>(i); }

  int calculateTimeToDie(vector<pos> const &cluster, set<pos> &rotten) {
    int timeToDie = 0;
    while (true) {
      if (cluster.size() == rotten.size()) {
        return timeToDie;
      }
      vector<pos> toAdd = {};
      for (auto [x, y] : rotten) {
        for (auto [xn, yn] : getNeighbours(x, y)) {
          if (!rotten.contains({xn, yn})) {
            toAdd.push_back({xn, yn});
          }
        }
      }

      for (auto element : toAdd) {
        rotten.insert(element);
      }
      timeToDie++;
    }
  }

  int traverseGrid(int ix, int iy, set<pos> &visited) {
    queue<pos> q;
    q.push({ix, iy});
    bool oneRotten = false;
    vector<pos> cluster;
    set<pos> rotten;
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      if (!visited.insert({x, y}).second) {
        continue;
      }

      int orange = m_grid[x][y];
      if (orange == 2) {
        oneRotten = true;
        rotten.insert({x, y});
      }
      cluster.push_back({x, y});

      for (auto [xn, yn] : getNeighbours(x, y)) {
        q.push({xn, yn});
      }
    }

    if (!oneRotten) {
      return -1;
    }

    return calculateTimeToDie(cluster, rotten);
  }

  int orangesRotting(vector<vector<int>> &grid) {
    m_grid = grid;
    if (m_grid.empty()) {
      return 0;
    } else if (m_grid[0].empty()) {
      return 0;
    }

    int maxTimeToDie = 0;
    set<pair<size_t, size_t>> visited = {};
    for (size_t x = 0; x < grid.size(); x++) {
      for (size_t y = 0; y < grid[0].size(); y++) {
        // Never seen before
        if (auto orange = grid[x][y]; orange > 0) {
          if (visited.contains({x, y})) {
            continue;
          }
          // New cluster of oranges
          auto timeToDie =
              traverseGrid(static_cast<int>(x), static_cast<int>(y), visited);
          if (timeToDie == -1) {
            return -1;
          }
          maxTimeToDie = max(maxTimeToDie, timeToDie);
        }
      }
    }

    return maxTimeToDie;
  }
};

int main() {

  {
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    Solution solution(grid);
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.orangesRotting(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 4 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> grid = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    Solution solution(grid);
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.orangesRotting(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << -1 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> grid = {{0, 2}};
    Solution solution(grid);
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.orangesRotting(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 0 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
