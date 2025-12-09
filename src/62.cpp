#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
  // The idea is:
  // Since the robot can only move right or down there are limited ways of how
  // to get to the end. Start thinking about the easiest grid possible where
  // there is only one square. Then there are 0 ways to reach the finish, the
  // robot is already there. For a 2x2 grid there are 2 ways to get there and so
  // on.
  //
  // In general (where i<m-1, j<n-1 is in the grid)
  //
  // grid[m-1][j] = 1 (can only go right)
  //
  // grid[i][n-1] = 1 (can only go down)
  //
  // grid[i][j] = grid[i+1][j] + grid[i][j+1] (summing ways to get there)
  int uniquePaths(int m, int n) {
    // Initialize grid
    std::vector<std::vector<int>> grid(m, std::vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
      // Can only go down
      grid[i][n - 1] = 1;
    }

    for (int j = 0; j < n; j++) {
      // Can only go right
      grid[m - 1][j] = 1;
    }

    for (int i = m - 2; i >= 0; i--) {
      for (int j = n - 2; j >= 0; j--) {
        // The robot can either go down or right from here
        // Sum their possible paths
        grid[i][j] = grid[i + 1][j] + grid[i][j + 1];
      }
    }
    return grid[0][0];
  }
};

int main() {
  Solution solution;

  {
    int m = 3, n = 7;
    int expected = 28;
    std::cout << "Input:    m = " << m << ", n = " << n << '\n';
    auto ans = solution.uniquePaths(m, n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int m = 3, n = 2;
    int expected = 3;
    std::cout << "Input:    m = " << m << ", n = " << n << '\n';
    auto ans = solution.uniquePaths(m, n);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
