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
  int maxLevelSum(TreeNode *root) {
    if (!root) {
      return 0;
    }

    queue<pair<TreeNode *, size_t>> nodes;
    nodes.push({root, 0});

    vector<int64_t> scores;
    while (!nodes.empty()) {
      auto [current, level] = nodes.front();
      nodes.pop();

      if (level < scores.size()) {
        scores[level] += current->val;
      } else {
        scores.push_back(current->val);
      }

      for (auto *node : {current->left, current->right}) {
        if (node) {
          nodes.push({node, level + 1});
        }
      }
    }

    int64_t bestSofar = numeric_limits<int64_t>::min();
    int bestLevel = 0;
    for (size_t level = 0; level < scores.size(); level++) {
      if (bestSofar < scores[level]) {
        bestSofar = scores[level];
        bestLevel = static_cast<int>(level);
      }
    }

    // NOTE: The problem statement has levels starting on 1
    return bestLevel + 1;
  }
};

int main() {
  Solution solution;
  optional<int> null = nullopt;

  {
    TreeNode *root = create(vector<optional<int>>{1, 7, 0, 7, -8, null, null});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.maxLevelSum(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 2 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }

  {
    TreeNode *root = create(vector<optional<int>>{
        989, null, 10250, 98693, -89388, null, null, null, -32127});
    std::cout << "Input:    " << str(root) << '\n';
    auto ans = solution.maxLevelSum(root);
    std::cout << "Got:      " << ans << '\n';
    std::cout << "Expected: " << 2 << '\n';
    std::cout << "-------------------------------------" << '\n';
  }
}
