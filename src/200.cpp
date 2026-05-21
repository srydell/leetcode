// Number of Islands
// Difficulty: Medium
//
// Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's
// (water), return the number of islands. An island is surrounded by water and is formed by
// connecting adjacent lands horizontally or vertically. You may assume all four edges of
// the grid are all surrounded by water.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
  void exploreIsland(vector<vector<char>> &grid, int i, int j) {
    queue<pair<int, int>> nodes;
    nodes.push({i, j});
    grid[i][j] = '2'; // Means visited

    while (!nodes.empty()) {
      auto [x, y] = nodes.front();
      nodes.pop();

      // Left
      if (x > 0 && grid[x - 1][y] == '1') {
        grid[x - 1][y] = '2';
        nodes.push({x - 1, y});
      }
      // Right
      if (x + 1 < grid.size() && grid[x + 1][y] == '1') {
        grid[x + 1][y] = '2';
        nodes.push({x + 1, y});
      }

      // Up
      if (y > 0 && grid[x][y - 1] == '1') {
        grid[x][y - 1] = '2';
        nodes.push({x, y - 1});
      }
      // Down
      if (y + 1 < grid[0].size() && grid[x][y + 1] == '1') {
        grid[x][y + 1] = '2';
        nodes.push({x, y + 1});
      }
    }
  }

public:
  int numIslands(vector<vector<char>> &grid) {
    // A piece of land is connected to another piece of land if they are neighbors.
    // Go through the grid, when a piece of land is found, search through it and keep track of the
    // indices already mapped to an island.
    int islands = 0;

    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[0].size(); j++) {
        if (grid[i][j] == '1') {
          exploreIsland(grid, i, j);
          islands++;
        }
      }
    }
    return islands;
  }
};

int main() {
  Solution solution;

  {
    vector<vector<char>> grid = vector<vector<char>>{{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}};
    int expected = 1;
    std::cout << "Input:    " << str(grid, true) << '\n';
    auto ans = solution.numIslands(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<char>> grid = vector<vector<char>>{{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};
    int expected = 3;
    std::cout << "Input:    " << str(grid, true) << '\n';
    auto ans = solution.numIslands(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
