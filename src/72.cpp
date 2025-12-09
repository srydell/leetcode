#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

std::string str(std::vector<int> const &v) {
  std::stringstream ss;
  ss << '[';
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    ss << v[i];
    if (i < v.size() - 1) {
      ss << ", ";
    }
  }
  ss << ']';
  return ss.str();
}

std::string str(vector<vector<int>> const &v) {
  std::stringstream ss;
  ss << '[';
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    ss << str(v[i]) << '\n';
    if (i < v.size() - 1) {
      ss << ", ";
    }
  }
  ss << ']';
  return ss.str();
}

class Solution {
public:
  // The brute force idea is simple:
  //
  // For each letter in word1 we try to make it the same as the corresponding
  // letter in word2.
  //
  // If they are the same, do nothing
  // If they are not we can
  //   1. add the letter from word2 into word1
  //   2. delete the letter from word1
  //   3. replace the letter from word1 to the one from word2
  //
  // Each of these operations will lead to a new subproblem caused by the choice
  // E.g. removing a letter not matching causes a new 'easier' subproblem
  // Brute force is simply exploring all possible ways to convert the two words
  // into each other, minimizing the the distance.
  //
  // This should smell like a dynamic programming problem, so lets look at a
  // matrix
  //
  //
  // word1 = acd
  // word2 = abd
  //
  //    | a | b | d | ''
  // a  |   |   |   |
  // c  |   |   |   |
  // d  |   |   |   |
  // '' |   |   |   |
  //
  // Let the value in the top left corner be the minDistance(acd, abd) which is
  // what we are looking for Moving right means shortening word2 to
  // minDistance(acd, bd) etc. In the last column/row we have the empty string
  // representing our base cases when the strings are empty. They are easy to
  // fill out since minDistance('', '') = 0, minDistance('', word) =
  // minDistance(word, '') = word.size() or:
  //
  //    | a | b | d | ''
  // a  |   |   |   | 3
  // c  |   |   |   | 2
  // d  |   |   |   | 1
  // '' | 3 | 2 | 1 | 0
  //
  // We want to know the best way to get to the upper left corner, so lets look
  // at the operations
  //
  // If the letters in the matrix are the same, move on to the next letter:
  // word1[i] == word2[j] => No operations needed, (i, j) => (i + 1, j + 1)
  //
  // If adding a letter, we now matched the letter from word2 => move word2
  // index forward 1 operation done, (i, j) => (i, j + 1)
  //
  // If removing a letter, essentially just move the word1 index forward
  // 1 operation done, (i, j) => (i + 1, j)
  //
  // If replacing a letter, the letters now match and we can increase both
  // indices 1 operation done, (i, j) => (i + 1, j + 1)
  //
  // Start at the bottom right, look at the ways to get there, i.e. right, down,
  // diagonally right take the best option (minimum of the values) and if the
  // current letters do not match, add one.
  int minDistance(std::string word1, string word2) {
    std::vector<std::vector<int>> distances(
        word1.size() + 1,
        std::vector<int>(word2.size() + 1, std::numeric_limits<int>::max()));

    // The edges
    for (int i = 0; i < word1.size() + 1; i++) {
      distances[i][word2.size()] = word1.size() - i;
    }
    for (int j = 0; j < word2.size() + 1; j++) {
      distances[word1.size()][j] = word2.size() - j;
    }

    for (int i = word1.size() - 1; i >= 0; i--) {
      for (int j = word2.size() - 1; j >= 0; j--) {
        if (word1[i] == word2[j]) {
          // The same => just carry the previous min distance
          distances[i][j] = distances[i + 1][j + 1];
        } else {
          // Best operation to get here?
          int adding = distances[i][j + 1];
          int removing = distances[i + 1][j];
          int replacing = distances[i + 1][j + 1];
          distances[i][j] = 1 + std::min(adding, std::min(removing, replacing));
        }
      }
    }

    return distances[0][0];
  }
};

int main() {
  Solution solution;

  {
    string word1 = "horse", word2 = "ros";
    int expected = 3;
    std::cout << "Input:    " << word1 << ", " << word2 << '\n';
    auto ans = solution.minDistance(word1, word2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string word1 = "intention", word2 = "execution";
    int expected = 5;
    std::cout << "Input:    " << word1 << ", " << word2 << '\n';
    auto ans = solution.minDistance(word1, word2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    string word1 = "a", word2 = "aa";
    int expected = 1;
    std::cout << "Input:    " << word1 << ", " << word2 << '\n';
    auto ans = solution.minDistance(word1, word2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
