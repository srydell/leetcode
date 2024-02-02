#include <algorithm>
#include <cmath>
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
    ss << ']';
    return ss.str();
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

template <typename T> string str(vector<T> const &v) {
  std::stringstream ss;
  ss << '[';
  for (size_t i = 0; i < v.size(); i++) {
    ss << v[i];
    if (i < v.size() - 1) {
      ss << ", ";
    }
  }
  ss << ']';
  return ss.str();
}

class Solution {
public:
  vector<int> rightSideView(TreeNode *root) {
    if (!root) {
      return {};
    }

    queue<pair<TreeNode *, size_t>> nodes;
    nodes.push({root, 0});
    vector<int> out;
    while (!nodes.empty()) {
      auto [current, level] = nodes.front();
      nodes.pop();
      if (level < out.size()) {
        out[level] = current->val;
      } else {
        out.push_back(current->val);
      }

      if (current->left) {
        nodes.push({current->left, level + 1});
      }

      if (current->right) {
        nodes.push({current->right, level + 1});
      }
    }

    return out;
  }
};

int main() {
  Solution solution;
  optional<int> null = nullopt;

  {
    TreeNode *root = create(vector<optional<int>>{1, null, 3});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.rightSideView(root);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector<int>{1, 3}) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{1, 2, 3, null, 5, null, 4});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.rightSideView(root);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector<int>{1, 3, 4}) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.rightSideView(root);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(vector<int>{}) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
