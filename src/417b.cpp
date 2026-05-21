// Pacific Atlantic Water Flow
// Difficulty: Medium
//
// There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic
// Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean
// touches the island's right and bottom edges. The island is partitioned into a grid of
// square cells. You are given an m x n integer matrix heights where heights[r][c]
// represents the height above sea level of the cell at coordinate (r, c). The island
// receives a lot of rain, and the rain water can flow to neighboring cells directly north,
// south, east, and west if the neighboring cell's height is less than or equal to the
// current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.
// Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain
// water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.

#include "helpers.hpp"

#include <iostream>
#include <vector>

using namespace std;
class Solution {
  void bfs(vector<pair<int, int>> &starts, vector<vector<bool>> &reach, vector<vector<int>> &heights) {
    vector<vector<bool>> seen(heights.size(), vector<bool>(heights[0].size(), false));

    vector<pair<int, int>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto [sr, sc] : starts) {
      queue<pair<int, int>> nodes;
      nodes.push({sr, sc});
      seen[sr][sc] = true;
      reach[sr][sc] = true;

      while (!nodes.empty()) {
        auto [r, c] = nodes.front();
        nodes.pop();

        // Go in every direction
        for (auto [dr, dc] : dirs) {
          int nr = dr + r;
          int nc = dc + c;

          if (nr < 0 || nr >= heights.size() || nc < 0 || nc >= heights[0].size()) {
            continue;
          }
          if (seen[nr][nc]) {
            continue;
          }
          if (heights[r][c] > heights[nr][nc]) {
            continue;
          }

          reach[nr][nc] = true;
          seen[nr][nc] = true;
          nodes.push({nr, nc});
        }
      }
    }
  }

public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
    // Search from the coastline inwards going up/same heigth. Compare where you can reach from both atlantic/pacific and return those.
    //

    vector<vector<bool>> pac(heights.size(), vector<bool>(heights[0].size(), false));
    vector<vector<bool>> atl(heights.size(), vector<bool>(heights[0].size(), false));

    // Generate starting cells
    vector<pair<int, int>> pac_start;
    vector<pair<int, int>> atl_start;
    for (int r = 0; r < heights.size(); r++) {
      pac_start.push_back({r, 0});
      atl_start.push_back({r, heights[0].size() - 1});
    }

    for (int c = 0; c < heights[0].size(); c++) {
      pac_start.push_back({0, c});
      atl_start.push_back({heights.size() - 1, c});
    }

    bfs(pac_start, pac, heights);
    bfs(atl_start, atl, heights);

    vector<vector<int>> answer;
    for (int r = 0; r < pac.size(); r++) {
      for (int c = 0; c < pac[0].size(); c++) {
        if (pac[r][c] && atl[r][c]) {
          answer.push_back({r, c});
        }
      }
    }
    return answer;
  }
};

int main() {
  Solution solution;

  {
    // The following cells can flow to the Pacific and Atlantic oceans, as shown below: [0,4]: [0,4] -> Pacific Ocean [0,4] -> Atlantic Ocean [1,3]: [1,3] -> [0,3] -> Pacific Ocean [1,3] -> [1,4] -> Atlantic Ocean [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean [1,4] -> Atlantic Ocean [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean [3,0]: [3,0] -> Pacific Ocean [3,0] -> [4,0] -> Atlantic Ocean [3,1]: [3,1] -> [3,0] -> Pacific Ocean [3,1] -> [4,1] -> Atlantic Ocean [4,0]: [4,0] -> Pacific Ocean [4,0] -> Atlantic Ocean Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
    vector<vector<int>> heights = vector<vector<int>>{{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}};
    vector<vector<int>> expected = vector<vector<int>>{{0, 4}, {1, 3}, {1, 4}, {2, 2}, {3, 0}, {3, 1}, {4, 0}};
    std::cout << "Input:    " << str(heights) << '\n';
    auto ans = solution.pacificAtlantic(heights);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    // The water can flow from the only cell to the Pacific and Atlantic oceans.
    vector<vector<int>> heights = vector<vector<int>>{{1}};
    vector<vector<int>> expected = vector<vector<int>>{{0, 0}};
    std::cout << "Input:    " << str(heights) << '\n';
    auto ans = solution.pacificAtlantic(heights);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
