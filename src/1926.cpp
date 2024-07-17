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

string str(vector<char> const &v) {
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

string str(vector<vector<char>> const &v) {
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
  set<pair<int, int>> visited;
  int x_max;
  int y_max;
  vector<vector<char>> m_maze;
  pair<int, int> start;

  bool canGo(int x, int y) {
    if (x == -1 || y == -1) {
      return false;
    }
    size_t xs = static_cast<size_t>(x);
    size_t ys = static_cast<size_t>(y);
    return x < x_max && y < y_max && m_maze[xs][ys] == '.' &&
           !visited.contains({x, y});
  }

  bool isExit(int x, int y) {
    if (pair{x, y} == start) {
      return false;
    }
    return x == 0 || y == 0 || x == x_max - 1 || y == y_max - 1;
  }

  int nearestExit(vector<vector<char>> &maze, vector<int> &entrance) {
    using P = pair<int, int>;
    x_max = static_cast<int>(maze.size());
    y_max = static_cast<int>(maze[0].size());
    m_maze = maze;

    queue<pair<int, P>> positions;
    start = {entrance[0], entrance[1]};
    visited.insert(start);
    positions.push({0, start});

    while (!positions.empty()) {
      auto [len, pos] = positions.front();
      auto [x, y] = pos;
      positions.pop();
      for (auto [new_x, new_y] :
           vector<P>{P{x + 1, y}, P{x - 1, y}, P{x, y + 1}, P{x, y - 1}}) {
        if (canGo(new_x, new_y)) {
          if (isExit(new_x, new_y)) {
            return len + 1;
          }
          visited.insert({new_x, new_y});
          positions.push({len + 1, {new_x, new_y}});
        }
      }
    }

    return -1;
  }
};

int main() {

  {
    Solution solution;
    vector<vector<char>> maze = {
        {'+', '+', '.', '+'}, {'.', '.', '.', '+'}, {'+', '+', '+', '.'}};
    vector<int> entrance{1, 2};
    std::cout << "Input:    " << str(maze) << ", " << str(entrance) << '\n';
    auto ans = solution.nearestExit(maze, entrance);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 1 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<vector<char>> maze = {
        {'+', '+', '+'}, {'.', '.', '.'}, {'+', '+', '+'}};
    vector<int> entrance{1, 0};
    std::cout << "Input:    " << str(maze) << ", " << str(entrance) << '\n';
    auto ans = solution.nearestExit(maze, entrance);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 2 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<vector<char>> maze = {{'.', '+'}};
    vector<int> entrance{0, 0};
    std::cout << "Input:    " << str(maze) << ", " << str(entrance) << '\n';
    auto ans = solution.nearestExit(maze, entrance);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << -1 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
