// Rotting Oranges
// Difficulty: Medium
//
// You are given an m x n grid where each cell can have one of three values: 0 representing
// an empty cell, 1 representing a fresh orange, or 2 representing a rotten orange. Every
// minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes
// rotten. Return the minimum number of minutes that must elapse until no cell has a fresh
// orange. If this is impossible, return -1.

#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int orangesRotting(vector<vector<int>> &grid) {
    // This is multisite BFS where each rotten orange is a starting point
    // and each step in the search corresponds to one minute.

    int rows = grid.size();
    int cols = grid[0].size();

    int fresh = 0;
    queue<pair<int, int>> rotten;
    // Find all the rotten/fresh oranges
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (grid[r][c] == 2) {
          rotten.push({r, c});
        } else if (grid[r][c] == 1) {
          fresh++;
        }
      }
    }

    int minutes = 0;
    vector<pair<int, int>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!rotten.empty() && fresh > 0) {
      int numRotten = rotten.size();

      // Mark fresh oranges rotten around rotten ones
      for (int i = 0; i < numRotten; i++) {
        auto [r, c] = rotten.front();
        rotten.pop();

        for (auto [dr, dc] : dirs) {
          int nr = r + dr;
          int nc = c + dc;

          if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
            // Out of bounds
            continue;
          }

          // Is there a fresh one?
          if (grid[nr][nc] != 1) {
            continue;
          }

          // Mark it rotten and push it
          grid[nr][nc] = 2;
          fresh--;
          rotten.push({nr, nc});
        }
      }

      minutes++;
    }
    return fresh == 0 ? minutes : -1;
  }
};

int main() {
  Solution solution;

  {
    vector<vector<int>> grid = vector<vector<int>>{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    int expected = 4;
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.orangesRotting(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
    vector<vector<int>> grid = vector<vector<int>>{{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    int expected = -1;
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.orangesRotting(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // Since there are already no fresh oranges at minute 0, the answer is just 0.
    vector<vector<int>> grid = vector<vector<int>>{{0, 2}};
    int expected = 0;
    std::cout << "Input:    " << str(grid) << '\n';
    auto ans = solution.orangesRotting(grid);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
