#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  // The idea is to backtrack
  //
  // Go through all the choices of ways to build the sums
  // and if you pass a threshold (i.e. sum > target, or we run out of
  // candidates) return.
  //
  // If you found a way to build a sum along the way, push it to a result vector
  void buildSums(int current, int sum, vector<int> choices,
                 vector<int> const &candidates, int target,
                 vector<vector<int>> &out) {
    if (sum == target) {
      out.push_back(choices);
      return;
    } else if (sum > target || current >= candidates.size()) {
      // Reject it
      return;
    }

    // Choose this candidate
    choices.push_back(candidates[current]);
    buildSums(current, sum + candidates[current], choices, candidates, target,
              out);

    // Move forward instead
    choices.pop_back();
    buildSums(current + 1, sum, choices, candidates, target, out);
  }

  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> out;
    buildSums(0, 0, {}, candidates, target, out);
    return out;
  }
};

int main() {
  Solution solution;

  {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> expected = {{2, 2, 3}, {7}};
    std::cout << "Input:    " << str(candidates) << ", " << target << '\n';
    auto ans = solution.combinationSum(candidates, target);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> candidates = {2, 3, 5};
    int target = 8;
    vector<vector<int>> expected = {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}};
    std::cout << "Input:    " << str(candidates) << ", " << target << '\n';
    auto ans = solution.combinationSum(candidates, target);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> candidates = {2};
    int target = 1;
    vector<vector<int>> expected = {};
    std::cout << "Input:    " << str(candidates) << ", " << target << '\n';
    auto ans = solution.combinationSum(candidates, target);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
