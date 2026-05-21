// Max Area of Island
// Difficulty: Medium
//
// You are given an m x n binary matrix grid. An island is a group of 1's (representing
// land) connected 4-directionally (horizontal or vertical.) You may assume all four edges
// of the grid are surrounded by water. The area of an island is the number of cells with a
// value 1 in the island. Return the maximum area of an island in grid. If there is no
// island, return 0.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
  int getAreaOfIsland(vector<vector<int>> &grid, int sr, int sc) {
    int area = 1;
    grid[sr][sc] = 2;
    queue<pair<int, int>> indices;
    indices.push({sr, sc});

    while (!indices.empty()) {
      auto [r, c] = indices.front();
      indices.pop();

      // Up
      if (r - 1 >= 0 && grid[r - 1][c] == 1) {
        area++;
        grid[r - 1][c] = 2;
        indices.push({r - 1, c});
      }

      // Down
      if (r + 1 < grid.size() && grid[r + 1][c] == 1) {
        area++;
        grid[r + 1][c] = 2;
        indices.push({r + 1, c});
      }

      // Left
      if (c - 1 >= 0 && grid[r][c - 1] == 1) {
        area++;
        grid[r][c - 1] = 2;
        indices.push({r, c - 1});
      }

      // Right
      if (c + 1 < grid[0].size() && grid[r][c + 1] == 1) {
        area++;
        grid[r][c + 1] = 2;
        indices.push({r, c + 1});
      }
    }
    return area;
  }

public:
  int maxAreaOfIsland(vector<vector<int>> &grid) {
    int maxArea = 0;

    for (int r = 0; r < grid.size(); r++) {
      for (int c = 0; c < grid[0].size(); c++) {
        if (grid[r][c] == 1) {
          maxArea = max(maxArea, getAreaOfIsland(grid, r, c));
        }
      }
    }
    return maxArea;
  }
};

int main() {
  Solution solution;

  {
    // The answer is not 11, because the island must be connected 4-directionally.
    vector<vector<int>> grid = vector<vector<int>>{{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0}, {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
    int expected = 6;
    std::cout << "Input:    " << str(grid, true) << '\n';
    auto ans = solution.maxAreaOfIsland(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> grid = vector<vector<int>>{{0, 0, 0, 0, 0, 0, 0, 0}};
    int expected = 0;
    std::cout << "Input:    " << str(grid, true) << '\n';
    auto ans = solution.maxAreaOfIsland(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
