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

using namespace std;
class Solution {
  void pourWaterOn(int sr, int sc, vector<vector<int>> &heights, vector<vector<int>> &visited) {
    // Need to explore where this water can go

    vector<pair<int, int>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    vector<vector<bool>> local_visited(heights.size(), vector<bool>(heights[0].size(), false));
    queue<pair<int, int>> nodes;
    nodes.push({sr, sc});
    local_visited[sr][sc] = true;

    // The visited cluster
    vector<pair<int, int>> current;
    current.push_back({sr, sc});
    bool pacificReached = false;
    bool atlanticReached = false;
    while (!nodes.empty()) {
      auto [r, c] = nodes.front();
      nodes.pop();

      for (auto [dr, dc] : dirs) {
        int nr = dr + r;
        int nc = dc + c;

        if (nc < 0 || nr < 0) {
          // pacific (north west) reached
          pacificReached = true;
          continue;
        }

        if (nr >= heights.size() || nc >= heights[0].size()) {
          // atlantic (south east) reached
          atlanticReached = true;
          continue;
        }

        if (local_visited[nr][nc]) {
          continue;
        }

        int is_visited = visited[nr][nc];
        if (is_visited == 1) {
          pacificReached = true;
          continue;
        } else if (is_visited == 2) {
          atlanticReached = true;
          continue;
        } else if (is_visited == 3) {
          pacificReached = true;
          atlanticReached = true;
          continue;
        } else if (is_visited != 0) {
          continue;
        }

        if (heights[r][c] < heights[nr][nc]) {
          continue;
        }

        nodes.push({nr, nc});
        local_visited[nr][nc] = true;
        current.push_back({nr, nc});
      }
    }

    int status = -1;
    if (pacificReached && atlanticReached) {
      status = 3;
    } else if (pacificReached) {
      status = 1;
    } else if (atlanticReached) {
      status = 2;
    }
    for (auto [r, c] : current) {
      visited[r][c] = status;
    }
  }

public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
    // Seems like a multisource bfs type of problem.
    // Need to mark each square if it's possible to go to any ocean.

    // -1 stuck in a well
    // 0 represents unvisited
    // 1 can go to pacific (north,west)
    // 2 can go to atlantic (south,east)
    // 3 can go to both
    vector<vector<int>> visited(heights.size(), vector<int>(heights[0].size(), 0));

    for (int r = 0; r < heights.size(); r++) {
      for (int c = 0; c < heights[0].size(); c++) {
        if (visited[r][c] == 0) {
          pourWaterOn(r, c, heights, visited);
        }
      }
    }
    std::cout << str(visited, true) << '\n';
    vector<vector<int>> answer;
    for (int r = 0; r < visited.size(); r++) {
      for (int c = 0; c < visited[0].size(); c++) {
        if (visited[r][c] == 3) {
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
