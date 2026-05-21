#include "helpers.hpp"

#include <iostream>

using namespace std;
class Solution {
public:
  int minDepth(TreeNode *root) { return 1; }
};

int main() {
  Solution solution;

  {
    TreeNode *root =
        create(vector<optional<int>>{3, 9, 20, nullopt, nullopt, 15, 7});
    int expected = 2;
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.minDepth(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{2, nullopt, 3, nullopt, 4,
                                                  nullopt, 5, nullopt, 6});
    int expected = 5;
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.minDepth(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
