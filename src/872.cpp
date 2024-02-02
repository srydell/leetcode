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
  vector<int> getLeaves(TreeNode *root) {
    if (!root) {
      return {};
    }
    vector<int> leaves;

    stack<TreeNode *> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
      auto current = nodes.top();
      nodes.pop();

      bool isLeaf = true;
      if (current->left) {
        isLeaf = false;
        nodes.push(current->left);
      }
      if (current->right) {
        isLeaf = false;
        nodes.push(current->right);
      }

      if (isLeaf) {
        leaves.push_back(current->val);
      }
    }
    return leaves;
  }

  bool leafSimilar(TreeNode *root1, TreeNode *root2) {
    return getLeaves(root1) == getLeaves(root2);
  }
};

int main() {
  Solution solution;

  optional<int> null = nullopt;

  {
    TreeNode *root1 =
        create(vector<optional<int>>{3, 5, 1, 6, 2, 9, 8, null, null, 7, 4});
    TreeNode *root2 = create(vector<optional<int>>{
        3, 5, 1, 6, 7, 4, 2, null, null, null, null, null, null, 9, 8});
    std::cout << "Input:    " << str(root1) << '\n';
    std::cout << "Input:    " << str(root2) << '\n';
    auto ans = solution.leafSimilar(root1, root2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << true << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root1 = create(vector<optional<int>>{1, 2, 3});
    TreeNode *root2 = create(vector<optional<int>>{1, 3, 2});
    std::cout << "Input:    " << str(root1) << '\n';
    std::cout << "Input:    " << str(root2) << '\n';
    auto ans = solution.leafSimilar(root1, root2);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << false << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
