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
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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
  map<TreeNode *, TreeNode *> childToParent;

  void populateMap(TreeNode *root, TreeNode *p, TreeNode *q) {
    stack<TreeNode *> nodes;
    nodes.push(root);

    bool foundP = false;
    bool foundQ = false;

    while (!nodes.empty()) {
      auto current = nodes.top();
      nodes.pop();

      if (!foundP && current == p) {
        foundP = true;
      }

      if (!foundQ && current == q) {
        foundQ = true;
      }

      if (foundP && foundQ) {
        break;
      }

      if (current->left) {
        childToParent[current->left] = current;
        nodes.push(current->left);
      }

      if (current->right) {
        childToParent[current->right] = current;
        nodes.push(current->right);
      }
    }
  }
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (!root) {
      return nullptr;
    }

    if (p == root || q == root) {
      return root;
    }

    populateMap(root, p, q);

    set<TreeNode *> parents;
    parents.insert(p);
    p = childToParent[p];
    while (p != root) {
      parents.insert(p);
      p = childToParent[p];
    }
    parents.insert(root);

    while (!parents.contains(q)) {
      q = childToParent[q];
    }

    return q;
  }
};

int main() {
  Solution solution;
  optional<int> null = nullopt;

  {
    TreeNode *root = create(vector<optional<int>>{1, 2, 3, null, 4});
    auto p = root->left->right;
    auto q = root->right;
    std::cout << "Input:    " << str(root) << ", p = " << p->val
              << ", q = " << q->val << '\n';
    auto ans = solution.lowestCommonAncestor(root, p, q);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << root << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root =
        create(vector<optional<int>>{3, 5, 1, 6, 2, 0, 8, null, null, 7, 4});
    auto p = root->left;
    auto q = root->right;
    std::cout << "Input:    " << str(root) << ", p = " << p->val
              << ", q = " << q->val << '\n';
    auto ans = solution.lowestCommonAncestor(root, p, q);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << root << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
