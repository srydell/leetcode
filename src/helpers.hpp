#include <deque>
#include <list>
#include <map>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

template <typename Key, typename Value>
std::string str(std::map<Key, Value> const &m) {
  std::stringstream ss;
  ss << '{' << '\n';
  for (auto const &[key, value] : m) {
    ss << "  " << key << ", " << value << '\n';
  }
  ss << '}';
  return ss.str();
}

template <typename T>
std::string str(std::vector<T> const &v, bool newline = false) {
  std::stringstream ss;
  ss << '[';
  if (newline) {
    ss << '\n';
  }
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    ss << v[static_cast<size_t>(i)];
    if (static_cast<size_t>(i) < v.size() - 1) {
      ss << ", ";
    }
    if (newline) {
      ss << '\n';
    }
  }
  ss << ']';
  return ss.str();
}

template <typename T>
std::string str(std::vector<std::vector<T>> const &v, bool newline = false) {
  std::stringstream ss;
  ss << '[';
  if (newline) {
    ss << '\n';
  }
  for (size_t i = 0; i < v.size(); i++) {
    ss << str(v[i]);
    if (i < v.size() - 1) {
      ss << ", ";
    }
    if (newline) {
      ss << '\n';
    }
  }
  ss << ']';
  return ss.str();
}

template <typename T>
std::string str(std::deque<T> const &d, bool newline = false) {
  std::vector<T> v(d.begin(), d.end());
  return str(v, newline);
}

std::string str(ListNode const *head) {
  std::stringstream ss;
  ss << '[';

  while (head) {
    ss << head->val;
    if (head->next) {
      ss << ", ";
    }
    head = head->next;
  }

  ss << ']';
  return ss.str();
}

void append_tree(std::stringstream &ss, TreeNode const *node, std::string const &prefix, bool is_left) {
  if (!node) {
    ss << prefix << (is_left ? "|-- " : "`-- ") << "null" << '\n';
    return;
  }

  ss << prefix << (is_left ? "|-- " : "`-- ") << node->val << '\n';

  if (!node->left && !node->right) {
    return;
  }

  std::string child_prefix = prefix + (is_left ? "|   " : "    ");
  append_tree(ss, node->left, child_prefix, true);
  append_tree(ss, node->right, child_prefix, false);
}

std::string str(TreeNode const *root) {
  if (!root) {
    return "null";
  }

  std::stringstream ss;
  ss << root->val << '\n';
  if (root->left || root->right) {
    append_tree(ss, root->left, "", true);
    append_tree(ss, root->right, "", false);
  }
  return ss.str();
}

ListNode *create(std::vector<int> const &v) {
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  for (int value : v) {
    auto *node = new ListNode(value);
    if (!head) {
      head = node;
    } else {
      tail->next = node;
    }
    tail = node;
  }
  return head;
}

TreeNode *create(std::vector<std::optional<int>> const &v) {
  if (v.empty() || !v[0].has_value()) {
    return nullptr;
  }

  auto *root = new TreeNode(v[0].value());
  std::queue<TreeNode *> nodes;
  nodes.push(root);
  size_t i = 1;
  while (i < v.size()) {
    TreeNode *current = nodes.front();
    nodes.pop();
    if (i < v.size()) {
      if (v[i].has_value()) {
        current->left = new TreeNode(v[i].value());
        nodes.push(current->left);
      }
      i++;
    }
    if (i < v.size()) {
      if (v[i].has_value()) {
        current->right = new TreeNode(v[i].value());
        nodes.push(current->right);
      }
      i++;
    }
  }
  return root;
}
