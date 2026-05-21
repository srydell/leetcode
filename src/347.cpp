#include "helpers.hpp"

#include <functional>
#include <iostream>
#include <unordered_map>

using namespace std;
class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> frequency;
    for (auto n : nums) {
      frequency[n]++;
    }

    vector<pair<int, int>> sorted;
    for (auto [n, f] : frequency) {
      sorted.push_back({f, n});
    }
    sort(sorted.begin(), sorted.end(), std::greater<>());

    vector<int> out;

    for (int i = 0; i < k; i++) {
      out.push_back(sorted[i].second);
    }
    return out;
  }
};

int main() {
  Solution solution;

  {
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;
    vector<int> expected = {1, 2};
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.topKFrequent(nums, k);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {1};
    int k = 1;
    vector<int> expected = {1};
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.topKFrequent(nums, k);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    vector<int> nums = {1, 2, 1, 2, 1, 2, 3, 1, 3, 2};
    int k = 2;
    vector<int> expected = {1, 2};
    std::cout << "Input:    " << str(nums) << ", " << k << '\n';
    auto ans = solution.topKFrequent(nums, k);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(expected) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
