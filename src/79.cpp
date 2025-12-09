#include "helpers.hpp"

#include <iostream>
#include <set>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
class Solution {
public:
  std::vector<std::pair<int, int>>
  getSiblings(int row, int column, vector<vector<char>> const &board) {
    std::vector<std::pair<int, int>> siblings;

    // Up
    if (row > 0) {
      siblings.push_back({row - 1, column});
    }
    // down
    if (row + 1 < board.size()) {
      siblings.push_back({row + 1, column});
    }
    // right
    if (column + 1 < board[row].size()) {
      siblings.push_back({row, column + 1});
    }
    // left
    if (column > 0) {
      siblings.push_back({row, column - 1});
    }

    return siblings;
  }

  struct State {
    int row;
    int column;
    int i;
    std::set<std::pair<int, int>> visited;
  };

  void print(State state) {
    std::cout << "(" << state.row << ", " << state.column << "), i=" << state.i
              << '\n';
  }

  bool find(int row, int column, string const &word,
            vector<vector<char>> const &board) {
    std::stack<State> states;
    states.push(State{.row = row, .column = column, .i = 0});

    while (!states.empty()) {
      auto state = states.top();
      states.pop();
      // print(state);

      if (board[state.row][state.column] == word[state.i]) {
        if (state.i + 1 == word.size()) {
          return true;
        }

        // Keep on searching
        state.visited.insert({state.row, state.column});
        for (auto [nextRow, nextCol] :
             getSiblings(state.row, state.column, board)) {
          if (!state.visited.contains({nextRow, nextCol})) {
            states.push(State{.row = nextRow,
                              .column = nextCol,
                              .i = state.i + 1,
                              .visited = state.visited});
          }
        }
      }
    }

    return false;
  }

  bool exist(vector<vector<char>> &board, string word) {
    for (int row = 0; row < board.size(); row++) {
      for (int col = 0; col < board[0].size(); col++) {
        if (board[row][col] == word[0] && find(row, col, word, board)) {
          return true;
        }
      }
    }
    return false;
  }
};

int main() {

  {
    Solution solution;
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "ABCCED";
    bool expected = true;
    std::cout << "Input:    " << word << ", " << str(board) << '\n';
    auto ans = solution.exist(board, word);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "SEE";
    bool expected = true;
    std::cout << "Input:    " << word << ", " << str(board) << '\n';
    auto ans = solution.exist(board, word);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "ABCB";
    bool expected = false;
    std::cout << "Input:    " << word << ", " << str(board) << '\n';
    auto ans = solution.exist(board, word);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    Solution solution;
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'E', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "ABCESEEEFS";
    bool expected = true;
    std::cout << "Input:    " << word << ", " << str(board) << '\n';
    auto ans = solution.exist(board, word);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
