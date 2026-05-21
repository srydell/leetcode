#include "helpers.hpp"

#include <iostream>
#include <tuple>

using namespace std;
class Solution {
public:
  bool is_overlapping(int s0, int e0, int s1, int e1) {
    // Assumes s0 <= s1
    return s1 >= s0 && s1 <= e0;
  }

  vector<vector<int>> merge(vector<vector<int>> &intervals) {

    // The easiest I can think of is to just take one interval. On the next
    // interval, check whether there is overlap, if there is, merge them, if
    // there is not, add it.
    //
    // I should probably keep a sorted track on the starts and ends of each
    // interval

    sort(intervals.begin(), intervals.end());
    std::cout << str(intervals) << '\n';

    vector<vector<int>> merged;
    int start = intervals[0][0];
    int end = intervals[0][1];

    for (int i = 1; i < intervals.size(); i++) {
      int s = intervals[i][0];
      int e = intervals[i][1];

      if (s <= end) {
        end = max(end, e);
      } else {
        merged.push_back({start, end});
        start = s;
        end = e;
      }
    }

    merged.push_back({start, end});
    return merged;
  }
};

int main() {
  Solution solution;

  {
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> expected = {{1, 6}, {8, 10}, {15, 18}};
    std::cout << "Input:    " << str(intervals) << '\n';
    auto ans = solution.merge(intervals);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> intervals = {{1, 4}, {4, 5}};
    vector<vector<int>> expected = {{1, 5}};
    std::cout << "Input:    " << str(intervals) << '\n';
    auto ans = solution.merge(intervals);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<vector<int>> intervals = {{4, 7}, {1, 4}};
    vector<vector<int>> expected = {{1, 7}};
    std::cout << "Input:    " << str(intervals) << '\n';
    auto ans = solution.merge(intervals);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
