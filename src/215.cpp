#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) {
    make_heap(nums.begin(), nums.end());
    int largest = -1;
    for (int i = 0; i < k; i++) {
      pop_heap(nums.begin(), nums.end());
      largest = nums.back();
      nums.pop_back();
    }
    return largest;
  }
};

int main() {
  Solution solution;

  {
    vector<int> v = {3, 2, 1, 5, 6, 4};
    auto ans = solution.findKthLargest(v, 2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 5 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
