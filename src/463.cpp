// Island Perimeter
// Difficulty: Easy
//
// You are given row x col grid representing a map where grid[i][j] = 1 represents land and
// grid[i][j] = 0 represents water. Grid cells are connected horizontally/vertically (not
// diagonally). The grid is completely surrounded by water, and there is exactly one island
// (i.e., one or more connected land cells). The island doesn't have "lakes", meaning the
// water inside isn't connected to the water around the island. One cell is a square with
// side length 1. The grid is rectangular, width and height don't exceed 100. Determine the
// perimeter of the island.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
  int countPerimeter(vector<vector<int>> &grid, int sr, int sc) {
    queue<pair<int, int>> land;
    int perimeter = 0;
    grid[sr][sc] = 2;
    land.push({sr, sc});

    vector<pair<int, int>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    while (!land.empty()) {
      auto [r, c] = land.front();
      land.pop();

      for (auto [dr, dc] : dirs) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size()) {
          perimeter++;
          continue;
        }

        if (grid[nr][nc] == 0) {
          perimeter++;
          continue;
        } else if (grid[nr][nc] == 1) {
          grid[nr][nc] = 2;
          land.push({nr, nc});
        }
      }
    }
    return perimeter;
  }

public:
  int islandPerimeter(vector<vector<int>> &grid) {
    for (int r = 0; r < grid.size(); r++) {
      for (int c = 0; c < grid[0].size(); c++) {
        if (grid[r][c] == 1) {
          return countPerimeter(grid, r, c);
        }
      }
    }
    return 0;
  }
};

int main() {
  Solution solution;

  {
    // The perimeter is the 16 yellow stripes in the image above.
    vector<vector<int>> grid = vector<vector<int>>{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
    int expected = 16;
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.islandPerimeter(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> grid = vector<vector<int>>{{1}};
    int expected = 4;
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.islandPerimeter(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> grid = vector<vector<int>>{{1, 0}};
    int expected = 4;
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.islandPerimeter(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
