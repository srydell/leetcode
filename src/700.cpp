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
  TreeNode *searchBST(TreeNode *root, int val) {
    if (!root) {
      return nullptr;
    }

    while (root) {
      if (root->val < val) {
        root = root->right;
      } else if (root->val > val) {
        root = root->left;
      } else {
        return root;
      }
    }
    return root;
  }
};

int main() {
  Solution solution;

  {
    std::cout << "Input:    " << 0 << '\n';
    auto ans = solution.searchBST();
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 0 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
