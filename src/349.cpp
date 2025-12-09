#include "helpers.hpp"

#include <iostream>
#include <map>

using namespace std;
class Solution {
public:
  vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
    std::map<int, bool> m;
    for (auto num : nums1) {
      m[num] = false;
    }

    vector<int> out;
    for (auto num : nums2) {
      if (m.contains(num) && !m[num]) {
        m[num] = true;
        out.push_back(num);
      }
    }
    return out;
  }
};

int main() {

  {
    Solution solution;
    vector<int> nums1 = {1, 2, 2, 1};
    vector<int> nums2 = {2, 2};
    vector<int> expected = {2};
    std::cout << "Input:    " << str(nums1) << ", " << str(nums2) << '\n';
    auto ans = solution.intersection(nums1, nums2);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
