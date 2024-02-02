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
  int longest = 0;
  void takePath(TreeNode *root, bool isLeft, int step) {
    if (!root) {
      return;
    }
    longest = max(longest, step);

    if (isLeft) {
      takePath(root->left, false, step + 1);
      takePath(root->right, true, 1);
    } else {
      takePath(root->right, true, step + 1);
      takePath(root->left, false, 1);
    }
  }
  int longestZigZag(TreeNode *root) {

    takePath(root, true, 0);
    takePath(root, false, 0);

    return longest;
  }
};

int main() {
  Solution solution;
  optional<int> null = nullopt;

  {
    TreeNode *root = create(vector<optional<int>>{1, 1, 1, 1, null, null, 1});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.longestZigZag(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 1 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{
        1, null, 1, 1, 1, null, null, 1, 1, null, 1, null, null, null, 1});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.longestZigZag(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(
        vector<optional<int>>{1, 1, 1, null, 1, null, null, 1, 1, null, 1});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.longestZigZag(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 4 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{1});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.longestZigZag(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 0 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
