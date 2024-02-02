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

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

TreeNode *create(vector<optional<int>> const &v) {
  if (v.empty() || !v[0].has_value()) {
    return nullptr;
  }
  TreeNode *root = new TreeNode(v[0].value());
  std::queue<TreeNode *> nodes;
  nodes.push(root);
  size_t i = 1;
  while (i < v.size()) {
    TreeNode *current = nodes.front();
    nodes.pop();
    if (i < v.size()) {
      if (v[i]) {
        current->left = new TreeNode(v[i].value());
        nodes.push(current->left);
      }
      i++;
    }
    if (i < v.size()) {
      if (v[i]) {
        current->right = new TreeNode(v[i].value());
        nodes.push(current->right);
      }
      i++;
    }
  }
  return root;
}

std::string str(TreeNode const *root) {
  std::stringstream ss;
  ss << '[';
  if (!root) {
    ss << "null";
  }

  std::queue<TreeNode const *> nodes;
  nodes.push(root);
  while (!nodes.empty()) {
    auto current = nodes.front();
    nodes.pop();

    ss << current->val << ", ";
    if (current->left) {
      nodes.push(current->left);
    } else {
      ss << "null, ";
    }

    if (current->right) {
      nodes.push(current->right);
    } else {
      ss << "null, ";
    }
  }
  string out = ss.str();
  if (out.back() == ' ') {
    // Remove ", "
    out.pop_back();
    out.pop_back();
  }

  out.push_back(']');
  return out;
}

class Solution {
public:
  int pathSum(TreeNode *root, int targetSum) {
    if (!root) {
      return 0;
    }

    stack<pair<TreeNode const *, vector<int64_t>>> nodes;
    nodes.push({root, {}});
    int numPaths = 0;

    while (!nodes.empty()) {
      auto [current, paths] = nodes.top();
      nodes.pop();

      for (auto &path : paths) {
        path += current->val;
        if (path == targetSum) {
          numPaths++;
        }
      }

      // Start a new path
      paths.push_back(current->val);
      numPaths += current->val == targetSum ? 1 : 0;

      if (current->left) {
        nodes.push({current->left, paths});
      }
      if (current->right) {
        nodes.push({current->right, paths});
      }
    }

    return numPaths;
  }
};

int main() {
  Solution solution;
  optional<int> null = nullopt;

  {
    TreeNode *root = create(
        vector<optional<int>>{10, 5, -3, 3, 2, null, 11, 3, -2, null, 1});
    int targetSum = 8;
    std::cout << "Input:    " << str(root) << ", " << targetSum << '\n';
    auto ans = solution.pathSum(root, targetSum);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{5, 4, 8, 11, null, 13, 4, 7,
                                                  2, null, null, 5, 1});
    int targetSum = 22;
    std::cout << "Input:    " << str(root) << ", " << targetSum << '\n';
    auto ans = solution.pathSum(root, targetSum);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
