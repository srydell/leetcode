#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Solution {
  public:
      int maxOperations(vector<int>& nums, int k) {
        return 0;
      }
};

struct TestCase {
      vector<int> nums;
      int k;
      int answer;
};

int main() {
  Solution s;

  for (TestCase test : std::vector<TestCase>{TestCase{{1, 2, 3, 4}, 5, 2},
                                             TestCase{{3, 1, 3, 4, 3}, 6, 1}}) {
    std::cout << "Test: " << '\n';
    std::cout << s.maxOperations(test.nums, test.k) << " = " << test.answer
              << '\n';
  }
}
