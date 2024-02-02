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
  int goodNodes(TreeNode *root) {
    if (!root) {
      return 0;
    }

    int good = 0;
    stack<pair<TreeNode const *, int>> nodes;
    nodes.push({root, numeric_limits<int>::min()});

    while (!nodes.empty()) {
      auto [current, maxValueAbove] = nodes.top();
      nodes.pop();

      if (current->val >= maxValueAbove) {
        good++;
        maxValueAbove = max(current->val, maxValueAbove);
      }

      if (current->left) {
        nodes.push({current->left, maxValueAbove});
      }
      if (current->right) {
        nodes.push({current->right, maxValueAbove});
      }
    }

    return good;
  }
};

int main() {
  Solution solution;

  optional<int> null = nullopt;
  {
    TreeNode *root = create(vector<optional<int>>{3, 1, 4, 3, null, 1, 5});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.goodNodes(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 4 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{3, 3, null, 4, 2});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.goodNodes(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 3 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{1});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.goodNodes(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 1 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
