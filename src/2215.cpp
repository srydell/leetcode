#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T> string str(vector<T> const &v) {
  std::stringstream ss;
  ss << '[';
  for (size_t i = 0; i < v.size(); i++) {
    ss << v[i];
    if (i < v.size() - 1) {
      ss << ", ";
    }
  }
  ss << ']';
  return ss.str();
}

class Solution {
public:
  vector<vector<int>> findDifference(vector<int> &nums1, vector<int> &nums2) {
    set<int> m1(nums1.begin(), nums1.end());
    set<int> m2(nums2.begin(), nums2.end());
    vector<int> uniq1 = {};
    vector<int> uniq2 = {};
    for (auto e : m1) {
      if (!m2.contains(e)) {
        uniq1.push_back(e);
      }
    }
    for (auto e : m2) {
      if (!m1.contains(e)) {
        uniq2.push_back(e);
      }
    }
    return {uniq1, uniq2};
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums1 = {1, 2, 3};
    vector<int> nums2 = {2, 4, 6};
    auto ans = solution.findDifference(nums1, nums2);
    std::cout << '[' << str(ans[0]) << ", " << str(ans[1]) << ']' << '\n';
    std::cout << "Expected: [[1,3],[4,6]]" << '\n';
  }

  {
    vector<int> nums1 = {1, 2, 3, 3};
    vector<int> nums2 = {1, 1, 2, 2};
    auto ans = solution.findDifference(nums1, nums2);
    std::cout << '[' << str(ans[0]) << ", " << str(ans[1]) << ']' << '\n';
    std::cout << "Expected: [[3], []]" << '\n';
  }
}
