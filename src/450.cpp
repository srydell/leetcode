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

class Solution {
public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    if (root) {
      if (key < root->val) {
        root->left = deleteNode(root->left, key);
      } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
      } else {
        if (!root->left && !root->right) {
          return nullptr;
        }
        if (!root->left || !root->right) {
          return root->left ? root->left : root->right;
        }
        TreeNode *temp = root->left;
        while (temp->right != nullptr) {
          temp = temp->right;
        }
        root->val = temp->val;
        root->left = deleteNode(root->left, temp->val);
      }
    }
    return root;
  }
};

int main() {
  Solution solution;
  optional<int> null = nullopt;

  {
    TreeNode *root = create(vector<optional<int>>{5, 3, 6, 2, 4, null, 7});
    int key = 5;
    std::cout << "Input:    " << str(root) << ", " << key << '\n';
    auto ans = solution.deleteNode(root, key);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: "
              << str(create(vector<optional<int>>{6, 3, 7, 2, 4})) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{0});
    int key = 0;
    std::cout << "Input:    " << str(root) << ", " << key << '\n';
    auto ans = solution.deleteNode(root, key);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: " << str(create(vector<optional<int>>{})) << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{5, 3, 6, 2, 4, null, 7});
    int key = 3;
    std::cout << "Input:    " << str(root) << ", " << key << '\n';
    auto ans = solution.deleteNode(root, key);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: "
              << str(create(vector<optional<int>>{5, 4, 6, 2, null, null, 7}))
              << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{5, 3, 6, 2, 4, null, 7});
    int key = 0;
    std::cout << "Input:    " << str(root) << ", " << key << '\n';
    auto ans = solution.deleteNode(root, key);
    std::cout << "Got:      " << str(ans) << '\n';
    std::cout << "Expected: "
              << str(create(vector<optional<int>>{5, 3, 6, 2, 4, null, 7}))
              << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
