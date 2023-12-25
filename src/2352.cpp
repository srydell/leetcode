#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int equalPairs(vector<vector<int>> &grid) {
    int pairs = 0;
    vector<vector<int>> transposed = grid;
    size_t n = grid.size();
    for (size_t row = 0; row < n; row++) {
      for (size_t col = 0; col < n; col++) {
        transposed[col][row] = grid[row][col];
      }
    }

    for (size_t row = 0; row < n; row++) {
      for (size_t col = 0; col < n; col++) {
        if (grid[row] == transposed[col]) {
          pairs++;
        }
      }
    }

    return pairs;
  }
};

int main() {
  Solution solution;

  {
    vector<vector<int>> grid = {{3, 2, 1}, {1, 7, 6}, {2, 7, 7}};
    auto ans = solution.equalPairs(grid);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 1 << '\n';
  }

  {
    vector<vector<int>> grid = {
        {3, 1, 2, 2}, {1, 4, 4, 5}, {2, 4, 2, 2}, {2, 4, 2, 2}};
    auto ans = solution.equalPairs(grid);
    std::cout << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
  }
}
