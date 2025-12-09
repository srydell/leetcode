#include "helpers.hpp"

#include <iostream>
#include <utility>

using namespace std;
class Solution {
public:
  // Create a base board nxn like
  // n = 2:
  // board = {{..}, {..}};
  //
  // backtrack by placing a queen, keeping track of how many queens placed
  // if placing a queen, block the row, column and diagonal that queen is
  // attacking with e.g. '-'.
  // If reaching the end (row, column) without placing n queens -> discard
  // if reaching the end with n queens -> add to output

  vector<string> buildBaseBoard(int n) {
    vector<string> board;
    for (int i = 0; i < n; i++) {
      string row(n, '.');
      board.push_back(row);
    }
    return board;
  }

  void placeQueen(int row, int column, vector<string> &board) {
    for (int i = 0; i < board.size(); i++) {
      // Block the column/row
      board[row][i] = '-';
      board[i][column] = '-';

      // Block the diagonal down right/left
      if (row + i < board.size()) {
        if (column + i < board[row + i].size()) {
          board[row + i][column + i] = '-';
        }
        if (column - i >= 0) {
          board[row + i][column - i] = '-';
        }
      }

      // Bloci the diagonal up right/left
      if (row - i >= 0) {
        if (column + i < board[row - i].size()) {
          board[row - i][column + i] = '-';
        }
        if (column - i >= 0) {
          board[row - i][column - i] = '-';
        }
      }
    }
    board[row][column] = 'Q';
  }

  std::pair<int, int> getNext(int row, int column, int n) {
    column++;
    column %= n;
    if (column == 0) {
      row++;
    }
    return {row, column};
  }

  void finalizeBoard(vector<string> &board) {
    for (auto &row : board) {
      for (int i = 0; i < row.size(); i++) {
        if (row[i] == '-') {
          row[i] = '.';
        }
      }
    }
  }

  void buildQueens(int row, int column, int queensPlaced, int n,
                   vector<string> board, vector<vector<string>> &validBoards) {
    if (row > queensPlaced) {
      // Failed branch
      return;
    }
    // Are we done?
    if (row == n - 1 && column == n - 1) {
      // Last spot
      // Should we bother to place the last queen?
      if (board[row][column] != '-') {
        board[row][column] = 'Q';
        queensPlaced++;
      }

      if (queensPlaced == n) {
        finalizeBoard(board);
        validBoards.push_back(board);
      }
      return;
    }

    // Choose not to place a queen
    auto [nextRow, nextColumn] = getNext(row, column, n);
    buildQueens(nextRow, nextColumn, queensPlaced, n, board, validBoards);

    // Can we place a queen here?
    if (board[row][column] != '-') {
      placeQueen(row, column, board);
      queensPlaced++;
      buildQueens(nextRow, nextColumn, queensPlaced, n, board, validBoards);
    }
  }

  vector<vector<string>> solveNQueens(int n) {

    auto board = buildBaseBoard(n);
    vector<vector<string>> validBoards;
    buildQueens(0, 0, 0, n, board, validBoards);

    return validBoards;
  }
};

int main() {
  Solution solution;
  bool newline = true;
  {
    int n = 4;
    vector<vector<string>> expected = {{".Q..", "...Q", "Q...", "..Q."},
                                       {"..Q.", "Q...", "...Q", ".Q.."}};
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.solveNQueens(n);
    std::cout << "Got:      \n" << str(ans, newline) << '\n';
    std::cout << "Expected: \n" << str(expected, newline) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    int n = 1;
    vector<vector<string>> expected = {{"Q"}};
    std::cout << "Input:    " << n << '\n';
    auto ans = solution.solveNQueens(n);
    std::cout << "Got:      \n" << str(ans, newline) << '\n';
    std::cout << "Expected: \n" << str(expected, newline) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
