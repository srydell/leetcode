#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
  // The idea is to solve subproblems and build up to the solution of the main
  // problem.
  //
  // E.g. build this matrix
  //
  //      |  a  |  b  |  c  |  d  |  e  | ""
  //   a  |  0  |  0  |  0  |  0  |  0  | 0
  //   c  |  0  |  0  |  0  |  0  |  0  | 0
  //   e  |  0  |  0  |  0  |  0  |  0  | 0
  //  ""  |  0  |  0  |  0  |  0  |  0  | 0
  //
  //  The bottom right corner is simply the lcs between "e" and "e"
  //  Go up one step to get the lcs between "ce" and "e"
  //  Go left one step to get the lcs between "e" and "de"
  //  Diagonally up left to get the lcs between "ce" and "de"
  //  What we want is the upper left corner, i.e. the lcs between the whole two
  //  strings We can calculate the subproblem of the rest of the grid to get
  //  there. Two insights:
  //    1. If the two characters text1[i] and text2[j] matches
  //       -> to get the rest of the lcs length we can
  //          add 1 (the match) and
  //          remove both of those characters (i.e. move down right diagonally)
  //    2. If the two characters text1[i] and text2[j] does not match
  //       -> to get the rest of the match we can either remove text1[i] (move
  //       right)
  //          or remove text2[j] (move left) and take the max of these (the best
  //          option)
  int longestCommonSubsequence(std::string text1, string text2) {
    std::vector<std::vector<int>> lcs(text1.size() + 1,
                                      std::vector<int>(text2.size() + 1, 0));

    for (int i = text1.size() - 1; i >= 0; i--) {
      for (int j = text2.size() - 1; j >= 0; j--) {
        if (text1[i] == text2[j]) {
          // Match! What did we get when removing both?
          lcs[i][j] = 1 + lcs[i + 1][j + 1];
        } else {
          // No match. What was the best we got by removing one of the
          // characters?
          lcs[i][j] = std::max(lcs[i + 1][j], lcs[i][j + 1]);
        }
      }
    }

    return lcs[0][0];
  }
};

int main() {
  Solution solution;

  {
    string text1 = "abcde", text2 = "ace";
    int expected = 3;
    std::cout << "Input:    " << text1 << ", " << text2 << '\n';
    auto ans = solution.longestCommonSubsequence(text1, text2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string text1 = "abc", text2 = "abc";
    int expected = 3;
    std::cout << "Input:    " << text1 << ", " << text2 << '\n';
    auto ans = solution.longestCommonSubsequence(text1, text2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string text1 = "abc", text2 = "def";
    int expected = 0;
    std::cout << "Input:    " << text1 << ", " << text2 << '\n';
    auto ans = solution.longestCommonSubsequence(text1, text2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
